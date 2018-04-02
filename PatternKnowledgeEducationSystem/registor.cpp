#include <QPixmap>
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <QPalette>
#include <QMouseEvent>

#include "registor.h"
#include "ui_registor.h"

registor::registor(QWidget *parent)
    : QWidget(parent), ui(new Ui::registor)
{
    ui->setupUi(this);

    mMove=false;//mouse moving

    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//无边框且最小化任务栏还原

    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, Qt::white);
    this->setPalette(palette);//设置窗口背景颜色：白

    QPixmap minPix=style()->standardPixmap(QStyle::SP_TitleBarMinButton);
    QPixmap closePix=style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
    ui->buttonMin->setIcon(minPix);
    ui->buttonClose->setIcon(closePix);//获取并设置最小化、关闭按钮图标

    QLineEdit* le = ui->sexComboBox->lineEdit();
    le->setPlaceholderText(tr("性别"));
    QLineEdit* lele = ui->educationComboBox->lineEdit();
    lele->setPlaceholderText(tr("教育程度"));//ComboBox暗注释

    //connect(ui->cancelButton, &QPushButton::clicked, this, &registor::close);                    // 关闭注册界面

    QObject::connect(ui->buttonClose, &QPushButton::clicked, this, &registor::close);              // 点击关闭
    QObject::connect(ui->buttonMin, &QPushButton::clicked, this, &registor::showMinimized);        // 点击最小化
}

registor::~registor()
{
    delete ui;
}

//重写鼠标函数实现窗口自由移动
void registor::mousePressEvent(QMouseEvent *event)
{
    mMove = true;
    //记录下鼠标相对于窗口的位置
    //event->globalPos()鼠标按下时，鼠标相对于整个屏幕位置
    //pos() this->pos()鼠标按下时，窗口相对于整个屏幕位置
    mPos = event->globalPos() - pos();
    return QWidget::mousePressEvent(event);
}

void registor::mouseMoveEvent(QMouseEvent *event)
{
    //(event->buttons() && Qt::LeftButton)按下是左键
    //通过事件event->globalPos()知道鼠标坐标，鼠标坐标减去鼠标相对于窗口位置，就是窗口在整个屏幕的坐标
    if (mMove && (event->buttons() && Qt::LeftButton)
        && (event->globalPos()-mPos).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-mPos);
        mPos = event->globalPos() - pos();
    }
    return QWidget::mouseMoveEvent(event);
}

void registor::mouseReleaseEvent(QMouseEvent *event)
{
    mMove = false;
}
//mouse END

QString registor::getUserName()
{
    return ui->usernameLineEdit->text();
}

QString registor::getSex()
{
    return ui->sexComboBox->currentText();
}

QString registor::getPassword()
{
    return ui->passwordLineEdit->text();
}

QString registor::getDoublePassword()
{
    return ui->doublePasswordLineEdit->text();
}

QString registor::getAge()
{
    return ui->ageLineEdit->text();
}

QString registor::getEducation()
{
    return ui->educationComboBox->currentText();
}

void registor::resetUserName()
{
    ui->usernameLineEdit->clear();
}

void registor::resetSex()
{
    ui->sexComboBox->setEditText(tr("男"));
}

void registor::resetPassword()
{
    ui->passwordLineEdit->clear();
}

void registor::resetDoublePassword()
{
    ui->doublePasswordLineEdit->clear();
}

void registor::resetAge()
{
    ui->ageLineEdit->clear();
}

void registor::resetEducation()
{
    ui->educationComboBox->setEditText(tr("请选择"));
}

void registor::resetAll()
{
    resetUserName();
    resetSex();
    resetPassword();
    resetDoublePassword();
    resetAge();
    resetEducation();
}

void registor::closeEvent(QCloseEvent * /* ev */)
{
    emit closeSignal();
}

void registor::on_registerButton_clicked()
{
    emit registerUser();
}
