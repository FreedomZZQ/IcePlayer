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

    //��������ֵ��0~100��
    int ICE_Get_Volume() const;

    //�����������Ƿ��ɼ�
    void ICE_Set_Slider_Visiable(bool);

public slots:

    //����������ʹ��������һ����
    void ICE_Increase_Volume();

    //����������ʹ��������һ����
    void ICE_Descrease_Volume();

    //��������
    void ICE_Set_Volume(int volume);

    //��ť�����¼��������˵�
    void ICE_Button_Clicked();

signals:

    //�����ı��źţ������������϶�ʱ���䣩
    void ICE_Volume_Changed(int volume);

private:
    ICE_Ice_Button *button;
    QSlider *slider;
    QMenu *menu;
    QWidgetAction *action;
};

#endif
