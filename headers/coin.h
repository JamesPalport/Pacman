#ifndef COIN_H
#define COIN_H

#include <QGraphicsItem>
#include <QPainter>
#include "constants.h"

class Coin : public QGraphicsItem
{
private:
	int	m_size;

public:
	Coin(int size = TILE_SIZE);
	QRectF	boundingRect() const override;
	QPainterPath	shape() const override;
	void	paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
			   QWidget *widget) override;
	int		type() const override
		{return (Type);}
	enum {Type = UserType + 3};

};

#endif // COIN_H
