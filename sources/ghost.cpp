#include "ghost.h"

Ghost::Ghost(int size, int algo)
{
	m_size = size;
	m_size = size;
	m_algo = algo;
	m_count = 20;
	m_matsize[0] = 0;
	m_matsize[1] = 0;
	m_dl[0] = 	m_dl[1] = m_nextdl[0] = m_nextdl[1] = 0;
	m_offset[0] = m_offset[1] = 0;
	m_dl[0] = static_cast<int>(-GSPEED);
	m_enemy = nullptr;
}

QPainterPath	Ghost::shape() const
{
	QPainterPath	path;
	path.addEllipse(0, 0, m_size, m_size );
	return (path);
}

void	Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	QPainterPath	path;

	path.moveTo(m_size, m_size / 2);
	path.arcTo(0, 0, m_size, m_size , 0, 180);
	path.lineTo(0, m_size );
	path.cubicTo(m_size / 3, m_size / 2, m_size / 3, m_size , m_size / 2, m_size );
	path.cubicTo(m_size * 2 / 3, m_size , m_size * 2 / 3, m_size / 2, m_size, m_size );
	path.lineTo(m_size, m_size / 2);
	QRadialGradient radialGrad(QPointF(m_size / 2, 0), TILE_SIZE);
	if (m_algo == 1)
	{
		radialGrad.setColorAt(0.3, QColor("#DC143C"));
		radialGrad.setColorAt(0.8, QColor("#cd0000"));
	}
	else
	{
		radialGrad.setColorAt(0.3, QColor("#4169e1"));
		radialGrad.setColorAt(0.8, QColor("#0000cd"));
	}
	painter->setRenderHints(QPainter::Antialiasing);
	painter->setOpacity(0.8);
	painter->setBrush(radialGrad);
	painter->drawPath(path);
	painter->setBrush(Qt::white);
	painter->drawEllipse(m_size / 2 - 5 + m_offset[0],
			m_size / 3 + m_offset[1], 4, 4);
	painter->drawEllipse(m_size / 2 + 3 + m_offset[0],
			m_size / 3 + m_offset[1], 4, 4);
	this->scene()->update(this->scene()->sceneRect());
}

bool	Ghost::checkNext()
{
	int	i = static_cast<int>(x()) / TILE_SIZE;
	int j = static_cast<int>(y()) / TILE_SIZE;

	if (i < 0 || i >= m_matsize[0 || j < 0 || j >= m_matsize[1]])
		return (false);
	if (m_nextdl[0])
	{
		int s = m_nextdl[0] > 0? 1: -1;
		if (i + s < 0 || i + s >= m_matsize[0])
			return (false);
		if (static_cast<int>(y()) % TILE_SIZE > TILE_SIZE - m_size
			&& (matrice[j][i + s] == 1 || matrice[j + 1][i + s] == 1))
			return (false);
		else if (static_cast<int>(y()) % TILE_SIZE <= TILE_SIZE - m_size
				 && matrice[j][i + s] == 1)
			return (false);
	}
	else if (m_nextdl[1])
	{
		int s = m_nextdl[1] > 0? 1: -1;
		if (j + s < 0 || j + s >= m_matsize[1])
			return (false);
		if (static_cast<int>(x()) % TILE_SIZE > TILE_SIZE - m_size
			&& (matrice[j + s][i + 1] == 1 || matrice[j + s][i] == 1))
			return (false);
		else if (static_cast<int>(y()) % TILE_SIZE <= TILE_SIZE - m_size
				 && matrice[j + s][i] == 1)
			return (false);
	}
	return (true);
}

void	Ghost::setOffset()
{
	if (m_dl[0] == static_cast<int>(GSPEED))
	{
		m_offset[0] = 2;
		m_offset[1] = 0;
	}
	else if (m_dl[0] == static_cast<int>(-GSPEED))
	{
		m_offset[0] = -2;
		m_offset[1] = 0;
	}
	else if (m_dl[1] == static_cast<int>(GSPEED))
	{
		m_offset[0] = 0;
		m_offset[1] = 2;
	}
	else if (m_dl[1] == static_cast<int>(-GSPEED))
	{
		m_offset[0] = 0;
		m_offset[1] = -2;
	}
}

void	Ghost::useRandom()
{
	if (++m_count < 15)
		return ;
	m_count = 0;
	int	i = static_cast<int>(x()) / TILE_SIZE;
	int j = static_cast<int>(y()) / TILE_SIZE;
	if (i < 0 || i >= m_matsize[0] || j < 0 || j >= m_matsize[1])
		return ;
	if (matrice[j][i] != 0 && (m_dl[0] || m_dl[1]))
		return ;
	m_nextdl[0] = m_nextdl[1] = 0;
	if (m_dl[0] == 0 && m_dl[1] == 0)
	{
		int c = QRandomGenerator::global()->bounded(4);
		if (c == 0)
			m_nextdl[0] = static_cast<int>(GSPEED);
		else if (c == 1)
			m_nextdl[0] = static_cast<int>(-GSPEED);
		else if (c == 2)
			m_nextdl[1] = static_cast<int>(GSPEED);
		else
			m_nextdl[1] = static_cast<int>(-GSPEED);
		return ;
	}
	int *ptr = (m_dl[0] == 0)? m_nextdl: m_nextdl + 1;
	int c = QRandomGenerator::global()->bounded(2);
	if (c == 0)
		*ptr = static_cast<int>(GSPEED);
	else
		*ptr = static_cast<int>(-GSPEED);
}

void	Ghost::useAstar()
{
	if (m_enemy == nullptr)
		return ;
	QPoint	*s = new QPoint(static_cast<int>(x()) / TILE_SIZE,
							static_cast<int>(y()) / TILE_SIZE);
	QPoint	*e = new QPoint(static_cast<int>(m_enemy->x()) / TILE_SIZE,
							static_cast<int>(m_enemy->y()) / TILE_SIZE);
	int	*d = reach(s, e,matrice, m_matsize);
	delete s;
	delete e;
	if (d == nullptr)
		return ;
	if (d[0] != 0 && d[0] != 1 && d[0] != -1)
		d[0] = d[0] > 1? -1: 1;
	m_nextdl[0] = static_cast<int>(GSPEED) * d[0];
	m_nextdl[1] = static_cast<int>(GSPEED) * d[1];
	delete []d;
	if (m_nextdl[0] && static_cast<int>(y()) % TILE_SIZE > TILE_SIZE - m_size)
	{
		m_nextdl[0] = 0;
		m_nextdl[1] = static_cast<int>(-GSPEED);
	}
	else if (m_nextdl[1]
			 && static_cast<int>(x()) % TILE_SIZE > TILE_SIZE - m_size)
	{
		m_nextdl[0] = static_cast<int>(-GSPEED);
		m_nextdl[1] = 0;
	}
}

void	Ghost::setNextSpeed()
{
	if (m_algo == 1 && !m_enemy->isDead())
		useAstar();
	else
		useRandom();
}

void	Ghost::colisionsHandler()
{
	QList<QGraphicsItem *> coll = this->collidingItems();
	QList<QGraphicsItem *>::iterator	it;

	if (coll.isEmpty())
		return ;
	for (it = coll.begin(); it != coll.end(); it++)
		if (qgraphicsitem_cast<QGraphicsPixmapItem *>(*it))
			collideWall(qgraphicsitem_cast<QGraphicsPixmapItem *>(*it));
}

void	Ghost::advance(int step)
{
	if (!step)
		return ;
	setNextSpeed();
	setupSpeed();
	boundariesHandler();
	QGraphicsPixmapItem	*col = nullptr;
	if (!this->collidingItems().isEmpty())
		col = qgraphicsitem_cast<QGraphicsPixmapItem *>(this->collidingItems().first());
	while (col && col->pixmap().toImage() == m_wall.toImage())
	{
		m_dl[0] = m_dl[0] > 1? -1: m_dl[0] < -1? 1: m_dl[0];
		m_dl[1] = m_dl[1] > 1? -1: m_dl[1] < -1? 1: m_dl[1];
		setX(x() + m_dl[0]);
		setY(y() + m_dl[1]);
		col = nullptr;
		if (!this->collidingItems().isEmpty())
			col = qgraphicsitem_cast<QGraphicsPixmapItem *>(this->collidingItems().first());
		if (!col || col->pixmap().toImage() != m_wall.toImage())
			m_dl[0] = m_dl[1] = 0;
	}
}
