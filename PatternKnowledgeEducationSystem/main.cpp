#include "stable.h"
#include <QApplication>
#include "login.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Login loginSystem;
    loginSystem.show();

    return app.exec();
}
