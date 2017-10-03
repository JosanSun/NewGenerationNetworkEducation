#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	login w;
	w.setWindowTitle(QStringLiteral("在线网络教学系统"));
	w.show();
	return a.exec();
}
