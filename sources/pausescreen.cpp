#include "pausescreen.h"

PauseScreen::PauseScreen()
{
	m_item = nullptr;
	this->setHandlesChildEvents(false);
}

void			PauseScreen::addPause(QPushButton *m_pause)
{
	m_pause->setFont(QFont("Courier Header", 30, QFont::Bold));
	m_pause->setPalette(Qt::black);
	m_item = new QGraphicsProxyWidget();
	m_item->setWidget(m_pause);
	m_item->setZValue(this->zValue());
	m_item->setPos(static_cast<int>(boundingRect().width()
									- m_item->size().width()) / 2,
				   static_cast<int>(boundingRect().height() / 2));
	this->addToGroup(m_item);
	m_item->setOpacity(0.4);
}

void			PauseScreen::addButton(colorWindow *m_button)
{
	m_item = new QGraphicsProxyWidget();
	m_item->setWidget(m_button);
	m_item->setZValue(this->zValue());
	m_item->setPos(static_cast<int>(boundingRect().width()
									- m_item->size().width()) / 2,
				   static_cast<int>(boundingRect().height() / 2) + 60);
	this->addToGroup(m_item);
	m_item->setOpacity(0.4);
}

QPainterPath	PauseScreen::shape() const
{
	QPainterPath	path;

	path.addRect(this->scene()->sceneRect());
	return (path);
}

QRectF		PauseScreen::boundingRect() const
{
	return (this->scene()->sceneRect());
}

void		PauseScreen::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->setOpacity(0.8);
	painter->setBrush(Qt::black);
	painter->drawRect(boundingRect());
	painter->setOpacity(1);
	painter->setFont(QFont("Courier Header", 10));
	painter->setPen(Qt::white);
	painter->drawText(0, static_cast<int>(boundingRect().height() / 2) + 120
					  , static_cast<int>(boundingRect().width()), 55,
					  Qt::AlignHCenter, "Volume");
	painter->drawText(0, static_cast<int>(boundingRect().height() / 2 + 200)
					  , static_cast<int>(boundingRect().width()), 200,
					  Qt::AlignHCenter,
					  "Space = Pause/unPause\nArrows = Pacman directions\nR = Reset");
}
