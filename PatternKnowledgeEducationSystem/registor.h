/*========== 注册模块 ============*/
#ifndef REGISTOR_H
#define REGISTOR_H

#include <QWidget>

namespace Ui {
class registor;
}

class registor : public QWidget
{
	Q_OBJECT

public:
	registor(QWidget *parent = 0);
	~registor();

    //get and set Functions
    QString getUserName();
    QString getSex();
    QString getPassword();
    QString getDoublePassword();
    QString getAge();
    QString getEducation();

    void resetUserName();
    void resetSex();
    void resetPassword();
    void resetDoublePassword();
    void resetAge();
    void resetEducation();
    void resetAll();

signals:
    void registerUser();
    void closeSignal();

protected:
    void closeEvent(QCloseEvent* ev);

private:
    Ui::registor* ui;

private slots:
    //void sendRegisterSignal();
    //void cancel();
    void on_registerButton_clicked();
};

#endif // REGISTOR_H
