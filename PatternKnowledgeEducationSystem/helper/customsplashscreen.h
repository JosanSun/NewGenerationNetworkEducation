#ifndef CUSTOMSPLASHSCREEN_H
#define CUSTOMSPLASHSCREEN_H

#include <QSplashScreen>
#include <QPainter>

class customSplashScreen : public QSplashScreen
{
public:
    customSplashScreen(const QPixmap& pixmap);
    ~customSplashScreen();
    virtual void drawContents(QPainter *painter);
    void showStatusMessage(const QString &message, const QColor &color = Qt::black);
    void setMessageRect(QRect rect, int alignment = Qt::AlignLeft);
private:
    QString message;
    int alignement;
    QColor color;
    QRect rect;
};

#endif // CUSTOMSPLASHSCREEN_H
