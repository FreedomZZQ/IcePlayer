//����ģ�飬ʵ�����繦��
//ʹ�õ���ģʽ����װ�����ӿ�
//ʹ��instance()��ȡΨһ��NetWorker����
//ʹ���ڲ���Private��װ˽�б���


#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class NetWorker : public QObject{

    Q_OBJECT

public:

    //��ȡΨһʵ��
    static NetWorker *instance();

    ~NetWorker();

    //��url����get����
    void get(const QString &url);

signals:
    //�������ɺ�����finished�ź�
    void finished(QNetworkReply *reply);

private:
    class Private;
    friend class Private;
    Private *d;

    //ʹ�õ���ģʽ�����Ĺ��캯�������ƹ��캯���͸�ֵ������������Ϊ˽��
    //��������֧��c++ 11��Q_DECL_EQ_DELETE���滻Ϊ =delete
    explicit NetWorker(QObject *parent = 0);
    NetWorker(const NetWorker &) Q_DECL_EQ_DELETE;
    NetWorker &operator=(NetWorker rhs) Q_DECL_EQ_DELETE;
};


#endif //NETWORK_H
