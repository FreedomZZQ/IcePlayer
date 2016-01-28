#include "icelrc.h"

ICE_Lrc::ICE_Lrc(QWidget *parent /* = 0 */)
:QWidget(parent)
{
	lrcLabel = NULL;

	//无边界的窗口,总在最上
	setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
	//去除窗体原背景
	setAttribute(Qt::WA_TranslucentBackground);
	//窗口拖动
	QWidgetResizeHandler *movewin = new QWidgetResizeHandler(this);
	movewin->setMovingEnabled(true);
	//固定大小
	this->setFixedSize(800, 80);

	lrcLabel = new ICE_Lrc_Label(this);
	lrcLabel->setGeometry(QRect(0, 6, 800, 60));
}

ICE_Lrc::~ICE_Lrc()
{
	if (lrcLabel != NULL)
		delete lrcLabel;
}

void ICE_Lrc::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	p.drawPixmap(0, 0, QPixmap(":/IcePlayer/Resources/lrc_background.png"));
}

void ICE_Lrc::ICE_Start_Lrc_Mask(qint64 intervaltime)
{
	lrcLabel->ICE_Start_Lrc_Mask(intervaltime);
}

void ICE_Lrc::ICE_Stop_Lrc_Mask()
{
	lrcLabel->ICE_Stop_Lrc_Mask();
}

QString ICE_Lrc::text() const
{
	return lrcLabel->text();
}

void ICE_Lrc::setText(QString &t)
{
	//if (t.size() > 35){
	//	lrcLabel->ICE_Set_Size(25);
	//	lrcLabel->setText(t);
	//}
	//else{
	//	lrcLabel->ICE_Set_Size(30);
	//	lrcLabel->setText(t);
	//}

	lrcLabel->setText(t);
}