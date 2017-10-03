/********************************************************************************
** Form generated from reading UI file 'usecase.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USECASE_H
#define UI_USECASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_usecase
{
public:
    QTextBrowser *textBrowser;
    QGroupBox *groupBox;
    QTextEdit *textEdit;
    QGroupBox *groupBox_2;
    QPushButton *testButton;
    QLabel *currentTimeLabel;
    QLabel *label_2;
    QLabel *usernameLabel;

    void setupUi(QWidget *usecase)
    {
        if (usecase->objectName().isEmpty())
            usecase->setObjectName(QStringLiteral("usecase"));
        usecase->resize(870, 650);
        usecase->setMinimumSize(QSize(870, 650));
        usecase->setMaximumSize(QSize(870, 650));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(10);
        usecase->setFont(font);
        textBrowser = new QTextBrowser(usecase);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(160, 10, 701, 461));
        groupBox = new QGroupBox(usecase);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(160, 480, 701, 161));
        groupBox->setContextMenuPolicy(Qt::NoContextMenu);
        groupBox->setCheckable(false);
        textEdit = new QTextEdit(groupBox);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 20, 681, 131));
        textEdit->setReadOnly(false);
        groupBox_2 = new QGroupBox(usecase);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 141, 631));
        testButton = new QPushButton(groupBox_2);
        testButton->setObjectName(QStringLiteral("testButton"));
        testButton->setGeometry(QRect(24, 260, 91, 31));
        QFont font1;
        font1.setPointSize(12);
        testButton->setFont(font1);
        currentTimeLabel = new QLabel(groupBox_2);
        currentTimeLabel->setObjectName(QStringLiteral("currentTimeLabel"));
        currentTimeLabel->setGeometry(QRect(10, 30, 121, 51));
        currentTimeLabel->setFont(font1);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 100, 71, 21));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font2.setPointSize(12);
        label_2->setFont(font2);
        usernameLabel = new QLabel(groupBox_2);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
        usernameLabel->setGeometry(QRect(30, 130, 91, 31));
        usernameLabel->setFont(font1);

        retranslateUi(usecase);

        QMetaObject::connectSlotsByName(usecase);
    } // setupUi

    void retranslateUi(QWidget *usecase)
    {
        usecase->setWindowTitle(QApplication::translate("usecase", "usecase", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("usecase", "\347\254\224\350\256\260\346\234\254", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("usecase", "\346\225\231\345\255\246\346\216\247\345\210\266", Q_NULLPTR));
        testButton->setText(QApplication::translate("usecase", "\350\277\233\345\205\245\346\265\213\350\257\225", Q_NULLPTR));
        currentTimeLabel->setText(QApplication::translate("usecase", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("usecase", "\345\275\223\345\211\215\347\224\250\346\210\267\357\274\232", Q_NULLPTR));
        usernameLabel->setText(QApplication::translate("usecase", "TextLabel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class usecase: public Ui_usecase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USECASE_H
