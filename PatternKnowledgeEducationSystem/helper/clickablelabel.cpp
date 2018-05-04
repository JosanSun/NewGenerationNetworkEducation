#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget *parent)
    : QLabel(parent)
{
    this->setText("clickableLabel");
}

void ClickableLabel::mousePressEvent(QMouseEvent * /* e */)
{
    myLabelPressed = 1;
}

void ClickableLabel::mouseReleaseEvent(QMouseEvent * /* e */)
{
    if (myLabelPressed)
    {
        emit clicked();
        myLabelPressed = 0;
    }
}
