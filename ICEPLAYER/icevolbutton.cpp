#include "icevolbutton.h"

ICE_Vol_Button::ICE_Vol_Button(QWidget *parent) :QWidget(parent)
{
	//setWindowFlags(Qt::FramelessWindowHint);
	//setAttribute(Qt::WA_TranslucentBackground);

	slider = new QSlider(Qt::Horizontal, this);
	slider->setRange(0, 100);
	slider->setGeometry(QRect(26,0,75,25));

	//当音量条被拖动时发射音量改变的信号
	connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(ICE_Volume_Changed(int)));

	slider->setStyleSheet("QSlider::groove:horizontal{border:0px;height:4px;}"  
		"QSlider::sub-page:horizontal{background:#0096ff;}"  
		"QSlider::add-page:horizontal{background:lightgray;} "
		"QSlider::handle:horizontal{background:white;width:10px;border:#51b5fb 10px;border-radius:5px;margin:-3px 0px -3px 0px;}");
		
	//slider->setVisible(false);
	

	button = new ICE_Ice_Button(this);

	QIcon icon_button, icon_button_focus;
	icon_button.addFile(QStringLiteral(":/IcePlayer/Resources/音量调节.png"), QSize(), QIcon::Normal, QIcon::Off);
	icon_button_focus.addFile(QStringLiteral(":/IcePlayer/Resources/音量调节2.png"), QSize(), QIcon::Normal, QIcon::Off);
	button->ICE_Set_Button_Icons(icon_button, icon_button_focus);

	button->setIconSize(QSize(25,25));
	button->setFlat(true);
	button->setFocusPolicy(Qt::NoFocus);
	button->setStyleSheet("QPushButton{background-color:rgba(255,255,255,0);border-style:solid;border-width:0px;border-color:rgba(255,255,255,0);}");
	button->setGeometry(QRect(0,0,25,25));

	connect(button, SIGNAL(clicked()), this, SLOT(ICE_Button_Clicked()));

	menu = new QMenu(this);

	action = new QWidgetAction(this);
	action->setDefaultWidget(slider);
	menu->addAction(action);
	/*menu->setStyleSheet(
		"QMenu{padding:1px;background:transparent;border:1px transparent;}"
		"QMenu::item{padding:0px 20px 0px 30px;height:25px;}"
		"QMenu::item:selected:enabled{background:transparent;color:transparent;}"
		"QMenu::item:selected:!enabled{background:transparent;}");*/

}

void ICE_Vol_Button::ICE_Set_Slider_Visiable(bool a)
{
	slider->setVisible(a);
}

void ICE_Vol_Button::ICE_Button_Clicked()
{
	menu->exec(QCursor::pos());
}

void ICE_Vol_Button::ICE_Increase_Volume()
{
	slider->triggerAction(QSlider::SliderPageStepAdd);
}

void ICE_Vol_Button::ICE_Descrease_Volume()
{
	slider->triggerAction(QSlider::SliderPageStepSub);
}

int ICE_Vol_Button::ICE_Get_Volume() const
{
	return slider->value();
}

void ICE_Vol_Button::ICE_Set_Volume(int volume)
{
	slider->setValue(volume);
}


	  