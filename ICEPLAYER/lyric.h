#ifndef LYRIC_H
#define LYRIC_H

#include <QtWidgets>
#include "icelabel.h"

class ICE_Lrc_Label : public IceLabel{

	Q_OBJECT

public:

	explicit ICE_Lrc_Label(QWidget *parent = 0);

	//开始歌词遮罩
	void ICE_Start_Lrc_Mask(qint64 intervaltime);

	//停止歌词遮罩
	void ICE_Stop_Lrc_Mask();

	//调整字体大小
	void ICE_Set_Size(int size);

protected:

	//绘制窗体
	void paintEvent(QPaintEvent *);

	//鼠标事件
	//void mousePressEvent(QMouseEvent *event);
	//void mouseMoveEvent(QMouseEvent *event);

	//菜单事件
	void contextMenuEvent(QContextMenuEvent *event);

private slots:

	void ice_time_out();

private:

	QLinearGradient linearGradient;
	QLinearGradient maskLinearGradient;
	QFont lrcFont;
	QTimer *lrcTimer;
	qreal lrcMaskWidth;
	qreal lrcMaskWidthInterval;
	QPoint offSet;
};

#endif