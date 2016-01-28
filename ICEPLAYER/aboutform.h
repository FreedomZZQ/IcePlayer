#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
#include <qwidgetresizehandler_p.h>
#include "iceButton.h"

class ICE_About_Form : public QDialog
{
	Q_OBJECT
public:
	ICE_About_Form(QWidget *parent = 0);
	~ICE_About_Form();

private:

	//ªÊ÷∆±≥æ∞Õº∆¨
	void paintEvent(QPaintEvent *event); 

	ICE_Ice_Button *exitButton;
};


#endif