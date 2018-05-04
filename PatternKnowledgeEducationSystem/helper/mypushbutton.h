/*   ======= 自定义按钮 =========== 
     ======= 这个类也不用管 =======
*/
#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT

public:
    explicit MyPushButton(QWidget *parent);
    int myLabelPressed;
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void clicked(QString);
};

#endif // MYPUSHBUTTON_H
