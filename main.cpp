#include "starburst.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	starburst w;
	w.show();
	return a.exec();
}
