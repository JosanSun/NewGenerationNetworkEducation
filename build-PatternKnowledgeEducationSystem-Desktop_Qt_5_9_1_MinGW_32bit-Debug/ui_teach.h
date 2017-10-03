/********************************************************************************
** Form generated from reading UI file 'teach.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEACH_H
#define UI_TEACH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_teach
{
public:
    QLabel *label;
    QGroupBox *groupBox_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_8;
    QTextBrowser *descriptionTextBrowser;
    QGroupBox *groupBox_3;
    QLabel *label_2;
    QLabel *usernameLabel;
    QLabel *label_6;
    QLabel *pointnameLabel;
    QLabel *currentTimeLabel;
    QTabWidget *tabWidget;
    QGroupBox *groupBox_4;
    QPushButton *playAgainButton;
    QPushButton *changeCaseButton;
    QPushButton *beginTestButton;
    QPushButton *quitButton;
    QPushButton *discussionButton;

    void setupUi(QWidget *teach)
    {
        if (teach->objectName().isEmpty())
            teach->setObjectName(QStringLiteral("teach"));
        teach->resize(870, 730);
        teach->setMinimumSize(QSize(870, 730));
        teach->setMaximumSize(QSize(870, 730));
        label = new QLabel(teach);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(150, 20, 231, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(20);
        label->setFont(font);
        groupBox_2 = new QGroupBox(teach);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(150, 70, 711, 381));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(10);
        groupBox_2->setFont(font1);
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 30, 81, 20));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        label_3->setFont(font2);
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 230, 51, 16));
        label_4->setFont(font2);
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 270, 71, 16));
        label_5->setFont(font2);
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 310, 71, 16));
        label_7->setFont(font2);
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(30, 350, 71, 16));
        label_8->setFont(font2);
        descriptionTextBrowser = new QTextBrowser(groupBox_2);
        descriptionTextBrowser->setObjectName(QStringLiteral("descriptionTextBrowser"));
        descriptionTextBrowser->setGeometry(QRect(110, 30, 571, 171));
        groupBox_3 = new QGroupBox(teach);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 70, 131, 271));
        groupBox_3->setFont(font1);
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 100, 111, 21));
        label_2->setFont(font2);
        usernameLabel = new QLabel(groupBox_3);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
        usernameLabel->setGeometry(QRect(20, 130, 71, 16));
        usernameLabel->setFont(font2);
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 180, 111, 21));
        label_6->setFont(font2);
        pointnameLabel = new QLabel(groupBox_3);
        pointnameLabel->setObjectName(QStringLiteral("pointnameLabel"));
        pointnameLabel->setGeometry(QRect(20, 210, 71, 16));
        pointnameLabel->setFont(font2);
        currentTimeLabel = new QLabel(groupBox_3);
        currentTimeLabel->setObjectName(QStringLiteral("currentTimeLabel"));
        currentTimeLabel->setGeometry(QRect(10, 30, 111, 51));
        currentTimeLabel->setFont(font2);
        tabWidget = new QTabWidget(teach);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(150, 460, 711, 261));
        groupBox_4 = new QGroupBox(teach);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 350, 131, 371));
        groupBox_4->setFont(font1);
        playAgainButton = new QPushButton(groupBox_4);
        playAgainButton->setObjectName(QStringLiteral("playAgainButton"));
        playAgainButton->setGeometry(QRect(30, 40, 75, 23));
        changeCaseButton = new QPushButton(groupBox_4);
        changeCaseButton->setObjectName(QStringLiteral("changeCaseButton"));
        changeCaseButton->setGeometry(QRect(30, 80, 75, 23));
        beginTestButton = new QPushButton(groupBox_4);
        beginTestButton->setObjectName(QStringLiteral("beginTestButton"));
        beginTestButton->setGeometry(QRect(30, 160, 75, 23));
        quitButton = new QPushButton(groupBox_4);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setGeometry(QRect(30, 200, 75, 23));
        discussionButton = new QPushButton(groupBox_4);
        discussionButton->setObjectName(QStringLiteral("discussionButton"));
        discussionButton->setGeometry(QRect(30, 120, 75, 23));

        retranslateUi(teach);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(teach);
    } // setupUi

    void retranslateUi(QWidget *teach)
    {
        teach->setWindowTitle(QApplication::translate("teach", "teach", Q_NULLPTR));
        label->setText(QApplication::translate("teach", "\345\234\250\347\272\277\347\275\221\347\273\234\346\225\231\345\255\246\347\263\273\347\273\237", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("teach", "\346\225\231\345\255\246\346\250\241\345\235\227", Q_NULLPTR));
        label_3->setText(QApplication::translate("teach", "\347\237\245\350\257\206\347\202\271\346\217\217\350\277\260\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("teach", "\351\242\206\345\237\237\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("teach", "\346\241\210\344\276\213\357\274\232", Q_NULLPTR));
        label_7->setText(QApplication::translate("teach", "\345\211\215\351\251\261\347\237\245\350\257\206\357\274\232", Q_NULLPTR));
        label_8->setText(QApplication::translate("teach", "\345\220\216\347\273\247\347\237\245\350\257\206\357\274\232", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("teach", "\345\237\272\346\234\254\344\277\241\346\201\257", Q_NULLPTR));
        label_2->setText(QApplication::translate("teach", "\345\275\223\345\211\215\347\224\250\346\210\267\357\274\232", Q_NULLPTR));
        usernameLabel->setText(QString());
        label_6->setText(QApplication::translate("teach", "\345\275\223\345\211\215\345\255\246\344\271\240\347\237\245\350\257\206\347\202\271\357\274\232", Q_NULLPTR));
        pointnameLabel->setText(QString());
        currentTimeLabel->setText(QApplication::translate("teach", "text", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("teach", "\346\225\231\345\255\246\347\233\270\345\205\263", Q_NULLPTR));
        playAgainButton->setText(QApplication::translate("teach", "\351\207\215\346\226\260\346\222\255\346\224\276", Q_NULLPTR));
        changeCaseButton->setText(QApplication::translate("teach", "\346\233\264\346\215\242\346\241\210\344\276\213", Q_NULLPTR));
        beginTestButton->setText(QApplication::translate("teach", "\345\274\200\345\247\213\346\265\213\350\257\225", Q_NULLPTR));
        quitButton->setText(QApplication::translate("teach", "\351\200\200\345\207\272\346\225\231\345\255\246", Q_NULLPTR));
        discussionButton->setText(QApplication::translate("teach", "\350\256\250\350\256\272\345\214\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class teach: public Ui_teach {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEACH_H
