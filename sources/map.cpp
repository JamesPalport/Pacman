#include "map.h"

void	Map::initMatrix()
{
	int mat[20][30] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
		{1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
		{1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1},
		{1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0,-1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1},
		{1, 1, 0, 1, 1, 1, 1, 0, 1, 2, 2, 2, 2, 2, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 2, 3, 3, 3, 3, 3, 2, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
		{1, 0, 1, 1, 1, 0, 1, 0, 2, 3, 3,-3, 3, 3, 2, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1},
		{1, 0, 1, 0, 0, 0, 1, 0, 2, 3,-2,-2,-2, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 0, 1, 0, 1, 1, 1, 0, 2, 3, 3, 3, 3, 3, 2, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
		{1, 0, 1, 0, 1, 1, 1, 0, 1, 2, 2, 2, 2, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};

	matrice = new int*[size[1]];
	for (size_t i(0); i < size[1]; i++)
		matrice[i] = new int[size[0]];
	for (size_t j(0); j < size[1]; j++)
		for (size_t i(0); i < size[0]; i++)
			matrice[j][i] = mat[j][i];
}

Map::Map()
{
	size[0] = 30;
	size[1] = 20;
	initMatrix();
	m_scene = new QGraphicsScene();
	m_pacman = new Pacman(TILE_SIZE - 6);
	m_timer = new QTimer();
	scores = new ScoreBoard();
	pause = new PauseScreen();
	m_button = new colorWindow(m_pacman, this);
	m_playlist = new QMediaPlaylist();
	m_player = new QMediaPlayer();
	m_sl = new QSlider(Qt::Horizontal);
	m_pause = new QPushButton("Pause");

	m_playlist->addMedia(QMediaContent(QUrl("qrc:/Sound/music.ogg")));
	m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
	m_player->setPlaylist(m_playlist);
	m_player->setVolume(5);
	m_player->play();
	setupView();
	m_scene->addItem(pause);
	pause->setZValue(5);
	pause->setVisible(true);
	pause->addButton(m_button);
	pause->addPause(m_pause);
	m_sl->setValue(5);
	m_sl->setPalette(Qt::black);
	m_sl->setMaximum(100);
	m_sl->setMinimum(0);
	m_sl->setGeometry(0, 0, 100, 20);
	QGraphicsProxyWidget *slider =
			m_scene->addWidget(m_sl);
	slider->setPos(size[0] * TILE_SIZE - slider->rect().width() - 5,
			size[1] * TILE_SIZE + 5);
	slider->setZValue(5);
	QGraphicsTextItem *t = m_scene->addText("Volume");
	t->setDefaultTextColor(Qt::white);
	t->setPos(slider->x() - 60, slider->y() - 5);
	t->setZValue(5);
	m_scene->addItem(scores);
	scores->setPos(300, size[1] * TILE_SIZE + 10);
	QObject::connect(m_pause, &QPushButton::clicked,
					 this, &Map::Pause);
	QObject::connect(m_timer, &QTimer::timeout,
					 m_scene, &QGraphicsScene::advance);
	QObject::connect(m_sl, &QSlider::sliderMoved,
					 this, &Map::setVolume);
	setRenderHint(QPainter::Antialiasing);
	setScene(m_scene);
	setAlignment(Qt::AlignTop);
	setMinimumSize(static_cast<int>(size[0] * TILE_SIZE + 5),
			static_cast<int>( (size[1] + 1) * TILE_SIZE + 5));
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	show();
}

Map::~Map()
{
	for (size_t j(0); j < size[1]; j++)
		delete []matrice[j];
	delete []matrice;
}

void	Map::Pause()
{
	if (m_timer->isActive())
	{
		m_timer->stop();
		pause->setVisible(true);
	}
	else
	{
		pause->setVisible(false);
		m_timer->start(TIME);
	}
}

void	Map::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_Escape)
		QApplication::quit();
	else if (event->key() == Qt::Key_Space)
		Pause();
	if (event->key() == Qt::Key_R)
		resetMap();
	if (m_timer->isActive())
		m_pacman->keyPress(event);
}

void	Map::setVolume(int volume)
{
	m_player->setVolume(volume);
	if (volume > 5)
		m_pacman->setVolume(volume / 5);
	else if (volume >= 3)
		m_pacman->setVolume(1);
	else
		m_pacman->setVolume(0);
}

void	Map::resetMap()
{
	QList<QGraphicsItem *>::iterator	it;
	int	*score = scores->score();

	*score = 0;
	m_pacman->resetPosition();
	QList<QGraphicsItem *> list = m_scene->items();
	foreach (QGraphicsItem *item, list)
	{
		Ghost *g = qgraphicsitem_cast<Ghost *>(item);
		Coin *c = qgraphicsitem_cast<Coin *>(item);
		if (g != nullptr)
			g->resetPosition();
		else if (c != nullptr)
			c->show();
	}
}
