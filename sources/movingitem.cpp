#include "movingitem.h"

MovingItem::MovingItem(int size)
{
	m_size = size;
	m_size = size;
	m_dead = false;
	m_initpos[0] = m_initpos[1] = -1;
	m_dl[0] = m_dl[1] = m_nextdl[0] = m_nextdl[1] = 0;
	matrice = nullptr;
}
#include <QDebug>
void	MovingItem::setupSpeed()
{
	if (checkNext())
	{
		m_dl[0] = m_nextdl[0];
		m_dl[1] = m_nextdl[1];
	}
	setOffset();
	setX(x() + m_dl[0]);
	setY(y() + m_dl[1]);
}

void	MovingItem::boundariesHandler()
{
	if (x() < -TILE_SIZE / 2)
	{
		if (m_dl[0] < 0)
			setX(this->scene()->width());
		else
		{
			m_dl[0] = 0;
			setX(0);
		}
	}
	else if (x() > this->scene()->width())
	{
		if (m_dl[0] > 0)
			setX(-TILE_SIZE / 2);
		else
		{
			m_dl[0] = 0;
			setX(this->scene()->width() - m_size);
		}
	}
	if (y() < 0)
	{
		m_dl[1] = 0;
		setY(0);
	}
	else if (y() > this->scene()->height() - m_size)
	{
		m_dl[1] = 0;
		setY(this->scene()->height() - m_size);
	}
}

bool	MovingItem::checkNext()
{
	int	i = static_cast<int>(x()) / TILE_SIZE;
	int j = static_cast<int>(y()) / TILE_SIZE;

	if (m_nextdl[0])
	{
		int s = m_nextdl[0] > 0? 1: -1;
		if (i + s < 0 || i + s >= m_matsize[0])
			return (false);
		if (static_cast<int>(y()) % TILE_SIZE > TILE_SIZE - m_size
			&& (i + s > m_matsize[0] || i + s < 0
				|| matrice[j][i + s] > 0 || matrice[j + 1][i + s] > 0))
			return (false);
		else if (static_cast<int>(y()) % TILE_SIZE <= TILE_SIZE -m_size
				 && (i + s > m_matsize[0] || i + s < 0
					 || matrice[j][i + s] > 0))
			return (false);
	}
	else if (m_nextdl[1])
	{
		int s = m_nextdl[1] > 0? 1: -1;
		if (j + s < 0 || j + s >= m_matsize[1])
			return (false);
		if (static_cast<int>(x()) % TILE_SIZE > TILE_SIZE - m_size
			&& (matrice[j + s][i + 1] > 0 || matrice[j + s][i] > 0))
			return (false);
		else if (static_cast<int>(y()) % TILE_SIZE <= TILE_SIZE - m_size
				 && matrice[j + s][i] > 0)
			return (false);
	}
	return (true);
}


void	MovingItem::collideWall(QGraphicsPixmapItem *wall)
{
	while (this->collidesWithItem(wall))
	{
		m_dl[0] = m_dl[0] > 1? -1: m_dl[0] < -1? 1: m_dl[0];
		m_dl[1] = m_dl[1] > 1? -1: m_dl[1] < -1? 1: m_dl[1];
		setX(x() + m_dl[0]);
		setY(y() + m_dl[1]);
	}
	m_dl[0] = m_dl[1] = 0;
}

void	MovingItem::getMatrix(int **matrix, size_t size[2])
{
	matrice = matrix;
	m_matsize[0] = static_cast<int>(size[0]);
	m_matsize[1] = static_cast<int>(size[1]);
}

void	MovingItem::setInitPos(int i, int j)
{
	if (i >= 0 && i < m_matsize[0])
		m_initpos[0] = i;
	if (j >= 0 && j < m_matsize[1])
		m_initpos[1] = j;
}

void	MovingItem::resetPosition()
{
	if (m_initpos[0] >= 0 && m_initpos[0] < m_matsize[0]
		&& m_initpos[1] >= 0 && m_initpos[1] < m_matsize[1]
		&& matrice[m_initpos[1]][m_initpos[0]] <= 0)
		setPos(m_initpos[0] * TILE_SIZE + (TILE_SIZE - m_size) / 2,
				m_initpos[1] * TILE_SIZE + (TILE_SIZE - m_size) / 2);
	m_nextdl[0] = m_nextdl[1] = 0;
	m_dl[0] = m_dl[1] = 0;
}
