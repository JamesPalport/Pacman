#include "colorwindow.h"

colorWindow::colorWindow(Pacman *object, QGraphicsView *view) : QWidget()
{
	m_obj = object;
	bouton = new QPushButton("color", this);
	m_map = view;
	m_menu = new QMenu();
	m_menu->setPalette(Qt::black);
	m_menu->setFont(QFont("Courier Header", 20));
	QAction *act = m_menu->addAction("Blue");
	QObject::connect(act, &QAction::triggered, this, &colorWindow::chooseColor);
	act = m_menu->addAction("Red");
	QObject::connect(act, &QAction::triggered, this, &colorWindow::chooseColor);
	act = m_menu->addAction("Yellow");
	QObject::connect(act, &QAction::triggered, this, &colorWindow::chooseColor);
	bouton->setMenu(m_menu);
	act = m_menu->addAction("Custom");
	QObject::connect(act, &QAction::triggered, this, &colorWindow::chooseColor);
	this->setPalette(Qt::black);
	this->setFont(QFont("Courier Header", 30, QFont::Bold));
}

colorWindow::~colorWindow()
{
	m_menu->clear();
	delete m_menu;
}

void	colorWindow::chooseColor()
{
	QColor color(qobject_cast<QAction *>(QObject::sender())->text());
	if (!color.isValid())
	{
		m_map->hide();
		color = QColorDialog::getColor(Qt::yellow, nullptr, "Pacman's Color",
									   QColorDialog::DontUseNativeDialog);
		m_map->show();
	}
	if (color.isValid())
		m_obj->setColor(color);
}
