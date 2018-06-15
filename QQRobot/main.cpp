#include "qqrobot.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	qputenv("QTWEBENGINE_REMOTE_DEBUGGING", QByteArray().setNum(9000));
	QQRobot w;
	w.show();
	return a.exec();
}
