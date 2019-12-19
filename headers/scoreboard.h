#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QTextItem>
#include <QPainter>
#include "constants.h"

class ScoreBoard : public QGraphicsItem
{
private:
	int						m_score;
	int						m_prevscore;
	QTextItem				*m_txtscore;

public:
	explicit		 ScoreBoard();
	~ScoreBoard() override;
	QPainterPath	shape() const override;
	void			advance(int step) override;
	void			paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
				  QWidget *widget) override;
	QRectF			boundingRect() const override
		{return QRectF(0, 0, 200, 300);}
	int				*score()
		{return (&m_score);}

};

#endif // SCOREBOARD_H
