# Krush

This is basically a playground for game development. Maybe later it will evolve into a funny
game...?

## What is this, exactly?

Currently, this repo contains a shabby game development framework. I believe it's capable of 
doing very tiny and stupid games. Later I'll post one or two games in this framework as a proof.

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
