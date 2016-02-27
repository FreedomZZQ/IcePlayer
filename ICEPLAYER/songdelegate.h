#ifndef SONGDELEGATE_H
#define SONGDELEGATE_H

#include <QAbstractItemDelegate>
#include <QModelIndex>

class QAbstractItemDelegate;
class QObject;
class QPainter;
class SongDelegate : public QAbstractItemDelegate
{
    Q_OBJECT
public:
    SongDelegate(QObject *parent = 0);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const Q_DECL_OVERRIDE;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
public slots:
    void setWidth(int size);
private:
    int size;
};

#endif // SONGDELEGATE_H
