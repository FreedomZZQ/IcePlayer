#include "songmodel.h"

SongModel::SongModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

void SongModel::setSongInfo(const QList<QStringList> &songInfo)
{
    beginResetModel();
    modelSongInfo.append(songInfo);
    endResetModel();
}

int SongModel::rowCount(const QModelIndex &/*parent*/) const
{
    if(modelSongInfo.isEmpty())
        return 0;
    return modelSongInfo.size();
}
QVariant SongModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();
    //qDebug() << modelSongInfo[index.row()].at(0);
    return modelSongInfo[index.row()];
}


void SongModel::clearModel()
{
    /* if modelSongInfo `s item is Empty, then you invoke clear. program crash*/
    if(modelSongInfo.isEmpty())
        return;
    modelSongInfo.clear();
}
