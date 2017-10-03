/********************************************************************************
** Form generated from reading UI file 'initial.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INITIAL_H
#define UI_INITIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_initial
{
public:
    QGroupBox *groupBox;
    QLabel *currentTimeLabel;
    QLabel *label;
    QLabel *usernameLabel;
    QLabel *label_3;
    QLabel *lastPointnameLabel;
    QPushButton *quitButton;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_6;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_10;

    void setupUi(QWidget *initial)
    {
        if (initial->objectName().isEmpty())
            initial->setObjectName(QStringLiteral("initial"));
        initial->resize(690, 480);
        initial->setMinimumSize(QSize(690, 480));
        initial->setMaximumSize(QSize(690, 480));
        groupBox = new QGroupBox(initial);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 40, 140, 430));
        groupBox->setMinimumSize(QSize(140, 430));
        groupBox->setMaximumSize(QSize(140, 430));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(10);
        groupBox->setFont(font);
        currentTimeLabel = new QLabel(groupBox);
        currentTimeLabel->setObjectName(QStringLiteral("currentTimeLabel"));
        currentTimeLabel->setGeometry(QRect(20, 30, 111, 51));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 110, 61, 21));
        usernameLabel = new QLabel(groupBox);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
        usernameLabel->setGeometry(QRect(30, 130, 91, 31));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 170, 91, 21));
        lastPointnameLabel = new QLabel(groupBox);
        lastPointnameLabel->setObjectName(QStringLiteral("lastPointnameLabel"));
        lastPointnameLabel->setGeometry(QRect(30, 190, 91, 31));
        quitButton = new QPushButton(groupBox);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setGeometry(QRect(30, 370, 75, 23));
        groupBox_2 = new QGroupBox(initial);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(160, 40, 521, 431));
        groupBox_2->setFont(font);
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 180, 291, 22));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(12);
        label_4->setFont(font1);

        horizontalLayout_3->addWidget(label_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        QFont font2;
        font2.setPointSize(12);
        label_6->setFont(font2);

        horizontalLayout_3->addWidget(label_6);

        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(120, 380, 281, 22));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget1);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setFont(font2);

        horizontalLayout_4->addWidget(label_9);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        label_10 = new QLabel(layoutWidget1);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setFont(font2);

        horizontalLayout_4->addWidget(label_10);


        retranslateUi(initial);

        QMetaObject::connectSlotsByName(initial);
    } // setupUi

    void retranslateUi(QWidget *initial)
    {
        initial->setWindowTitle(QApplication::translate("initial", "initial", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("initial", "\347\224\250\346\210\267\344\277\241\346\201\257", Q_NULLPTR));
        currentTimeLabel->setText(QString());
        label->setText(QApplication::translate("initial", "\345\275\223\345\211\215\347\224\250\346\210\267\357\274\232", Q_NULLPTR));
        usernameLabel->setText(QString());
        label_3->setText(QApplication::translate("initial", "\344\270\212\346\254\241\345\255\246\344\271\240\345\210\260\357\274\232", Q_NULLPTR));
        lastPointnameLabel->setText(QString());
        quitButton->setText(QApplication::translate("initial", "\351\200\200\345\207\272\347\263\273\347\273\237", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("initial", " \347\256\241\347\220\206\346\250\241\345\235\227", Q_NULLPTR));
        label_4->setText(QApplication::translate("initial", "\347\237\245\350\257\206\345\273\272\346\236\204\345\233\276", Q_NULLPTR));
        label_6->setText(QApplication::translate("initial", "\346\225\231\345\255\246\346\250\241\345\235\227", Q_NULLPTR));
        label_9->setText(QApplication::translate("initial", "\346\265\213\350\257\225\346\250\241\345\235\227", Q_NULLPTR));
        label_10->setText(QApplication::translate("initial", "\344\270\252\344\272\272\344\277\241\346\201\257", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class initial: public Ui_initial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INITIAL_H
