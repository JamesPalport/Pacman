#include <QApplication>
#include "map.h"
#include <iostream>
int main(int argc, char **argv)
{
	QApplication	app(argc, argv);
	Map				m;

	return (app.exec());
}
