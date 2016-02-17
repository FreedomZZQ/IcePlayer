#ifndef LYRIC_H
#define LYRIC_H

#include <QtWidgets>
#include "icelabel.h"

class ICE_Lrc_Label : public IceLabel{

    Q_OBJECT

public:

    explicit ICE_Lrc_Label(QWidget *parent = 0);

    //��ʼ��������
    void ICE_Start_Lrc_Mask(qint64 intervaltime);

    //ֹͣ��������
    void ICE_Stop_Lrc_Mask();

    //����������С
    void ICE_Set_Size(int size);

protected:

    //���ƴ���
    void paintEvent(QPaintEvent *);

    //�����¼�
    //void mousePressEvent(QMouseEvent *event);
    //void mouseMoveEvent(QMouseEvent *event);

    //�˵��¼�
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
