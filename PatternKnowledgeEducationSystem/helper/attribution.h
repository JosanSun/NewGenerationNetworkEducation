/*------- 知识库查看部分属性显示 --------*/
#ifndef ATTRIBUTION_H
#define ATTRIBUTION_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>

#include "ui_attribution.h"

class attribution : public QWidget
{
    Q_OBJECT

public:
    attribution(QWidget *parent = 0);
    ~attribution();

private:
    void initUI();
    void init();
    void openDatabase();
    void openXml(QString);

private:
    Ui::attribution ui;
    QSqlDatabase db;
};

#endif // ATTRIBUTION_H
