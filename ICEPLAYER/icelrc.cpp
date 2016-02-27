#include "icelrc.h"

ICE_Lrc::ICE_Lrc(movableWindow *parent /* = 0 */)
:movableWindow(parent)
{
    lrcLabel = NULL;

    //�ޱ߽��Ĵ���,��������
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(800, 80);

    lrcLabel = new ICE_Lrc_Label(this);
    lrcLabel->setGeometry(QRect(0, 6, 800, 60));
}

ICE_Lrc::~ICE_Lrc()
{
 //   if (lrcLabel != NULL)
//        delete lrcLabel;
}

void ICE_Lrc::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0, 0, QPixmap(":/Resources/lrc_background.png"));
}

void ICE_Lrc::ICE_Start_Lrc_Mask(qint64 intervaltime)
{
  //  lrcLabel->ICE_Start_Lrc_Mask(intervaltime);
}

void ICE_Lrc::ICE_Stop_Lrc_Mask()
{
//    lrcLabel->ICE_Stop_Lrc_Mask();
}

QString ICE_Lrc::text() const
{
//    return lrcLabel->text();
}

void ICE_Lrc::setText(QString /*&*/t)
{
    //if (t.size() > 35){
    //	lrcLabel->ICE_Set_Size(25);
    //	lrcLabel->setText(t);
    //}
    //else{
    //	lrcLabel->ICE_Set_Size(30);
    //	lrcLabel->setText(t);
    //}

//    lrcLabel->setText(t);
}
