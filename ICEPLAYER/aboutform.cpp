#include "aboutform.h"
#include "iceButton.h"
#include <QPushButton>
//#include <qwidgetresizehandler_p.h>
#include <QIcon>
#include <QPalette>
#include <QPixmap>
#include <QApplication>
#include <QtGui>

ICE_About_Form::ICE_About_Form(QWidget *parent /* = 0 */)
{
    exitButton = new ICE_Ice_Button(this);
    exitButton->setObjectName(QStringLiteral("exitButton"));
    exitButton->setGeometry(QRect(255, 12, 30, 30));
    QIcon icon_exit, icon_exit_focus;
    icon_exit.addFile(QStringLiteral(":/Resources/关闭按钮.png"), QSize(), QIcon::Normal, QIcon::Off);
    icon_exit_focus.addFile(QStringLiteral(":/Resources/关闭按钮2.png"), QSize(), QIcon::Normal, QIcon::Off);
    exitButton->ICE_Set_Button_Icons(icon_exit, icon_exit_focus);

    exitButton->setIconSize(QSize(20,20));
    exitButton->setFlat(true);
    exitButton->setFocusPolicy(Qt::NoFocus);
    exitButton->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");
    connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));


    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowOpacity(0.9);

    this->setFixedSize(300, 400);
    //this->setModal(true);

}

void ICE_About_Form::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0, 0 , QPixmap(":/Resources/about.png"));
}


ICE_About_Form::~ICE_About_Form()
{

}



