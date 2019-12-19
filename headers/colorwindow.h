#ifndef COLORWINDOW_H
#define COLORWINDOW_H

#include <QWidget>
#include <QColorDialog>
#include <QPushButton>
#include <QMenu>
#include <QAction>
#include <QGraphicsItem>
#include <QGraphicsView>
#include "pacman.h"

class colorWindow : public QWidget
{
	Q_OBJECT
public:
	colorWindow(Pacman *object, QGraphicsView *view);
	~colorWindow();

public slots:
	void	chooseColor();

private:
	Pacman			*m_obj;
	QPushButton		*bouton;
	QGraphicsView	*m_map;
	QMenu			*m_menu;
};

#endif // COLORWINDOW_H
