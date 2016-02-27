#include "icesearch.h"
#include "songdelegate.h"
#include "songmodel.h"
#include "httpdownload.h"
#include <QListView>
#include <QtWidgets>
IceSearch::IceSearch(QWidget *parent)
    : movableWindow(parent)
{
    init_UI();
    downloaded1 = false;
    downloaded2 = false;
    cacheLableFlag = 0;
    cacheLableTimer = new QTimer;
    cacheLableTimer->setInterval(300);
    model = new SongModel;
    download = new HttpDownload;
    view->setModel(model);
     delegate = new SongDelegate;
     view->setItemDelegate(delegate);
     connect(searchButton, SIGNAL(clicked()), this, SLOT(sndReq()));
     connect(searchButton, SIGNAL(clicked()), model, SLOT(clearModel()));
     connect(nextButton, SIGNAL(clicked()), this, SLOT(sndReq()));
     connect(view, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(itemData(QModelIndex)));
     connect(download, SIGNAL(downloaded(QByteArray, QString)), this, SLOT(rcvRawData(QByteArray, QString)));
     connect(cacheLableTimer, SIGNAL(timeout()), this, SLOT(cacheLableTimeOut()));
}

void IceSearch::init_UI()
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowOpacity(0.9);
    this->setFixedSize(600, 600);
    view = new QListView(this);
    view->setGeometry(40,45,530,500);
    view->setSpacing(0);
    keyWordsEdit = new QLineEdit("lighters", this);
    keyWordsEdit->setGeometry(40,20,100,20);
    searchButton =  new QPushButton("search",  this);
    searchButton->setGeometry(160, 20, 50, 20);
    searchButton->setObjectName("searchBtn");
    nextButton = new QPushButton("next", this);
    nextButton->setObjectName("nextBtn");
    nextButton->setGeometry(240, 20, 50, 20) ;

    referLable = new QLabel("", this);
    referLable->setGeometry(40,550,150,20);
    referLable->setText("0 "+lableFormat);
    cacheLable = new QLabel("", this);
    cacheLable->setGeometry(250, 550, 450, 20);
}

IceSearch::~IceSearch()
{

}

void IceSearch::itemData(const QModelIndex &index)
{
    QStringList str = index.model()->data(index, Qt::DisplayRole).toStringList();
    qDebug() << str.at(0) << str.at(1) << str.at(2);
    songInfo.append(str.at(0)+"--"+str.at(1));
    songInfo.append(str.at(0)+"--"+str.at(1));
    picUrl = str.at(3);
    songUrl = str.at(4);
    download->getRawData("1", picUrl);
    download->getRawData("2", songUrl);

    cacheLableTimer->start();
}

void IceSearch::sndReq()
{

    QString senderName = sender()->objectName();
    if(senderName == "searchBtn"){
        _songCount = 0;
        _offset = 0;
    }
    else if(senderName == "nextBtn"){
        if(_offset < 100)
            _offset += 1;
        else
            referLable->setText("out of high limit");
    }
    QString limit = "10";
    QString API = "http://s.music.163.com/search/get/?type=1";
    QString arg0 = "&s=" + keyWordsEdit->text();
    QString arg1 = "&limit=" + limit;
    QString arg2 = "&offset=" + QString::number(10*_offset, 10);
    QString url = API + arg0 + arg1 + arg2;
    download->getRawData("0", url );
    qDebug() << "send a req";
}


QList<QStringList> IceSearch::jsonToLListString(QByteArray rawData)
{
    QJsonDocument jsonDoc;
    QJsonObject jsonResultObj, jsonObj;
    QJsonValue  jsonResultVal;
    QJsonArray songArray, artistsArray;
    QJsonParseError err;
    QString songName, artistsName, album, picUrl, audio;
    artistsName = "temp";
    QStringList singleSongInfo;
    QList<QStringList> songList;
    int artistsNum;
    int ArraySize, i, j;
    jsonDoc = QJsonDocument::fromJson(rawData, &err) ;
   if(err.error != QJsonParseError::NoError)
   {
       qDebug() << "get error";
       referLable->setText("can`t access to network!");
       return songList;
   }
    jsonObj = jsonDoc.object();
    jsonResultVal = jsonObj.take("result");
    jsonResultObj = jsonResultVal.toObject();
    songCount = jsonResultObj.take("songCount").toInt();
    referLable->setText(QString::number(songCount)+lableFormat);
    songArray = jsonResultObj.take("songs").toArray();
    if(songArray.isEmpty() == true)
        return songList;
    ArraySize = songArray.count();
    for(i = 0; i < ArraySize; i++){
        if(singleSongInfo.isEmpty() == false)
            singleSongInfo.clear();
            songName = songArray.at(i).toObject().take("name").toString();
            artistsNum = songArray.at(i).toObject().take("artists").toArray().count();
            artistsArray = songArray.at(i).toObject().take("artists").toArray();
        if(artistsName.isEmpty() == false)
            artistsName.clear();
       for(j = 0; j < artistsNum; j++){
           // qDebug() << "artistsNum != artistArray";
           if(j < artistsArray.size() )
                artistsName = artistsName + artistsArray.at(j).toObject().take("name").toString() + "-";
           // if(j == artistsNum-1)
               // qDebug() << "artistsName = " << artistsName;
        }

        album = songArray.at(i).toObject().take("album").toObject().take("name").toString();
        picUrl = songArray.at(i).toObject().take("album").toObject().take("picUrl").toString();
        audio = songArray.at(i).toObject().take("audio").toString();
        singleSongInfo << songName << artistsName << album << picUrl << audio;
        songList.append(singleSongInfo);
    }
    return songList;
}
void IceSearch::rcvRawData(QByteArray data, QString type)
{
    QFile *file = new QFile;
    if(type == "0"){
        QList<QStringList> temp = jsonToLListString(data);
         model->setSongInfo(temp);
         return;
    }
    else if(type == "1"){
        file->setFileName(songInfo.at(0) +QString(".png"));
        songInfo.removeAt(0);
        downloaded1 = true;
    }
    else if(type == "2"){
         file->setFileName(songInfo.at(0) + QString(".mp3"));
         songInfo.removeAt(0);
         downloaded2 = true;
    }
    if(downloaded1 && downloaded2){
        cacheLableTimer->stop();
        downloaded1 = downloaded2 = false;
        cacheLable->setText("worked perfectly! downloaded completely!");
    }
    if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("HTTP"),
                                 tr("Unable to save the file %1: %2.")
                                 .arg("err1").arg("err2"));
        delete file;
        file = 0;
        return;
    }
    file->write(data);
    file->close();
    if(type == "2"){
        QStringList temp;
        temp << QFileInfo(*file).absoluteFilePath();
        emit audioFilePath(temp);
    }
    qDebug() << "Writen data";
}



void IceSearch::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0, 0,this->width(), this->height(),  QPixmap(":/Resources/background.png"));
}

void IceSearch::cacheLableTimeOut()
{
        if(cacheLableFlag == 0){
            cacheLable->setText("Be downloading song.");
            cacheLableFlag+=1;
        }
        else if(cacheLableFlag == 1){
            cacheLable->setText("Be downloading song..");
            cacheLableFlag+=1;
        }
        else if(cacheLableFlag == 2){
            cacheLable->setText("Be downloading song...");
            cacheLableFlag=0;
        }
}
