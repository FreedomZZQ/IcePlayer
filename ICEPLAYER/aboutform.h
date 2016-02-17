#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
//#include <qwidgetresizehandler_p.h>
#include "iceButton.h"
#include "movablewindow.h"
class ICE_Ice_Button;

class ICE_About_Form : public movableWindow
{
    Q_OBJECT
public:
    ICE_About_Form(QWidget *parent = 0);
    ~ICE_About_Form();

private:

    //���Ʊ���ͼƬ
    void paintEvent(QPaintEvent *event);
   // void mousePressEvent(QMouseEvent *event);
   // void mouseMoveEvent(QMouseEvent *event);
   // void mouseReleaseEvent(QMouseEvent *event);

   // bool m_drag;
   // bool m_move;
  //  QPoint dragPos;
  //  QRect mouseDownRect;
    ICE_Ice_Button *exitButton;
};


#endif
