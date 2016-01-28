#ifndef ICEVOLBUTTON_H
#define ICEVOLBUTTON_H

#include "iceButton.h"
#include <QtWidgets>

class ICE_Vol_Button : public QWidget
{
	Q_OBJECT
	Q_PROPERTY(int ICE_Get_Volume READ ICE_Get_Volume WRITE ICE_Set_Volume NOTIFY ICE_Volume_Changed)

public:
	ICE_Vol_Button(QWidget *parent = 0); 

	//返回音量值（0~100）
	int ICE_Get_Volume() const; 

	//设置音量条是否可见
	void ICE_Set_Slider_Visiable(bool);

public slots:

	//点击音量条使音量增加一部分	
	void ICE_Increase_Volume(); 

	//点击音量条使音量减少一部分
	void ICE_Descrease_Volume(); 

	//设置音量
	void ICE_Set_Volume(int volume); 

	//按钮单击事件，弹出菜单
	void ICE_Button_Clicked(); 

signals:

	//音量改变信号（当音量条被拖动时发射）
	void ICE_Volume_Changed(int volume); 

private:
	ICE_Ice_Button *button;
	QSlider *slider;
	QMenu *menu;
	QWidgetAction *action;
};

#endif 