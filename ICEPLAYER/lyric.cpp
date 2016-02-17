#include "lyric.h"

ICE_Lrc_Label::ICE_Lrc_Label(QWidget *parent) : IceLabel(parent)
{
    //setAttribute(Qt::WA_TranslucentBackground);
    setText(QString::fromLocal8Bit("冰点播放器"));
    //setAlignment(Qt::AlignCenter);
    // �̶���ʾ������С
    //setMaximumSize(800, 80);
// 	setMinimumSize(800, 80);

    //���ʵ����Խ�������
    linearGradient.setStart(0, 10);//��������������
    linearGradient.setFinalStop(0, 40);//�������յ�����
    //��һ�������յ����꣬�����������������������ԣ����ձ������м���
    /*linearGradient.setColorAt(0.1, QColor(14, 179, 255));
    linearGradient.setColorAt(0.5, QColor(114, 232, 255));
    linearGradient.setColorAt(0.9, QColor(14, 179, 255));
    linearGradient.setColorAt(0, QColor(14, 179, 230));*/
    linearGradient.setColorAt(0, QColor(1, 150, 255));

    // ���ֵ����Խ�������
// 	maskLinearGradient.setStart(0, 10);
// 	maskLinearGradient.setFinalStop(0, 40);
// 	maskLinearGradient.setColorAt(0.1, QColor(222, 54, 4));
// 	maskLinearGradient.setColorAt(0.5, QColor(255, 72, 16));
// 	maskLinearGradient.setColorAt(0.9, QColor(222, 54, 4));
// 	maskLinearGradient.setColorAt(0, QColor(0, 150, 255));
    // ��������
    lrcFont.setFamily(QString::fromLocal8Bit("Helvetica [Cronyx]"));
    //lrcFont.setBold(true);
    lrcFont.setPointSize(25);

    // ���ö�ʱ��
// 	lrcTimer = new QTimer(this);
// 	connect(lrcTimer, SIGNAL(ice_time_out()), this, SLOT(ice_time_out()));
// 	lrcMaskWidth = 0;
// 	lrcMaskWidthInterval = 0;
}

// �������֣���Ҫָ����ǰ���ʿ�ʼ������֮����ʱ������
void ICE_Lrc_Label::ICE_Start_Lrc_Mask(qint64 intervaltime)
{
    // ��������ÿ��30��������һ�����ֵĿ��ȣ���Ϊ��������̫Ƶ��
    // ������CPUռ���ʣ�������ʱ������̫�����򶯻�Ч���Ͳ�������
/*	qreal count = intervaltime / 30;*/
    // ��ȡ����ÿ����Ҫ���ӵĿ��ȣ�������800�ǲ����Ĺ̶�����
// 	lrcMaskWidthInterval = 800 / count;
// 	lrcMaskWidth = 0;
// 	lrcTimer->start(30);
}

void ICE_Lrc_Label::ICE_Stop_Lrc_Mask()
{
// 	lrcTimer->stop();
// 	lrcMaskWidth = 0;
    update();
}

void ICE_Lrc_Label::paintEvent(QPaintEvent *)
{

    QPainter painter(this);
    painter.setFont(lrcFont);

    if(text().size() < 2){
        setText("Music...");
    }
    QString tmp = text();
    tmp.toUtf8();
    // �Ȼ��Ƶײ����֣���Ϊ��Ӱ��������ʹ��ʾЧ�������������Ҹ����ʸ�
    painter.setPen(QColor(90, 105, 115, 200));
    painter.drawText(1, 1, 800, 60, Qt::AlignCenter, tmp);

    // ����������������
    painter.setPen(QPen(linearGradient, 0));
    painter.drawText(0, 0, 800, 60, Qt::AlignCenter, tmp);

    // ���ø�������
// 	painter.setPen(QPen(maskLinearGradient, 0));
// 	painter.drawText(0, 0, lrcMaskWidth, 60, Qt::AlignCenter, tmp);

}

// ��������
// void ICE_Lrc_Label::mousePressEvent(QMouseEvent *event)
// {
// 	if (event->button() == Qt::LeftButton)
// 		offSet = event->globalPos() - frameGeometry().topLeft();
// }
//
//
// void ICE_Lrc_Label::mouseMoveEvent(QMouseEvent *event)
// {
// 	//�ƶ����굽������ʱ������ʾ����
// 	//event->buttons()�����������������ͣ���Ϊ�������л����һ�
// 	//��������������ʾ������
// 	if (event->buttons() & Qt::LeftButton) {
// 		setCursor(Qt::PointingHandCursor);
// 		//ʵ���ƶ�����
// 		move(event->globalPos() - offSet);
// 	}
// }

//�һ��¼�
void ICE_Lrc_Label::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    menu.addAction(QString::fromLocal8Bit("unknown Act"), this->parent(), SLOT(hide()));
    menu.exec(event->globalPos());//globalPos()Ϊ��ǰ������λ������
}


void ICE_Lrc_Label::ice_time_out()
{

    //ÿ��һ�ι̶���ʱ�����ֵĳ��Ⱦ�����һ��
    //lrcMaskWidth += lrcMaskWidthInterval;
    update();//����widget�����ǲ��������ػ棬���ǰ���һ��Paint�¼�����������ѭ��ʱ��ϵͳ���ػ�
}


void ICE_Lrc_Label::ICE_Set_Size(int size)
{
    lrcFont.setPointSize(size);
}
