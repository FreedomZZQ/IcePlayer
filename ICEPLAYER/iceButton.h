#ifndef ICEBUTTON_H
#define ICEBUTTON_H

#include <QtGui>
#include <QPushButton>
//#include <qwidgetresizehandler_p.h>

class ICE_Ice_Button : public QPushButton
{
    Q_OBJECT
private:
    QIcon normalIcon;
    QIcon focusIcon;
    QIcon pressedIcon;
protected:

    //���ء����롱�͡��뿪���¼�������ʱ�л�Ϊ��һ��ͼ�꣬�뿪ʱ��ԭ
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

    //�������갴�º��ɿ��¼� ���л�ͼ��
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
public:
    ICE_Ice_Button(QWidget *parent = 0);
    ~ICE_Ice_Button();

    //����ͼ��
    //��ָֻ��һ��ͼ�꣬��Ĭ�ϡ����롱�����£��ɿ���Ϊ��ͼ��
    void ICE_Set_Button_Icons(const QIcon &normal, const QIcon &focus = QIcon(), const QIcon &pressed = QIcon() );
};


#endif
