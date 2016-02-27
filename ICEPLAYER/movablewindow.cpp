#include "movablewindow.h"
#include <QMouseEvent>
#include <QPaintEvent>

movableWindow::movableWindow(QWidget *parent) : QWidget(parent)
{

}

void movableWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->m_drag = true;
        this->dragPos = event->pos();
    }
}
void movableWindow::mouseMoveEvent(QMouseEvent * event)
{
    if(m_move) {
        move(event->globalPos() - dragPos);
        return;
    }
    setCursor(Qt::ArrowCursor);
    if (m_drag && (event->buttons() & Qt::LeftButton)) {
       m_move = true;
       move(event->globalPos() - dragPos);
    }
}
void movableWindow::mouseReleaseEvent(QMouseEvent *event)
{
    m_drag = false;
    if(m_move) {
        m_move = false;
    }
    setCursor(Qt::ArrowCursor);
}

