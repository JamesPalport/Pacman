#include "map.h"

void	Map::addWall(QPixmap imageWall, size_t i, size_t j)
{
	QGraphicsPixmapItem *im = m_scene->addPixmap(imageWall);
	im->setPos(i * TILE_SIZE,
			   j * TILE_SIZE);
	im->setZValue(3);
}

void	Map::addWater(QPixmap imageWater, size_t i, size_t j)
{
	QGraphicsPixmapItem *im = m_scene->addPixmap(imageWater);
	im->setPos(i * TILE_SIZE,
			   j * TILE_SIZE);
	im->setZValue(0);
}

void	Map::addFloor(QPixmap imageFloor, size_t i, size_t j)
{
	QGraphicsPixmapItem *im = m_scene->addPixmap(imageFloor);
	im->setPos(i * TILE_SIZE,
			   j * TILE_SIZE);
	im->setZValue(0);
}

void	Map::setupPacman(size_t i, size_t j)
{
	m_scene->addItem(m_pacman);
	m_pacman->setZValue(2);
	m_pacman->getMatrix(matrice, size);
	m_pacman->setInitPos(static_cast<int>(i), static_cast<int>(j));
	m_pacman->setPos(i * TILE_SIZE + 3,
					 j * TILE_SIZE + 3);
	m_pacman->getScore(scores->score());
}

void	Map::putGhost(size_t i, size_t j, QPixmap imageWall, QPixmap imageFloor)
{
	Ghost *ghost = new Ghost(TILE_SIZE - 6);

	addFloor(imageFloor, i, j);
	m_scene->addItem(ghost);
	ghost->setZValue(2);
	ghost->getMatrix(matrice, size);
	ghost->setInitPos(static_cast<int>(i), static_cast<int>(j));
	ghost->setPos(i * TILE_SIZE + 3,
				  j * TILE_SIZE + 3);
	ghost->setWall(imageWall);
	ghost->setEnemy(m_pacman);
}

void	Map::putGhostStar(size_t i, size_t j, QPixmap imageWall,
						  QPixmap imageFloor)
{
	Ghost *ghost = new Ghost(TILE_SIZE - 6, 1);

	addFloor(imageFloor, i, j);
	m_scene->addItem(ghost);
	ghost->setZValue(2);
	ghost->getMatrix(matrice, size);
	ghost->setInitPos(static_cast<int>(i), static_cast<int>(j));
	ghost->setPos(i * TILE_SIZE + 3,
				  j * TILE_SIZE + 3);
	ghost->setWall(imageWall);
	ghost->setEnemy(m_pacman);
}

void	Map::putCoin(size_t i, size_t j)
{
	Coin *c = new Coin();
	m_scene->addItem(c);
	c->setPos(i * TILE_SIZE, j * TILE_SIZE);
	c->setZValue(0);
}

void	Map::setupView()
{
	QPixmap	imageWall(":/Image/wall.png");
	QPixmap	imageGround(":/Image/ground.png");
	QPixmap	imageFloor(":/Image/floor.png");
	QPixmap	imageWater(":/Image/water.png");
	QBrush	ground;

	ground.setTexture(imageGround);
	imageWall = imageWall.scaledToHeight(TILE_SIZE);
	imageWater = imageWater.scaledToHeight(TILE_SIZE);
	imageFloor = imageFloor.scaledToHeight(TILE_SIZE);
	m_scene->setSceneRect(0, 0, size[0] * TILE_SIZE, size[1] * TILE_SIZE);
	m_scene->setBackgroundBrush(ground);
	for (size_t i(0); i < size[0]; i++)
	{
		for (size_t j(0); j < size[1]; j++)
		{
			if (matrice[j][i] == -1)
				setupPacman(i, j);
			else if (matrice[j][i] == -2)
				putGhost(i, j, imageWall, imageFloor);
			else if (matrice[j][i] == -3)
				putGhostStar(i, j, imageWall, imageFloor);
			else if (matrice[j][i] == 1)
				addWall(imageWall, i, j);
			else if (matrice[j][i] == 2)
				addWater(imageWater, i, j);
			else if (matrice[j][i] == 3)
				addFloor(imageFloor, i, j);
			else if (matrice[j][i] == 0)
				putCoin(i, j);
		}
	}
}
