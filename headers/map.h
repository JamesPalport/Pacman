#ifndef MAP_H
#define MAP_H

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QGraphicsProxyWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSlider>
#include "pacman.h"
#include "ghost.h"
#include "colorwindow.h"
#include "constants.h"
#include "coin.h"
#include "scoreboard.h"
#include "pausescreen.h"

class Map : public QGraphicsView
{
	Q_OBJECT
public:
	explicit	Map();
	~Map() override;
	void	keyPressEvent(QKeyEvent *event) override;
	void	initMatrix();
	void	setupView();
	void	addWall(QPixmap imageWall, size_t i, size_t j);
	void	addWater(QPixmap imageWater, size_t i, size_t j);
	void	addFloor(QPixmap imageFloor, size_t i, size_t j);
	void	setupPacman(size_t i, size_t j);
	void	putGhost(size_t i, size_t j, QPixmap imageWall, QPixmap imageFloor);
	void	putGhostStar(size_t i, size_t j, QPixmap imageWall,
						 QPixmap imageFloor);
	void	putCoin(size_t i, size_t j);
	void	resetMap();
	void	Pause();

private:
	QGraphicsScene	*m_scene;
	Pacman			*m_pacman;
	Ghost			*m_ghost;
	QTimer			*m_timer;
	colorWindow		*m_button;
	size_t			size[2];
	int				**matrice;
	ScoreBoard		*scores;
	PauseScreen		*pause;
	QMediaPlayer	*m_player;
	QMediaPlaylist	*m_playlist;
	QSlider			*m_sl;
	QPushButton		*m_pause;


signals:

public slots:
	void	setVolume(int volume);

};

#endif // MAP_H
