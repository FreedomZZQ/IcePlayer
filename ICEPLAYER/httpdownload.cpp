#include "httpdownload.h"
#include <QtNetwork>
HttpDownload::HttpDownload()
{
    downloading = false;
}

void HttpDownload::startRequest(QUrl url)
{
    reply = qnam.get(QNetworkRequest(url));
    connect(reply, SIGNAL(readyRead()),
            this, SLOT(httpReadyRead()));
    connect(reply, SIGNAL(finished()), this, SLOT(httpFinished()));
}

void HttpDownload::getSearchData(QString keyWords, QString limit, QString offset)
{
    QString API = "http://s.music.163.com/search/get/?type=1";
    QString arg0 = "&s=" + keyWords;
    QString arg1 = "&limit=" + limit;
    QString arg2 = "&offset=" + offset;
    QString link = API + arg0 + arg1 + arg2;
    qDebug() << link;
    if(rawData.isEmpty() == false)
        rawData.clear();

     startRequest(link);
    httpRequestAborted = false;
}

/*void HttpDownload::orderData()
{
    QJsonDocument jsonDoc;
    QJsonObject jsonResultObj, jsonObj;
    QJsonValue  jsonResultVal;
    QJsonArray songArray, artistsArray;
    QJsonParseError err;
    QString songName, artistsName, album, picUrl, audio;
    QStringList singleSongInfo;
    int artistsNum;
    int ArraySize, i, j;
    jsonDoc = QJsonDocument::fromJson(rawData, &err) ;
   if(err.error != QJsonParseError::NoError)
   {
       qDebug() << "get error";
       return ;
   }
    jsonObj = jsonDoc.object();
    jsonResultVal = jsonObj.take("result");
    jsonResultObj = jsonResultVal.toObject();
    songCount = jsonResultObj.take("songCount").toInt();
    songArray = jsonResultObj.take("songs").toArray();
    ArraySize = songArray.count();
    for(i = 0; i < ArraySize; i++){
        singleSongInfo.clear();
        songName = songArray.at(i).toObject().take("name").toString();
        artistsNum = songArray.at(i).toObject().take("artists").toArray().count();
        artistsArray = songArray.at(i).toObject().take("artists").toArray();
        artistsName.clear();
        for(j = 0; j < artistsNum; j++){
            artistsName = artistsName + artistsArray.at(j).toObject().take("name").toString() + ",";
            if(j == artistsNum-1)
                qDebug() << "artistsName = " << artistsName;
        }
        album = songArray.at(i).toObject().take("album").toObject().take("name").toString();
        picUrl = songArray.at(i).toObject().take("album").toObject().take("picUrl").toString();
        audio = songArray.at(i).toObject().take("audio").toString();
        singleSongInfo << songName << artistsName << album << picUrl << audio;
        songList.append(singleSongInfo);
    }
}
*/
void HttpDownload::httpFinished()
{
       emit downloaded(rawData, dataType);
        downloading = false;
        if(waitDownloadUrlList.isEmpty() == false)
            waitDownloadUrlList.removeAt(0);
        if(rawData.isEmpty() == false)
            rawData.clear();
       if(waitDownloadUrlList.isEmpty() != true && downloading == false){
           downloading = true;
           if(waitDownloadUrlList.isEmpty() == false){
                startRequest(waitDownloadUrlList.at(0).at(1));
                dataType = waitDownloadUrlList.at(0).at(0);
           }
       }
}

void HttpDownload::httpReadyRead()
{
        rawData = rawData + reply->readAll();
}

void HttpDownload::getRawData(QString type, QString url)
{
            QStringList waitDownloadUrl;
            waitDownloadUrl << type << url ;
            waitDownloadUrlList.append(waitDownloadUrl);
            if(downloading == false){
                downloading = true;
                if(rawData.isEmpty() == false)
                    rawData.clear();
                startRequest(waitDownloadUrl.at(1));
                dataType = waitDownloadUrl.at(0);
            }
}
