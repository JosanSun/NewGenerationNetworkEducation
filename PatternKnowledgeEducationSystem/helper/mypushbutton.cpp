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
