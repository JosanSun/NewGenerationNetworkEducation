/*------- 知识库查看部分属性显示 --------*/
#ifndef ATTRIBUTION_H
#define ATTRIBUTION_H

#include <QWidget>
#include <QtSql>
#include <QSqlDatabase>

namespace Ui {
class Attribution;
}

class Attribution : public QWidget
{
    Q_OBJECT

public:
    Attribution(QWidget *parent = 0);
    ~Attribution();

private:
    void initUI();
    void init();
    void openDatabase();
    void openXml(QString);

private:
    Ui::Attribution* ui;
    QSqlDatabase db;
};

#endif // ATTRIBUTION_H
