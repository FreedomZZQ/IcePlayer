#ifndef MOVABLEWINDOW_H
#define MOVABLEWINDOW_H

#include <QObject>
#include <QWidget>

class movableWindow : public QWidget
{
    Q_OBJECT
public:
    explicit movableWindow(QWidget *parent = 0);

private:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool m_drag;
    bool m_move;
    QPoint dragPos;
};

#endif // MOVABLEWINDOW_H
