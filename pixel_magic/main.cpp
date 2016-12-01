#include "pixel_magic.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	pixel_magic w;

	w.show();

	return a.exec();
}
