# Krush

This is basically a playground for game development. Maybe later it will evolve into a funny
game...?

## What is this, exactly?

Currently, this repo contains a shabby game development framework and a shabby game using it.

## Notes on the Framework
This framework (or engine?) consists of 4 types of components:
1. Graphics: wrapper around SDL window, renderer, etc.
2. Framework: switching scenes
3. Scene: collection of objects and event handlers
4. Object: to be displayed on a scene

This is rather straightforward, since it's a thin wrapper around SDL. You can easily dig the sources
for anything you want.

## Maze Game （妹子游戏（划掉
This is a traditional maze game, in which you use your mouse to guide yourself to leave a maze.
In the maze, the walls are toxic and you should never touch them! The exit is a green block. 
Go there, as soon as possible!

![Maze Map1](https://github.com/ksqsf/krush/blob/master/screeenshots/maze-map1.png?raw=true)

This game is not complete, and is not intended to be complete. You can change a line or two to make
it harder or easier for you.

You can draw your own map in `data/map1.maze`.
* `o` denotes the beginning point; should be unique
* `x` denotes the target; should be unique
* `#` denotes a toxic wall
* ` ` is safe for you to stand on.

## Copyright and License
Public Domain.
