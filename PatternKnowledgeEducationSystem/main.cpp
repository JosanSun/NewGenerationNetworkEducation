#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    login loginSystem;
    loginSystem.setWindowTitle(QObject::tr("在线网络教学系统"));
    loginSystem.show();

    return app.exec();
}
