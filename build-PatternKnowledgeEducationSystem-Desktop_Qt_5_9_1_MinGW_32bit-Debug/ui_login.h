/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *picLabel;
    QGroupBox *groupBox;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *loginClass)
    {
        if (loginClass->objectName().isEmpty())
            loginClass->setObjectName(QStringLiteral("loginClass"));
        loginClass->resize(545, 310);
        loginClass->setMinimumSize(QSize(545, 310));
        loginClass->setMaximumSize(QSize(545, 310));
        centralWidget = new QWidget(loginClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(140, 30, 211, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(17);
        label->setFont(font);
        picLabel = new QLabel(centralWidget);
        picLabel->setObjectName(QStringLiteral("picLabel"));
        picLabel->setGeometry(QRect(40, 20, 81, 51));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 90, 481, 191));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(12);
        groupBox->setFont(font1);
        loginButton = new QPushButton(groupBox);
        loginButton->setObjectName(QStringLiteral("loginButton"));
        loginButton->setGeometry(QRect(364, 40, 81, 23));
        registerButton = new QPushButton(groupBox);
        registerButton->setObjectName(QStringLiteral("registerButton"));
        registerButton->setGeometry(QRect(364, 90, 81, 23));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 20, 301, 111));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        usernameLineEdit = new QLineEdit(layoutWidget);
        usernameLineEdit->setObjectName(QStringLiteral("usernameLineEdit"));

        verticalLayout_2->addWidget(usernameLineEdit);

        passwordLineEdit = new QLineEdit(layoutWidget);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout_2->addWidget(passwordLineEdit);


        horizontalLayout->addLayout(verticalLayout_2);

        loginClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(loginClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 545, 23));
        loginClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(loginClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        loginClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(loginClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        loginClass->setStatusBar(statusBar);

        retranslateUi(loginClass);

        QMetaObject::connectSlotsByName(loginClass);
    } // setupUi

    void retranslateUi(QMainWindow *loginClass)
    {
        loginClass->setWindowTitle(QApplication::translate("loginClass", "login", Q_NULLPTR));
        label->setText(QApplication::translate("loginClass", "\345\234\250\347\272\277\347\275\221\347\273\234\346\225\231\345\255\246\347\263\273\347\273\237", Q_NULLPTR));
        picLabel->setText(QString());
        groupBox->setTitle(QString());
        loginButton->setText(QApplication::translate("loginClass", "\347\231\273\345\275\225", Q_NULLPTR));
        registerButton->setText(QApplication::translate("loginClass", "\346\263\250\345\206\214", Q_NULLPTR));
        label_2->setText(QApplication::translate("loginClass", "\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("loginClass", "\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class loginClass: public Ui_loginClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
