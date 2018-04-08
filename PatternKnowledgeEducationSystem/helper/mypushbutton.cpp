#include "mypushbutton.h"

myPushButton::myPushButton(QWidget *parent)
    : QPushButton(parent)
{
    this->setText("myPushButton");
}

void myPushButton::mousePressEvent(QMouseEvent * /* e */)
{
    myLabelPressed = 1;
}

void myPushButton::mouseReleaseEvent(QMouseEvent * /* e */)
{
    if (myLabelPressed)
    {
        emit clicked(this->text());
        myLabelPressed = 0;
    }
}
