#include <cstdlib>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <logger.h>
#include <framework.h>
#include <overlay.h>

int main()
{
	// Initialize graphics.
	Graphics g("Maze", 640, 480);
	
	// Create a framework over the window and the renderer.
	Framework framework(g);
	Scene scene(g);
	
	// Some dull objects
	scene.add_object(new ImageObject(g, DATA_PATH "/background.bmp"));
	
	Rectangle *rect = new Rectangle(g, {0, 0, 255, 255}, {255, 0, 0, 255});
	rect->x = rect->y = 0;
	rect->width = rect->height = 200;
	scene.add_object(rect);
	
	FilledRectangle *critical_region = new FilledRectangle(g, {255, 255, 255, 255});
	critical_region->x = critical_region->y = 400;
	critical_region->width = critical_region->height = 50;
	scene.add_object(critical_region);
	
	Text *text = new Text(g, "hello world!");
	text->x = text->y = 200;
	text->width = text->height = 200;
	scene.add_object(text);
	
	// Make the rectangle follow your mouse
	auto follow_mouse = [=](SDL_Event e) {
		rect->x = e.motion.x - rect->width / 2;
		rect->y = e.motion.y - rect->height / 2;
	};
	framework.listen("mouse-motion", follow_mouse);
	
	// When your rectangle touches the critical region, move the rect back.
	auto move_back = [=](Object *a, Object *b) {
		b->x = b->y = 0;
		log_info("Moving rect touches the critical region!\n");
	};
	OverlayHandler overlay2(move_back);
	overlay2.add_object(critical_region);
	overlay2.add_object(rect);
	framework.listen("mouse-motion", overlay2);
	
	// Switch to this scene, and run the event loop.
	framework.switch_scene(&scene);
	framework.run();
}
