#include "scoreboard.h"
#include <iostream>

ScoreBoard::ScoreBoard()
{
	m_txtscore = new QTextItem();
	m_score = m_prevscore = 0;
}

ScoreBoard::~ScoreBoard()
{
	delete m_txtscore;
}

void	ScoreBoard::advance(int step)
{
	if (!step)
		return ;
	if (m_score == m_prevscore)
		return ;
	m_prevscore = m_score;
}

QPainterPath	ScoreBoard::shape() const
{
	QPainterPath	path;

	path.addRect(0, 0, 50, 50);
	return (path);
}

void	ScoreBoard::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
						  QWidget *)
{
	painter->setBrush(Qt::black);
	painter->setOpacity(0.5);
	painter->drawRect(static_cast<int>(-x()),
		static_cast<int>(this->scene()->sceneRect().height() - y()),
					  static_cast<int>(this->scene()->width()), TILE_SIZE);
	painter->setOpacity(1);
	painter->setBrush(QColor("#daa520"));
	painter->drawEllipse(0, 0, 15, 15);
	painter->setPen(Qt::yellow);
	painter->drawText(20 , 13, QString::number(m_score));
	this->scene()->update(x(), y(), 200, 300);
}
