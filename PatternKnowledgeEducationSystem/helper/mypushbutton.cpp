#include "mypushbutton.h"

MyPushButton::MyPushButton(QWidget *parent)
    : QPushButton(parent)
{
    this->setText("myPushButton");
}

void MyPushButton::mousePressEvent(QMouseEvent * /* e */)
{
    myLabelPressed = 1;
}

void MyPushButton::mouseReleaseEvent(QMouseEvent * /* e */)
{
    if (myLabelPressed)
    {
        emit clicked(this->text());
        myLabelPressed = 0;
    }
}


QString MyPushButton::getInfo()
{
    return info;
}

void MyPushButton::setInfo(const QString &str)
{
    info = str;
}
