#ifndef SONGMODEL_H
#define SONGMODEL_H
#include <QAbstractListModel>
#include <QtCore>
class SongModel : public QAbstractListModel
{
    Q_OBJECT
public:
    SongModel(QObject *parent=0);
    void setSongInfo(const QList<QStringList> &songInfo);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
public slots:
    void clearModel();
private:
    QList<QStringList> modelSongInfo;
};

#endif // SONGMODEL_H
