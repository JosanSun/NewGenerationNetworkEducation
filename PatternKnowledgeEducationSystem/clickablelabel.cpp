#include "clickablelabel.h"

clickablelabel::clickablelabel(QWidget *parent)
	: QLabel(parent)
{
	this->setText("clickableLabel");
}

void clickablelabel::mousePressEvent(QMouseEvent * /* e */)
{
	myLabelPressed = 1;
}

void clickablelabel::mouseReleaseEvent(QMouseEvent * /* e */)
{
    if (myLabelPressed)
    {
		emit clicked();
		myLabelPressed = 0;
	}
}
