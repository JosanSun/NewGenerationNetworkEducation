/********************************************************************************
** Form generated from reading UI file 'attribution.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ATTRIBUTION_H
#define UI_ATTRIBUTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_attribution
{
public:
    QTabWidget *tabWidget;
    QWidget *tab1;
    QLabel *label;
    QLineEdit *idLineEdit;
    QLabel *label_2;
    QLineEdit *titleLineEdit;
    QLabel *label_3;
    QLineEdit *domainLineEdit;
    QLabel *label_4;
    QTextEdit *textEdit;
    QLabel *label_5;
    QLineEdit *qianLineEdit;
    QLabel *label_6;
    QLabel *label_7;
    QLineEdit *houLineEdit;
    QWidget *tab2;
    QLabel *label_8;
    QLabel *patternLabel;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_25;
    QLabel *label_39;
    QLabel *feature1Label;
    QLabel *feature2Label;
    QLabel *feature3Label;
    QLabel *problemLabel;
    QLabel *solutionLabel;
    QLabel *exampleLabel;
    QLabel *tipsLabel;

    void setupUi(QWidget *attribution)
    {
        if (attribution->objectName().isEmpty())
            attribution->setObjectName(QStringLiteral("attribution"));
        attribution->resize(566, 342);
        tabWidget = new QTabWidget(attribution);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 551, 331));
        tab1 = new QWidget();
        tab1->setObjectName(QStringLiteral("tab1"));
        label = new QLabel(tab1);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(12, 21, 60, 16));
        idLineEdit = new QLineEdit(tab1);
        idLineEdit->setObjectName(QStringLiteral("idLineEdit"));
        idLineEdit->setGeometry(QRect(78, 21, 111, 20));
        label_2 = new QLabel(tab1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 61, 36, 16));
        titleLineEdit = new QLineEdit(tab1);
        titleLineEdit->setObjectName(QStringLiteral("titleLineEdit"));
        titleLineEdit->setGeometry(QRect(75, 61, 111, 20));
        label_3 = new QLabel(tab1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 101, 36, 16));
        domainLineEdit = new QLineEdit(tab1);
        domainLineEdit->setObjectName(QStringLiteral("domainLineEdit"));
        domainLineEdit->setGeometry(QRect(76, 101, 111, 20));
        label_4 = new QLabel(tab1);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 150, 54, 12));
        textEdit = new QTextEdit(tab1);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(50, 150, 341, 101));
        label_5 = new QLabel(tab1);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(220, 20, 54, 12));
        qianLineEdit = new QLineEdit(tab1);
        qianLineEdit->setObjectName(QStringLiteral("qianLineEdit"));
        qianLineEdit->setGeometry(QRect(280, 60, 113, 20));
        label_6 = new QLabel(tab1);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(220, 60, 54, 12));
        label_7 = new QLabel(tab1);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(220, 100, 54, 12));
        houLineEdit = new QLineEdit(tab1);
        houLineEdit->setObjectName(QStringLiteral("houLineEdit"));
        houLineEdit->setGeometry(QRect(280, 100, 113, 20));
        tabWidget->addTab(tab1, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QStringLiteral("tab2"));
        label_8 = new QLabel(tab2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(30, 20, 31, 16));
        QFont font;
        font.setPointSize(12);
        label_8->setFont(font);
        patternLabel = new QLabel(tab2);
        patternLabel->setObjectName(QStringLiteral("patternLabel"));
        patternLabel->setGeometry(QRect(70, 20, 221, 16));
        patternLabel->setFont(font);
        label_10 = new QLabel(tab2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(40, 50, 111, 31));
        QFont font1;
        font1.setPointSize(10);
        label_10->setFont(font1);
        label_11 = new QLabel(tab2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(40, 80, 111, 31));
        label_11->setFont(font1);
        label_12 = new QLabel(tab2);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(40, 110, 111, 31));
        label_12->setFont(font1);
        label_25 = new QLabel(tab2);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(40, 200, 111, 31));
        label_25->setFont(font1);
        label_39 = new QLabel(tab2);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setGeometry(QRect(40, 230, 111, 31));
        label_39->setFont(font1);
        feature1Label = new QLabel(tab2);
        feature1Label->setObjectName(QStringLiteral("feature1Label"));
        feature1Label->setGeometry(QRect(120, 120, 241, 16));
        feature2Label = new QLabel(tab2);
        feature2Label->setObjectName(QStringLiteral("feature2Label"));
        feature2Label->setGeometry(QRect(120, 150, 291, 20));
        feature3Label = new QLabel(tab2);
        feature3Label->setObjectName(QStringLiteral("feature3Label"));
        feature3Label->setGeometry(QRect(120, 180, 421, 21));
        problemLabel = new QLabel(tab2);
        problemLabel->setObjectName(QStringLiteral("problemLabel"));
        problemLabel->setGeometry(QRect(160, 60, 231, 16));
        solutionLabel = new QLabel(tab2);
        solutionLabel->setObjectName(QStringLiteral("solutionLabel"));
        solutionLabel->setGeometry(QRect(160, 90, 231, 16));
        exampleLabel = new QLabel(tab2);
        exampleLabel->setObjectName(QStringLiteral("exampleLabel"));
        exampleLabel->setGeometry(QRect(120, 210, 241, 16));
        tipsLabel = new QLabel(tab2);
        tipsLabel->setObjectName(QStringLiteral("tipsLabel"));
        tipsLabel->setGeometry(QRect(120, 240, 241, 16));
        tabWidget->addTab(tab2, QString());

        retranslateUi(attribution);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(attribution);
    } // setupUi

    void retranslateUi(QWidget *attribution)
    {
        attribution->setWindowTitle(QApplication::translate("attribution", "attribution", Q_NULLPTR));
        label->setText(QApplication::translate("attribution", "\347\237\245\350\257\206\347\202\271ID\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("attribution", "\346\240\207\351\242\230\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("attribution", "\351\242\206\345\237\237\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("attribution", "\346\217\217\350\277\260\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("attribution", "\347\233\270\345\205\263\347\237\245\350\257\206\357\274\232", Q_NULLPTR));
        label_6->setText(QApplication::translate("attribution", "\345\211\215\351\251\261\357\274\232", Q_NULLPTR));
        label_7->setText(QApplication::translate("attribution", "\345\220\216\347\273\247\357\274\232", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab1), QApplication::translate("attribution", "Tab 1", Q_NULLPTR));
        label_8->setText(QApplication::translate("attribution", "\342\227\206", Q_NULLPTR));
        patternLabel->setText(QApplication::translate("attribution", "TextLabel", Q_NULLPTR));
        label_10->setText(QApplication::translate("attribution", "\342\227\217 \351\200\202\347\224\250\347\232\204\351\227\256\351\242\230\357\274\232", Q_NULLPTR));
        label_11->setText(QApplication::translate("attribution", "\342\227\217 \350\247\243\345\206\263\346\226\271\346\241\210\357\274\232", Q_NULLPTR));
        label_12->setText(QApplication::translate("attribution", "\342\227\217 \347\211\271\345\276\201\347\202\271\357\274\232", Q_NULLPTR));
        label_25->setText(QApplication::translate("attribution", "\342\227\217 \344\270\276\344\276\213\357\274\232", Q_NULLPTR));
        label_39->setText(QApplication::translate("attribution", "\342\227\217 \345\244\207\346\263\250\357\274\232", Q_NULLPTR));
        feature1Label->setText(QApplication::translate("attribution", "TextLabel", Q_NULLPTR));
        feature2Label->setText(QApplication::translate("attribution", "TextLabel", Q_NULLPTR));
        feature3Label->setText(QApplication::translate("attribution", "TextLabel", Q_NULLPTR));
        problemLabel->setText(QApplication::translate("attribution", "TextLabel", Q_NULLPTR));
        solutionLabel->setText(QApplication::translate("attribution", "TextLabel", Q_NULLPTR));
        exampleLabel->setText(QApplication::translate("attribution", "TextLabel", Q_NULLPTR));
        tipsLabel->setText(QApplication::translate("attribution", "TextLabel", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab2), QApplication::translate("attribution", "Tab 2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class attribution: public Ui_attribution {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ATTRIBUTION_H
