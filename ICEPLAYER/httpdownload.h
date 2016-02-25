#ifndef HttpDownload_H
#define HttpDownload_H
#include <QNetworkAccessManager>
#include <QUrl>
#include <QtCore>
class HttpDownload : public QObject
{
    Q_OBJECT
public:
    HttpDownload();
    void startRequest(QUrl url);
    void orderData();
signals:
    void downloaded(QList<QStringList> songList, int songCount);
    void downloaded(QByteArray data, QString type);
public slots:
    void getSearchData(QString keyWords, QString limit, QString offset);
    void getRawData(QString type, QString url);
private slots:
    void httpFinished();
    void httpReadyRead();
private:
    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QFile *file;
    int httpGetId;
    bool httpRequestAborted;
    bool search;
    bool downloading;
    QByteArray rawData;
    int songCount;
    QList<QStringList> songList;
    QList<QStringList> waitDownloadUrlList;
    QString dataType;
};

#endif //
