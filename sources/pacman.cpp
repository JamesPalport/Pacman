#include "pacman.h"

Pacman::Pacman(int size) : MovingItem(size)
{
	m_spawning = false;
	m_rot = 0;
	m_offset[0] = m_size / 2;
	m_offset[1] = m_size / 2;
	m_angle = 30;
	m_color = new QColor(Qt::yellow);
	m_dtheta = DTHETA;
	m_player = new QMediaPlayer();
	m_soundSmall = new QMediaContent(QUrl("qrc:/Sound/smallcoin.ogg"));
	m_soundBig = new QMediaContent(QUrl("qrc:/Sound/bigcoin.ogg"));
	m_player->setMuted(false);
	m_player->setVolume(1);
}

Pacman::~Pacman()
{
	delete m_color;
	delete m_player;
	delete m_soundBig;
	delete m_soundBig;
}

QPainterPath	Pacman::shape() const
{
	QPainterPath	path;
	path.addEllipse(0, 0, m_size, m_size);
	return (path);
}

void	Pacman::paint(QPainter *painter,
					  const QStyleOptionGraphicsItem *, QWidget *)
{
	QPainterPath	path;

	path.arcTo(-m_size / 2, -m_size / 2, m_size, m_size,
			   m_angle, 360 - 2 * m_angle);
	painter->setRenderHints(QPainter::Antialiasing);
	painter->setBrush(*m_color);
	if (m_rot)
		painter->rotate(m_rot);
	painter->translate(m_offset[0], m_offset[1]);
	painter->drawPath(path);
	this->scene()->update(this->scene()->sceneRect());
}

void	Pacman::mouthMovement()
{
	if (m_angle >= 60)
		m_dtheta = -DTHETA;
	else if (m_angle <= 10)
		m_dtheta = DTHETA;
	m_angle += m_dtheta;
}

void	Pacman::setOffset()
{
	if (m_dl[0] == static_cast<int>(SPEED))
	{
		m_rot = 0;
		m_offset[0] = m_size / 2;
		m_offset[1] = m_size / 2;
	}
	else if (m_dl[0] == static_cast<int>(-SPEED))
	{
		m_rot = 180;
		m_offset[0] = -m_size / 2;
		m_offset[1] = -m_size / 2;
	}
	else if (m_dl[1] == static_cast<int>(SPEED))
	{
		m_rot = 90;
		m_offset[0] = m_size / 2;
		m_offset[1] = -m_size / 2;
	}
	else if (m_dl[1] == static_cast<int>(-SPEED))
	{
		m_rot = -90;
		m_offset[0] = -m_size / 2;
		m_offset[1] = m_size / 2;
	}
}

void	Pacman::collideCoin(Coin *c)
{
	c->setVisible(false);
	if (m_player->position() == 0 || m_player->position() >= 150)
	{
		m_player->setMedia(*m_soundSmall);
		m_player->play();
	}
	*m_score += 1;
}

void	Pacman::collideGhost(Ghost *ghost)
{
	if (m_dead || ghost->isDead())
		return;
	m_dl[0] = m_dl[1] = 0;
	m_nextdl[0] = m_nextdl[1] = 0;
	m_dead = true;
}

void	Pacman::colisionsHandler()
{
	QList<QGraphicsItem *> coll = this->collidingItems();
	QList<QGraphicsItem *>::iterator	it;

	if (coll.isEmpty())
		return ;
	for (it = coll.begin(); it != coll.end(); it++)
	{
		if (qgraphicsitem_cast<QGraphicsPixmapItem *>(*it))
			collideWall(qgraphicsitem_cast<QGraphicsPixmapItem *>(*it));
		else if (qgraphicsitem_cast<Coin *>(*it))
			collideCoin(qgraphicsitem_cast<Coin *>(*it));
		else if (qgraphicsitem_cast<Ghost *>(*it))
			collideGhost(qgraphicsitem_cast<Ghost *>(*it));
	}
}

void	Pacman::advance(int step)
{
	if (!step)
		return ;
	if (m_dead && !m_spawning)
	{
		m_angle += DTHETA;
		if (m_angle >= 180)
		{
			m_angle = 180;
			m_spawning = true;
			if (m_initpos[0] >= 0 && m_initpos[1] >= 0
				&& matrice[m_initpos[1]][m_initpos[0]] <= 0)
				setPos(m_initpos[0] * TILE_SIZE + (TILE_SIZE - m_size) / 2,
						m_initpos[1] * TILE_SIZE + (TILE_SIZE - m_size) / 2);
		}
	}
	else if (m_spawning)
	{
		m_angle -= DTHETA;
		if (m_angle <= 30)
		{
			m_spawning = false;
			m_dead = false;
		}
	}
	else
	{
		setupSpeed();
		mouthMovement();
		boundariesHandler();
		colisionsHandler();
	}
}

void	Pacman::keyPress(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Up)
	{
		m_nextdl[0] = 0;
		m_nextdl[1] = static_cast<int>(-SPEED);
	}
	else if (event->key() == Qt::Key_Down)
	{
		m_nextdl[0] = 0;
		m_nextdl[1] = static_cast<int>(SPEED);
	}
	else if (event->key() == Qt::Key_Left)
	{
		m_nextdl[0] = static_cast<int>(-SPEED);
		m_nextdl[1] = 0;
	}
	else if (event->key() == Qt::Key_Right)
	{
		m_nextdl[0] = static_cast<int>(SPEED);
		m_nextdl[1] = 0;
	}
}

void	Pacman::resetPosition()
{
	m_rot = 0;
	m_offset[0] = m_size / 2;
	m_offset[1] = m_size / 2;
	m_angle = 30;
	m_dead = false;
	m_spawning = false;
	MovingItem::resetPosition();
}
