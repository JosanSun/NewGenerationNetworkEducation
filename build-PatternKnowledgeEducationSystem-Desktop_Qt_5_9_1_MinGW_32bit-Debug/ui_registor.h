/********************************************************************************
** Form generated from reading UI file 'registor.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTOR_H
#define UI_REGISTOR_H

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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_registor
{
public:
    QLabel *label;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *usernameLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *ageLineEdit;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QVBoxLayout *verticalLayout_4;
    QComboBox *sexComboBox;
    QLineEdit *doublePasswordLineEdit;
    QComboBox *educationComboBox;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *registerButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cancelButton;

    void setupUi(QWidget *registor)
    {
        if (registor->objectName().isEmpty())
            registor->setObjectName(QStringLiteral("registor"));
        registor->resize(600, 388);
        registor->setMinimumSize(QSize(600, 388));
        registor->setMaximumSize(QSize(600, 388));
        label = new QLabel(registor);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(240, 30, 81, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(15);
        label->setFont(font);
        groupBox = new QGroupBox(registor);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(40, 80, 521, 201));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(10);
        groupBox->setFont(font1);
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(23, 30, 471, 151));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font2;
        font2.setPointSize(12);
        label_2->setFont(font2);

        verticalLayout->addWidget(label_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setFont(font2);

        verticalLayout->addWidget(label_3);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setFont(font2);

        verticalLayout->addWidget(label_4);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        usernameLineEdit = new QLineEdit(layoutWidget);
        usernameLineEdit->setObjectName(QStringLiteral("usernameLineEdit"));

        verticalLayout_2->addWidget(usernameLineEdit);

        passwordLineEdit = new QLineEdit(layoutWidget);
        passwordLineEdit->setObjectName(QStringLiteral("passwordLineEdit"));

        verticalLayout_2->addWidget(passwordLineEdit);

        ageLineEdit = new QLineEdit(layoutWidget);
        ageLineEdit->setObjectName(QStringLiteral("ageLineEdit"));

        verticalLayout_2->addWidget(ageLineEdit);


        horizontalLayout->addLayout(verticalLayout_2);


        horizontalLayout_3->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setFont(font2);

        verticalLayout_3->addWidget(label_5);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setFont(font2);

        verticalLayout_3->addWidget(label_6);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setFont(font2);

        verticalLayout_3->addWidget(label_7);


        horizontalLayout_2->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        sexComboBox = new QComboBox(layoutWidget);
        sexComboBox->setObjectName(QStringLiteral("sexComboBox"));

        verticalLayout_4->addWidget(sexComboBox);

        doublePasswordLineEdit = new QLineEdit(layoutWidget);
        doublePasswordLineEdit->setObjectName(QStringLiteral("doublePasswordLineEdit"));

        verticalLayout_4->addWidget(doublePasswordLineEdit);

        educationComboBox = new QComboBox(layoutWidget);
        educationComboBox->setObjectName(QStringLiteral("educationComboBox"));

        verticalLayout_4->addWidget(educationComboBox);


        horizontalLayout_2->addLayout(verticalLayout_4);


        horizontalLayout_3->addLayout(horizontalLayout_2);

        layoutWidget1 = new QWidget(registor);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(140, 310, 321, 26));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        registerButton = new QPushButton(layoutWidget1);
        registerButton->setObjectName(QStringLiteral("registerButton"));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font3.setPointSize(12);
        registerButton->setFont(font3);

        horizontalLayout_4->addWidget(registerButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        cancelButton = new QPushButton(layoutWidget1);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setFont(font3);

        horizontalLayout_4->addWidget(cancelButton);


        retranslateUi(registor);

        QMetaObject::connectSlotsByName(registor);
    } // setupUi

    void retranslateUi(QWidget *registor)
    {
        registor->setWindowTitle(QApplication::translate("registor", "registor", Q_NULLPTR));
        label->setText(QApplication::translate("registor", "\347\224\250\346\210\267\346\263\250\345\206\214", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("registor", "\345\237\272\346\234\254\344\277\241\346\201\257", Q_NULLPTR));
        label_2->setText(QApplication::translate("registor", "\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        label_3->setText(QApplication::translate("registor", "\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        label_4->setText(QApplication::translate("registor", "\345\271\264\351\276\204\357\274\232", Q_NULLPTR));
        label_5->setText(QApplication::translate("registor", "\346\200\247\345\210\253\357\274\232", Q_NULLPTR));
        label_6->setText(QApplication::translate("registor", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        label_7->setText(QApplication::translate("registor", "\346\225\231\350\202\262\347\250\213\345\272\246\357\274\232", Q_NULLPTR));
        sexComboBox->clear();
        sexComboBox->insertItems(0, QStringList()
         << QApplication::translate("registor", "\347\224\267", Q_NULLPTR)
         << QApplication::translate("registor", "\345\245\263", Q_NULLPTR)
        );
        educationComboBox->clear();
        educationComboBox->insertItems(0, QStringList()
         << QApplication::translate("registor", "\350\257\267\351\200\211\346\213\251", Q_NULLPTR)
         << QApplication::translate("registor", "\345\215\232\345\243\253\345\220\216", Q_NULLPTR)
         << QApplication::translate("registor", "\345\215\232\345\243\253", Q_NULLPTR)
         << QApplication::translate("registor", "\347\241\225\345\243\253", Q_NULLPTR)
         << QApplication::translate("registor", "\346\234\254\347\247\221", Q_NULLPTR)
         << QApplication::translate("registor", "\345\244\247\344\270\223", Q_NULLPTR)
         << QApplication::translate("registor", "\351\253\230\344\270\255", Q_NULLPTR)
         << QApplication::translate("registor", "\344\270\255\344\270\223", Q_NULLPTR)
         << QApplication::translate("registor", "\345\210\235\344\270\255", Q_NULLPTR)
         << QApplication::translate("registor", "\345\260\217\345\255\246", Q_NULLPTR)
         << QApplication::translate("registor", "\345\260\217\345\255\246\344\273\245\344\270\213", Q_NULLPTR)
        );
        registerButton->setText(QApplication::translate("registor", "\346\263\250\345\206\214", Q_NULLPTR));
        cancelButton->setText(QApplication::translate("registor", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class registor: public Ui_registor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTOR_H
