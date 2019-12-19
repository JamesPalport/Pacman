#ifndef PACMAN_H
#define PACMAN_H

#include <QMediaPlayer>
#include <QMediaContent>
#include "movingitem.h"
#include "coin.h"
#include "ghost.h"

class Pacman : public MovingItem
{
private:
	bool			m_spawning;
	int				m_rot;
	qreal			m_angle;
	qreal			m_dtheta;
	QColor			*m_color;
	int				*m_score;
	QMediaPlayer	*m_player;
	QMediaContent	*m_soundSmall;
	QMediaContent	*m_soundBig;

public:
	Pacman(int size = TILE_SIZE);
	~Pacman() override;
	QPainterPath	shape() const override;
	void			paint(QPainter *painter,
						  const QStyleOptionGraphicsItem *option,
						  QWidget *widget) override;
	void			keyPress(QKeyEvent *event);
	virtual void	setOffset() override;
	void			mouthMovement();
	void			collideCoin(Coin *c);
	void			collideGhost(Ghost *ghost);
	void			colisionsHandler();
	void			resetPosition() override;
	int				type() const override
		{return (Type);}
	void			setAngle(int angle)
		{m_angle = angle;}
	void			setColor(QColor color)
		{m_color->setNamedColor(color.name());}
	void			setSize(int size)
		{m_size = size;}
	void			setVolume(int vol)
		{m_player->setVolume(vol);}
	void			getScore(int *score)
		{m_score = score;}
	enum	{Type = UserType + 1};

protected:
	void advance(int step) override;

};

#endif // PACMAN_H
