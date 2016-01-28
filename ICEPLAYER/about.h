#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>
//#include <QFrame>

class iceButton;

class about : public QDialog
{
	Q_OBJECT
public:
	about(QWidget *parent = 0);
	~about();

private slots:
	
private:
	iceButton *exitButton;

	void paintEvent(QPaintEvent *event); //用窗口绘制事件来绘制背景图片


};


#endif