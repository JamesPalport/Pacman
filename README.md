# Pacman
Custom Qt-based Pacman Game.

Everything is written in C++ using QGraphicsview/scene/item functionalities

![Pac](https://user-images.githubusercontent.com/45261035/71520938-ee971f00-28be-11ea-9532-188336f25673.gif)


### Game Logic

Pacman's upcoming direction is updated thanks to user input (arrow-keys), and changed in real time to avoid wall collision.

The red Ghost is following the pacman using an Astar algorithm.

Blue Ghosts are moving in a random way. The random choices available are set to avoid too frequent changes of directions.


### Graphics

Ghosts and Pacman are animated thanks to QPainter,
Pacman's color is customisable

Map's walls floor and lava tiles are found here https://opengameart.org/content/dungeon-crawl-32x32-tiles

Music background was found here: https://opengameart.org/content/xeon-theme-remastered

Coin sound was found here: https://opengameart.org/content/soundpack-02

Volume is changeable and the number of coins picked-up is displayed.
