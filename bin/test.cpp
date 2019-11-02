#include <cstdlib>
#include <SDL.h>

#include <logger.h>
#include <framework.h>
#include <overlay.h>

int main(int argc, char *argv[])
{
	// Initialize graphics.
	Graphics g("Test", 640, 480);
	
	// Create a framework over the window and the renderer.
	Framework framework(g);
	auto scene = std::make_shared<Scene>(g);
	framework.switch_scene(scene);
	
	// Some dull objects
	scene->add_object(new ImageObject(g, DATA_PATH "/background.bmp"));
	
	Rectangle *rect = new Rectangle(g, {0, 0, 255, 255}, {255, 0, 0, 255});
	rect->x = rect->y = 0;
	rect->width = rect->height = 200;
	scene->add_object(rect);
	
	FilledRectangle *critical_region = new FilledRectangle(g, {255, 255, 255, 255});
	critical_region->x = critical_region->y = 400;
	critical_region->width = critical_region->height = 50;
	scene->add_object(critical_region);
	
	Text *text = new Text(g, "hello world!");
	text->x = text->y = 200;
	text->width = text->height = 200;
	scene->add_object(text);
	
	// Make the rectangle follow your mouse
	auto follow_mouse = [=](SDL_Event e) {
		rect->x = e.motion.x - rect->width / 2;
		rect->y = e.motion.y - rect->height / 2;
		return true;
	};
	scene->listen("mouse-motion", follow_mouse);
	
	// When your rectangle touches the critical region, move the rect back.
	auto move_back = [=](Object *a, Object *b) {
		b->x = b->y = 0;
		log_info("Moving rect touches the critical region!\n");
		return true;
	};
	OverlayHandler overlay(move_back);
	overlay.add_object(critical_region);
	overlay.add_object(rect);
	scene->listen("mouse-motion", overlay);
	
	// Move the critical region slowly
	int dx = 1, dy = 1;
	scene->alarm(1, [=]() mutable {
		critical_region->x += dx;
		critical_region->y += dy;
		if (critical_region->x + critical_region->width >= 640 || critical_region->x <= 0) {
			dx = -dx;
		}
		if (critical_region->y + critical_region->height >= 480 || critical_region->y <= 0) {
			dy = -dy;
		}
		return true; // do not remove this handler
	});
	
	// Switch to this scene, and run the event loop.
	framework.run();
}
