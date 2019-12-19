#include "coin.h"

Coin::Coin(int size)
{
	m_size = size / 2;
}

QRectF	Coin::boundingRect() const
{
	return (QRectF(m_size / 2, m_size / 2, m_size, m_size));
}

QPainterPath	Coin::shape() const
{
	QPainterPath	path;

	path.addEllipse(boundingRect());//m_size / 2, m_size / 2, m_size, m_size);
	return (path);
}

void	Coin::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setBrush(QColor("#daa520"));
	painter->drawEllipse(boundingRect());
}
