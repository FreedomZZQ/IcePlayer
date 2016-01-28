//网络模块，实现网络功能
//使用单例模式，封装网络接口
//使用instance()获取唯一的NetWorker对象
//使用内部类Private封装私有变量


#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class NetWorker : public QObject{

	Q_OBJECT

public:

	//获取唯一实例
	static NetWorker *instance();

	~NetWorker();

	//向url发送get请求
	void get(const QString &url);

signals:
	//操作完成后发射finished信号
	void finished(QNetworkReply *reply);

private:
	class Private;
	friend class Private;
	Private *d;

	//使用单例模式，类的构造函数，复制构造函数和赋值运算符都声明为私有
	//若编译器支持c++ 11，Q_DECL_EQ_DELETE宏替换为 =delete
	explicit NetWorker(QObject *parent = 0);
	NetWorker(const NetWorker &) Q_DECL_EQ_DELETE;
	NetWorker &operator=(NetWorker rhs) Q_DECL_EQ_DELETE;
};


#endif //NETWORK_H
