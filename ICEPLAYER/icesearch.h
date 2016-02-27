#ifndef ICESEARCH_H
#define ICESEARCH_H

#include <QWidget>
#include "movablewindow.h"
class QListView;
class SongModel;
class SongDelegate;
class QPushButton;
class QLineEdit;
class QLabel;
class HttpDownload;
const QString lableFormat=" relative songs.";
class IceSearch : public movableWindow
{
    Q_OBJECT

public:
    IceSearch(QWidget *parent=0);
    void init_UI();
    QList<QStringList> jsonToLListString(QByteArray rawData);
    void paintEvent(QPaintEvent *event);
    ~IceSearch();
signals:
    void transfer(QString picUrl, QString songUrl);
    void audioFilePath(QStringList Path);
public slots:
   void sndReq();
   void itemData(const QModelIndex &index);
   void rcvRawData(QByteArray data, QString type);
private slots:
   void cacheLableTimeOut();
private:
    QListView  *view;
     SongModel  *model;
     SongDelegate *delegate;
     QPushButton *searchButton;
     QPushButton *nextButton;
     QLineEdit *keyWordsEdit;
     QLabel *referLable;
     HttpDownload *download;
     int _songCount;
     int _offset;
     int highLimit;
     QString picUrl;
     QString songUrl;
     QList<QString> songInfo;
     QByteArray rawData;

     QLabel *cacheLable;
     QTimer *cacheLableTimer;
     int cacheLableFlag;

     int songCount;
     bool downloaded1;
     bool downloaded2;
};

#endif // ICESEARCH_H

