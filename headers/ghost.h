#ifndef GHOST_H
#define GHOST_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsScene>
#include <iostream>
#include <QKeyEvent>
#include <QGraphicsView>
#include <QRandomGenerator>
#include <QPoint>
#include <QtMath>
#include "movingitem.h"
#include "constants.h"
#include "node.h"

class Ghost : public MovingItem
{
private:
	QPixmap			m_wall;
	int				m_count;
	MovingItem		*m_enemy;
	int				m_algo;

public:
	Ghost(int size = TILE_SIZE, int algo = 0);
	QPainterPath	shape() const override;
	void			paint(QPainter *painter,
						  const QStyleOptionGraphicsItem *option,
						  QWidget *widget) override;
	bool			checkNext() override;
	void			useRandom();
	void			useAstar();
	void			setNextSpeed();
	virtual void	setOffset() override;
	void			colisionsHandler();
	void			advance(int step) override;
	int				type() const override
		{return (Type);}
	void			setWall(QPixmap wall)
		{m_wall = wall;}
	void			setEnemy(MovingItem *enemy)
		{m_enemy = enemy;}
	enum {Type = UserType + 2};


};

#endif // GHOST_H
