/********************************************************************************
** Form generated from reading UI file 'administrate.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINISTRATE_H
#define UI_ADMINISTRATE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_administrate
{
public:
    QGroupBox *groupBox_4;
    QLabel *label_3;
    QLabel *usernameLabel;
    QLabel *currentTimeLabel;
    QLabel *label_4;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *usernameLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *passwordLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QComboBox *sexComboBox;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QLineEdit *ageLineEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_7;
    QComboBox *educationComboBox;
    QGroupBox *groupBox_2;
    QTabWidget *tabWidget;
    QGroupBox *groupBox_3;
    QPushButton *modifyButton;
    QPushButton *saveButton;
    QPushButton *quitButton;

    void setupUi(QWidget *administrate)
    {
        if (administrate->objectName().isEmpty())
            administrate->setObjectName(QStringLiteral("administrate"));
        administrate->resize(764, 584);
        administrate->setMinimumSize(QSize(764, 584));
        administrate->setMaximumSize(QSize(764, 584));
        groupBox_4 = new QGroupBox(administrate);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 60, 171, 191));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(10);
        groupBox_4->setFont(font);
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 100, 111, 21));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        label_3->setFont(font1);
        usernameLabel = new QLabel(groupBox_4);
        usernameLabel->setObjectName(QStringLiteral("usernameLabel"));
        usernameLabel->setGeometry(QRect(20, 130, 71, 16));
        usernameLabel->setFont(font1);
        currentTimeLabel = new QLabel(groupBox_4);
        currentTimeLabel->setObjectName(QStringLiteral("currentTimeLabel"));
        currentTimeLabel->setGeometry(QRect(10, 30, 111, 51));
        currentTimeLabel->setFont(font1);
        label_4 = new QLabel(administrate);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(150, 10, 231, 31));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font2.setPointSize(20);
        label_4->setFont(font2);
        groupBox = new QGroupBox(administrate);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(190, 60, 561, 171));
        groupBox->setFont(font);
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 31, 212, 141));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setFont(font1);

        horizontalLayout->addWidget(label);

        usernameLineEdit = new QLineEdit(layoutWidget);
        usernameLineEdit->setObjectName(QStringLiteral("usernameLineEdit"));

        horizontalLayout->addWidget(usernameLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font1);

        horizontalLayout_2->addWidget(label_2);

        passwordLineEdit = new QLineEdit(layoutWidget);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));

        horizontalLayout_2->addWidget(passwordLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font1);

        horizontalLayout_3->addWidget(label_5);

        sexComboBox = new QComboBox(layoutWidget);
        sexComboBox->setObjectName(QStringLiteral("sexComboBox"));
        sexComboBox->setFont(font1);

        horizontalLayout_3->addWidget(sexComboBox);


        verticalLayout->addLayout(horizontalLayout_3);

        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(293, 31, 199, 91));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font1);

        horizontalLayout_4->addWidget(label_6);

        ageLineEdit = new QLineEdit(layoutWidget1);
        ageLineEdit->setObjectName(QStringLiteral("ageLineEdit"));

        horizontalLayout_4->addWidget(ageLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font1);

        horizontalLayout_5->addWidget(label_7);

        educationComboBox = new QComboBox(layoutWidget1);
        educationComboBox->setObjectName(QStringLiteral("educationComboBox"));
        educationComboBox->setFont(font1);

        horizontalLayout_5->addWidget(educationComboBox);


        verticalLayout_2->addLayout(horizontalLayout_5);

        groupBox_2 = new QGroupBox(administrate);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(190, 230, 561, 341));
        groupBox_2->setFont(font);
        tabWidget = new QTabWidget(groupBox_2);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 20, 541, 311));
        groupBox_3 = new QGroupBox(administrate);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 260, 171, 311));
        groupBox_3->setFont(font);
        modifyButton = new QPushButton(groupBox_3);
        modifyButton->setObjectName(QStringLiteral("modifyButton"));
        modifyButton->setGeometry(QRect(30, 80, 111, 31));
        QFont font3;
        font3.setPointSize(10);
        modifyButton->setFont(font3);
        saveButton = new QPushButton(groupBox_3);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setGeometry(QRect(30, 140, 111, 31));
        saveButton->setFont(font3);
        quitButton = new QPushButton(groupBox_3);
        quitButton->setObjectName(QStringLiteral("quitButton"));
        quitButton->setGeometry(QRect(30, 200, 111, 31));
        quitButton->setFont(font3);

        retranslateUi(administrate);

        tabWidget->setCurrentIndex(-1);


        QMetaObject::connectSlotsByName(administrate);
    } // setupUi

    void retranslateUi(QWidget *administrate)
    {
        administrate->setWindowTitle(QApplication::translate("administrate", "administrate", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("administrate", "\345\237\272\346\234\254\344\277\241\346\201\257", Q_NULLPTR));
        label_3->setText(QApplication::translate("administrate", "\345\275\223\345\211\215\347\224\250\346\210\267\357\274\232", Q_NULLPTR));
        usernameLabel->setText(QString());
        currentTimeLabel->setText(QApplication::translate("administrate", "text", Q_NULLPTR));
        label_4->setText(QApplication::translate("administrate", "\345\234\250\347\272\277\347\275\221\347\273\234\346\225\231\345\255\246\347\263\273\347\273\237", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("administrate", "\347\224\250\346\210\267\344\270\252\344\272\272\344\277\241\346\201\257", Q_NULLPTR));
        label->setText(QApplication::translate("administrate", "\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        label_2->setText(QApplication::translate("administrate", "\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("administrate", "\346\200\247\345\210\253\357\274\232", Q_NULLPTR));
        sexComboBox->clear();
        sexComboBox->insertItems(0, QStringList()
         << QApplication::translate("administrate", "\347\224\267", Q_NULLPTR)
         << QApplication::translate("administrate", "\345\245\263", Q_NULLPTR)
        );
        label_6->setText(QApplication::translate("administrate", "\345\271\264\351\276\204\357\274\232", Q_NULLPTR));
        label_7->setText(QApplication::translate("administrate", "\345\217\227\346\225\231\350\202\262\347\250\213\345\272\246\357\274\232", Q_NULLPTR));
        educationComboBox->clear();
        educationComboBox->insertItems(0, QStringList()
         << QApplication::translate("administrate", "\350\257\267\351\200\211\346\213\251", Q_NULLPTR)
         << QApplication::translate("administrate", "\345\215\232\345\243\253\345\220\216", Q_NULLPTR)
         << QApplication::translate("administrate", "\345\215\232\345\243\253", Q_NULLPTR)
         << QApplication::translate("administrate", "\347\241\225\345\243\253", Q_NULLPTR)
         << QApplication::translate("administrate", "\346\234\254\347\247\221", Q_NULLPTR)
         << QApplication::translate("administrate", "\345\244\247\344\270\223", Q_NULLPTR)
         << QApplication::translate("administrate", "\351\253\230\344\270\255", Q_NULLPTR)
         << QApplication::translate("administrate", "\344\270\255\344\270\223", Q_NULLPTR)
         << QApplication::translate("administrate", "\345\210\235\344\270\255", Q_NULLPTR)
         << QApplication::translate("administrate", "\345\260\217\345\255\246", Q_NULLPTR)
         << QApplication::translate("administrate", "\345\260\217\345\255\246\344\273\245\344\270\213", Q_NULLPTR)
        );
        groupBox_2->setTitle(QApplication::translate("administrate", "\347\224\250\346\210\267\345\255\246\344\271\240\350\256\260\345\275\225", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("administrate", "\347\224\250\346\210\267\347\256\241\347\220\206", Q_NULLPTR));
        modifyButton->setText(QApplication::translate("administrate", "\344\277\256\346\224\271\347\224\250\346\210\267\344\277\241\346\201\257", Q_NULLPTR));
        saveButton->setText(QApplication::translate("administrate", "\344\277\235\345\255\230\347\224\250\346\210\267\344\277\241\346\201\257", Q_NULLPTR));
        quitButton->setText(QApplication::translate("administrate", "\351\200\200\345\207\272\347\224\250\346\210\267\347\256\241\347\220\206", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class administrate: public Ui_administrate {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINISTRATE_H
