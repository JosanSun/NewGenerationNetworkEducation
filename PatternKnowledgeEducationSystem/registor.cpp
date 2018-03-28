#include "registor.h"
#include "ui_registor.h"

registor::registor(QWidget *parent)
    : QWidget(parent), ui(new Ui::registor)
{
    ui->setupUi(this);

    connect(ui->cancelButton, &QPushButton::clicked,
            this, &registor::close);                    // 关闭注册界面
}

registor::~registor()
{

}

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
