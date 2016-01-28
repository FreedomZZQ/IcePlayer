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

	//设置文本:
	//如果ms为0则文字不滚动(默认不滚动);
	//如果调用setText()文字将不滚动(与使用QLabel相同);
	void ICE_Set_Text(const QString &context=0, const int &ms=0);

	//停止滚动
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