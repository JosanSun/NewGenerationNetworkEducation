/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test
{
public:
    QGroupBox *groupBox;
    QLabel *currentTimeLabel;
    QLabel *label_2;
    QLabel *usernameLabel;
    QLabel *label_4;
    QLabel *currentPointNameLabel;
    QLabel *label_6;
    QLabel *label_8;
    QLabel *label_9;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *restHourLabel;
    QLabel *label_13;
    QLabel *restMinuteLabel;
    QLabel *label_14;
    QPushButton *submitButton;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *testHourLabel;
    QLabel *label_11;
    QLabel *testMinuteLabel;
    QLabel *label_12;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;

    void setupUi(QWidget *test)
    {
        if (test->objectName().isEmpty())
            test->setObjectName(QStringLiteral("test"));
        test->resize(870, 670);
        test->setMinimumSize(QSize(870, 670));
        test->setMaximumSize(QSize(870, 670));
        groupBox = new QGroupBox(test);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 151, 651));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(10);
        groupBox->setFont(font);
        currentTimeLabel = new QLabel(groupBox);
        currentTimeLabel->setObjectName(QStringLiteral("currentTimeLabel"));
        currentTimeLabel->setGeometry(QRect(10, 30, 131, 51));
        QFont font1;
        font1.setPointSize(12);
        currentTimeLabel->setFont(font1);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 90, 71, 21));
        label_2->setFont(font1);
        usernameLabel = new QLabel(groupBox);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
        usernameLabel->setGeometry(QRect(30, 120, 81, 21));
        usernameLabel->setFont(font1);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 160, 121, 31));
        label_4->setFont(font1);
        currentPointNameLabel = new QLabel(groupBox);
        currentPointNameLabel->setObjectName(QStringLiteral("currentPointNameLabel"));
        currentPointNameLabel->setGeometry(QRect(30, 200, 81, 21));
        currentPointNameLabel->setFont(font1);
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 250, 81, 21));
        label_6->setFont(font1);
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(4, 330, 141, 61));
        label_8->setFont(font1);
        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 400, 71, 31));
        label_9->setFont(font1);
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 440, 196, 20));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        restHourLabel = new QLabel(layoutWidget);
        restHourLabel->setObjectName(QStringLiteral("restHourLabel"));
        restHourLabel->setFont(font1);

        horizontalLayout_2->addWidget(restHourLabel);

        label_13 = new QLabel(layoutWidget);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setFont(font1);

        horizontalLayout_2->addWidget(label_13);

        restMinuteLabel = new QLabel(layoutWidget);
        restMinuteLabel->setObjectName(QStringLiteral("restMinuteLabel"));
        restMinuteLabel->setFont(font1);

        horizontalLayout_2->addWidget(restMinuteLabel);

        label_14 = new QLabel(layoutWidget);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setFont(font1);

        horizontalLayout_2->addWidget(label_14);

        submitButton = new QPushButton(groupBox);
        submitButton->setObjectName(QStringLiteral("submitButton"));
        submitButton->setGeometry(QRect(30, 590, 91, 23));
        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 290, 196, 20));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        testHourLabel = new QLabel(layoutWidget1);
        testHourLabel->setObjectName(QStringLiteral("testHourLabel"));
        testHourLabel->setFont(font1);

        horizontalLayout->addWidget(testHourLabel);

        label_11 = new QLabel(layoutWidget1);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setFont(font1);

        horizontalLayout->addWidget(label_11);

        testMinuteLabel = new QLabel(layoutWidget1);
        testMinuteLabel->setObjectName(QStringLiteral("testMinuteLabel"));
        testMinuteLabel->setFont(font1);

        horizontalLayout->addWidget(testMinuteLabel);

        label_12 = new QLabel(layoutWidget1);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setFont(font1);

        horizontalLayout->addWidget(label_12);

        scrollArea = new QScrollArea(test);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(170, 20, 691, 641));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 689, 639));
        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(test);

        QMetaObject::connectSlotsByName(test);
    } // setupUi

    void retranslateUi(QWidget *test)
    {
        test->setWindowTitle(QApplication::translate("test", "test", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("test", "\347\224\250\346\210\267\344\277\241\346\201\257", Q_NULLPTR));
        currentTimeLabel->setText(QApplication::translate("test", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("test", "\345\275\223\345\211\215\347\224\250\346\210\267\357\274\232", Q_NULLPTR));
        usernameLabel->setText(QApplication::translate("test", "TextLabel", Q_NULLPTR));
        label_4->setText(QApplication::translate("test", "\345\275\223\345\211\215\346\265\213\350\257\225\347\237\245\350\257\206\347\202\271\357\274\232", Q_NULLPTR));
        currentPointNameLabel->setText(QApplication::translate("test", "TextLabel", Q_NULLPTR));
        label_6->setText(QApplication::translate("test", "\346\265\213\350\257\225\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        label_8->setText(QApplication::translate("test", "<html><head/><body><p><span style=\" color:#ff0000;\">\346\263\250\346\204\217\357\274\232</span></p><p><span style=\" color:#ff0000;\">\346\227\266\351\227\264\345\210\260\357\274\214\350\207\252\345\212\250\344\272\244\345\215\267\357\274\201</span></p></body></html>", Q_NULLPTR));
        label_9->setText(QApplication::translate("test", "\345\275\223\345\211\215\350\277\230\345\211\251\357\274\232", Q_NULLPTR));
        restHourLabel->setText(QApplication::translate("test", "<html><head/><body><p><span style=\" color:#ff0000;\">TextLabel</span></p></body></html>", Q_NULLPTR));
        label_13->setText(QApplication::translate("test", "\346\227\266", Q_NULLPTR));
        restMinuteLabel->setText(QApplication::translate("test", "<html><head/><body><p><span style=\" color:#ff0000;\">TextLabel</span></p></body></html>", Q_NULLPTR));
        label_14->setText(QApplication::translate("test", "\345\210\206", Q_NULLPTR));
        submitButton->setText(QApplication::translate("test", "\346\217\220\344\272\244\350\257\225\345\215\267", Q_NULLPTR));
        testHourLabel->setText(QApplication::translate("test", "<html><head/><body><p><span style=\" color:#ff0000;\">TextLabel</span></p></body></html>", Q_NULLPTR));
        label_11->setText(QApplication::translate("test", "\346\227\266", Q_NULLPTR));
        testMinuteLabel->setText(QApplication::translate("test", "<html><head/><body><p><span style=\" color:#ff0000;\">TextLabel</span></p></body></html>", Q_NULLPTR));
        label_12->setText(QApplication::translate("test", "\345\210\206", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class test: public Ui_test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
