#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include <QGraphicsItem>
#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QSlider>
#include "pacman.h"
#include "colorwindow.h"

class PauseScreen : public QGraphicsItemGroup
{
private:
	QTimer		*m_timer;
	QGraphicsProxyWidget *m_item;

public:
	PauseScreen();
	void			addPause(QPushButton *m_pause);
	void			addButton(colorWindow *m_button);
	QPainterPath	shape() const override;
	void			paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
				  QWidget *widget) override;
	QRectF			boundingRect() const override;
};

#endif // PAUSESCREEN_H
