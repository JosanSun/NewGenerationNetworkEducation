/********************************************************************************
** Form generated from reading UI file 'knowledge.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KNOWLEDGE_H
#define UI_KNOWLEDGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_knowledge
{
public:
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QLabel *label;
    QLabel *begintimeLabel;
    QLabel *label_3;
    QLabel *domainLabel;
    QLabel *label_5;
    QLabel *scoreLabel;
    QLabel *label_2;
    QLabel *pointNameLabel;

    void setupUi(QWidget *knowledge)
    {
        if (knowledge->objectName().isEmpty())
            knowledge->setObjectName(QStringLiteral("knowledge"));
        knowledge->resize(942, 564);
        groupBox = new QGroupBox(knowledge);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(800, 10, 131, 541));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(10);
        groupBox->setFont(font);
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 400, 111, 31));
        QFont font1;
        font1.setPointSize(12);
        pushButton->setFont(font1);
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 100, 81, 21));
        label->setFont(font1);
        begintimeLabel = new QLabel(groupBox);
        begintimeLabel->setObjectName(QStringLiteral("begintimeLabel"));
        begintimeLabel->setGeometry(QRect(33, 120, 81, 51));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 180, 54, 12));
        label_3->setFont(font1);
        domainLabel = new QLabel(groupBox);
        domainLabel->setObjectName(QStringLiteral("domainLabel"));
        domainLabel->setGeometry(QRect(40, 210, 54, 21));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 270, 71, 16));
        label_5->setFont(font1);
        scoreLabel = new QLabel(groupBox);
        scoreLabel->setObjectName(QStringLiteral("scoreLabel"));
        scoreLabel->setGeometry(QRect(40, 310, 54, 21));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 30, 101, 16));
        label_2->setFont(font1);
        pointNameLabel = new QLabel(groupBox);
        pointNameLabel->setObjectName(QStringLiteral("pointNameLabel"));
        pointNameLabel->setGeometry(QRect(40, 60, 54, 21));

        retranslateUi(knowledge);

        QMetaObject::connectSlotsByName(knowledge);
    } // setupUi

    void retranslateUi(QWidget *knowledge)
    {
        knowledge->setWindowTitle(QApplication::translate("knowledge", "knowledge", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("knowledge", "\347\233\270\345\205\263\344\277\241\346\201\257", Q_NULLPTR));
        pushButton->setText(QApplication::translate("knowledge", "\350\277\275\350\270\252\345\255\246\344\271\240\350\267\257\345\276\204", Q_NULLPTR));
        label->setText(QApplication::translate("knowledge", "\345\255\246\344\271\240\346\227\266\351\227\264\357\274\232", Q_NULLPTR));
        begintimeLabel->setText(QString());
        label_3->setText(QApplication::translate("knowledge", "\351\242\206\345\237\237\357\274\232", Q_NULLPTR));
        domainLabel->setText(QString());
        label_5->setText(QApplication::translate("knowledge", "\346\265\213\350\257\225\345\276\227\345\210\206\357\274\232", Q_NULLPTR));
        scoreLabel->setText(QString());
        label_2->setText(QApplication::translate("knowledge", "\345\275\223\345\211\215\347\237\245\350\257\206\350\212\202\347\202\271\357\274\232", Q_NULLPTR));
        pointNameLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class knowledge: public Ui_knowledge {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KNOWLEDGE_H
