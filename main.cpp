#include "qtvtk.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtVtk w;
	w.show();
	return a.exec();
}
