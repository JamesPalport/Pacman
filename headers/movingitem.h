#ifndef MOVINGITEM_H
#define MOVINGITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "constants.h"
#include "coin.h"

class MovingItem : public QGraphicsItem
{
protected:
	int		m_size;
	int		m_initpos[2];
	int		m_dl[2];
	int		m_nextdl[2];
	int		m_offset[2];
	int		**matrice;
	int		m_matsize[2];
	bool	m_dead;

public:
	MovingItem(int size = TILE_SIZE);
	virtual bool	checkNext();
	void			boundariesHandler();
	virtual void	setOffset() = 0;
	void			setupSpeed();
	QRectF			boundingRect() const override
		{return (QRectF(0, 0, m_size, m_size));}
	void			getMatrix(int **matrix, size_t size[2]);
	void			collideWall(QGraphicsPixmapItem *wall);
	void			setInitPos(int i, int j);
	bool			isDead()
		{return (m_dead);}
	void			kill()
		{m_dead = true;}
	virtual void	resetPosition();
};

#endif // MOVINGITEM_H
