#include "ResolutionMethodWorker.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ResolutionMethodWorker w;
	w.show();
	return a.exec();
}
