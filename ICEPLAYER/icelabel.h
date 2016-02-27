#ifndef ICELABEL_H
#define ICELABEL_H
#include <QLabel>
#include <QTimer>

class IceLabel : public QLabel
{
    Q_OBJECT
public:
    explicit IceLabel(QWidget *parent=0);
    ~IceLabel();
    void ICE_Set_Text(const QString &context=0, const int &ms=0);

    //ֹͣ����
    void ICE_Stop();

private slots:

    void ice_time_out();

private:

    void ice_init(int ms = 0);

    QString mContext;
    QTimer *mTimer;

    int mMs;
    int mPos;
};

#endif
