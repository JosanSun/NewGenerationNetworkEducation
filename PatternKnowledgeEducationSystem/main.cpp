#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    login loginSystem;

    loginSystem.show();

    return app.exec();
}
