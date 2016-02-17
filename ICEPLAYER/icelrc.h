#ifndef ICE_LRC_H
#define ICE_LRC_H

#include <QtWidgets>
#include "lyric.h"
#include "movablewindow.h"
class ICE_Lrc : public movableWindow{
    Q_OBJECT

public:
    ICE_Lrc(movableWindow *parent = 0);
    ~ICE_Lrc();

    //¿ªÊ¼¸è´ÊƠÚ
    void ICE_Start_Lrc_Mask(qint64 intervaltime);

    void ICE_Stop_Lrc_Mask();

    QString text() const;

    void setText(QString /*&*/t);

private:

    void paintEvent(QPaintEvent *event);

    ICE_Lrc_Label *lrcLabel;

};

#endif //ICE_LRC_H
