/*-------- 可点击标签控件 ----------*/
/*========= 这个类不用管 ===========*/
#ifndef CLICKABLELABEL_H
#define CLICKABLELABEL_H

#include <QtGui>
#include <QLabel>

class clickablelabel : public QLabel
{
    Q_OBJECT

public:
    clickablelabel(QWidget *parent = 0);
    int myLabelPressed;
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void clicked();
};

#endif // CLICKABLELABEL_H
