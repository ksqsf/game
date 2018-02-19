#include <cstdio>
#include <cassert>
#include <utility>
#include <logger.h>
#include <framework.h>
#include <overlay.h>
using namespace std;

const int scrw = 640;
const int scrh = 480;
const int block_size = 40; // 16x12
const int sprite_size = 25;

enum BlockType {
	EMPTY,
	BLOCK,
	BEGIN,
	END
} map1_buf[scrh/block_size][scrw/block_size];
bool game_running = false;

int begx, begy, endx, endy;
static void load_mapfile(BlockType buf[scrh/block_size][scrw/block_size], const char *pathname);
static SDL_Color get_color_by_type(BlockType type);

int main(int argc, char *argv[])
{
	if (argc != 2)
		load_mapfile(map1_buf, DATA_PATH "/map1.maze");
	else
		load_mapfile(map1_buf, argv[1]);
	
	// Game
	Graphics g("Maze", scrw, scrh);
	Framework framework(g);
	
	auto lost = make_shared<Scene>(g);
	auto win = make_shared<Scene>(g);
	auto map1 = make_shared<Scene>(g);
	
	// Map1 scene
	auto sprite = new ImageObject(g, DATA_PATH "/sprites.png");
	sprite->x = begx;
	sprite->y = begy;
	sprite->width = sprite->height = sprite_size;
	map1->add_object(sprite);
	map1->listen("mouse-motion", [&](SDL_Event e) mutable {
		// If the game is running (the mouse is held), the sprite should follow the mouse.
		if (game_running) {
			sprite->x = e.motion.x - sprite->width/2;
			sprite->y = e.motion.y - sprite->height/2;
		}
		return true;
	});
	map1->listen("mouse-button-down", [&](SDL_Event e) mutable {
		// If the game is not running, and the player clicks inside the sprite, the game is on.
		// If the player clicks another place, (s)he will lost immediately.
		if (begx <= e.motion.x && e.motion.x <= begx + sprite_size
			&& begy <= e.motion.y && e.motion.y <= begy + sprite_size)
			game_running = true;
		else
			framework.switch_scene(lost);
		return true;
	});
	map1->listen("mouse-button-up", [&](SDL_Event e) mutable {
		// If the player releases the mouse before (s)he reaches the target, (s)he will immediately
		// lose the game.
		game_running = false;
		framework.switch_scene(lost);
		return true;
	});
	
	auto target = new FilledRectangle(g, {0, 255, 0, 255});
	target->x = endx;
	target->y = endy;
	target->width = target->height = block_size;
	map1->add_object(target);
	
	map1->listen("mouse-motion", OverlayHandler({sprite, target}, [&](Object*, Object*) {
		// If the player reaches the target, (s)he will win, and the game will not be running
		// anymore.
		game_running = false;
		framework.switch_scene(win);
		return true;
	}));
	
	for (int i = 0; i < scrh/block_size; ++i) {
		for (int j = 0; j < scrw/block_size; ++j) {
			if (map1_buf[i][j] != BLOCK)
				continue;
			
			auto block = new FilledRectangle(g, {0, 0, 0, 191});
			block->x = j*block_size;
			block->y = i*block_size;
			block->width = block->height = block_size;
			map1->add_object(block);
			map1->listen("mouse-motion", OverlayHandler({sprite, block}, [&](Object*, Object*) {
				// If the player touches any of the rectangle, (s)he will lose the game.
				game_running = false;
				framework.switch_scene(lost);
				return true;
			}));
		}
	}
	
	// Lost scene
	auto lost_msg = new Text(g, "You've lost!");
	auto retry_msg = new Text(g, "Press any key to retry...", 24);
	lost_msg->x = (scrw - lost_msg->width) / 2;
	lost_msg->y = (scrh - lost_msg->height) / 2;
	retry_msg->x = lost_msg->x + lost_msg->width/2 - retry_msg->width/2;
	retry_msg->y = lost_msg->y + lost_msg->height/2 + retry_msg->height;
	lost->add_object(lost_msg);
	lost->add_object(retry_msg);
	lost->listen("key-down", [&](SDL_Event e) mutable {
		game_running = false;
		sprite->x = begx;
		sprite->y = begy;
		framework.switch_scene(map1);
		return true;
	});
	
	// Win scene
	auto win_msg = new Text(g, "You win!");
	auto restart_msg = new Text(g, "Press any key to start a new game...", 24);
	win_msg->x = (scrw - win_msg->width) / 2;
	win_msg->y = (scrh - win_msg->height) / 2;
	restart_msg->x = lost_msg->x + lost_msg->width/2 - restart_msg->width/2;
	restart_msg->y = lost_msg->y + lost_msg->height/2 + restart_msg->height;
	win->add_object(win_msg);
	win->add_object(restart_msg);
	win->listen("key-down", [&](SDL_Event e) mutable {
		game_running = false;
		sprite->x = begx;
		sprite->y = begy;
		framework.switch_scene(map1);
		return true;
	});
	
	g.warp_mouse(begx, begy);
	framework.switch_scene(map1);
	framework.run();
}

static void load_mapfile(BlockType buf[scrh/block_size][scrw/block_size], const char *pathname)
{
	char linebuf[scrw/block_size+4];
	FILE *fp = nullptr;
	
	fp = fopen(pathname, "r");
	if (!fp) {
		log_fatal("Failed to read map data!\n");
		abort();
	}
	
	for (int i = 0; i < scrh/block_size; ++i) {
		fgets(linebuf, scrw/block_size+4, fp);
		for (int j = 0; j < scrw/block_size; ++j) {
				switch(linebuf[j]) {
				case ' ': map1_buf[i][j] = EMPTY; break;
				case '#': map1_buf[i][j] = BLOCK; break;
				case 'o': 
					map1_buf[i][j] = BEGIN;
					begx = j * block_size + block_size/2 - sprite_size/2;
					begy = i * block_size + block_size/2 - sprite_size/2;
					break;
				case 'x': 
					map1_buf[i][j] = END;
					endx = j * block_size;
					endy = i * block_size;
					break;
				default: assert(false);
			}
		}
	}
}
