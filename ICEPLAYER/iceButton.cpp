#include "iceButton.h"

ICE_Ice_Button::ICE_Ice_Button(QWidget *parent)  
	: QPushButton(parent)  
{  
	//setDown(false);  

	//设置图标无焦点
	setFocusPolicy(Qt::NoFocus);  

	//QWidgetResizeHandler *movewin = new QWidgetResizeHandler(this);
	//movewin->setMovingEnabled(true);
}  

ICE_Ice_Button::~ICE_Ice_Button()  
{  

}  

void ICE_Ice_Button::enterEvent(QEvent *event)  
{  
	if( isEnabled() && !focusIcon.isNull() )  
		setIcon(focusIcon);  
}  

void ICE_Ice_Button::leaveEvent(QEvent *event)  
{  
	if( isEnabled() )  
		setIcon(normalIcon);  
}  


void ICE_Ice_Button::mousePressEvent(QMouseEvent *event)  
{  
	if( isEnabled() && !pressedIcon.isNull() )  
		setIcon(pressedIcon);  
	QPushButton::mousePressEvent(event);  
}  

void ICE_Ice_Button::mouseReleaseEvent(QMouseEvent *event)  
{  
	if( isEnabled() && focusIcon.isNull() )  
		setIcon(focusIcon);  
	QPushButton::mouseReleaseEvent(event);  
}  

void ICE_Ice_Button::ICE_Set_Button_Icons(const QIcon &normal, const QIcon &focus, const QIcon &pressed)  
{  
	normalIcon = normal;  
	focusIcon = focus;  
	pressedIcon = pressed;  
	setIcon(normalIcon);  
} 
