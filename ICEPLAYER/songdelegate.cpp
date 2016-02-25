#include "songdelegate.h"
#include  <QPainter>
#include <QDebug>
SongDelegate::SongDelegate(QObject *parent)
    : QAbstractItemDelegate(parent)
{
    size = 30;
}

void SongDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    if(index.row()%2 == 0){
        const QColor color = QColor(255, 255, 255);
        painter->fillRect(option.rect, color);
    }
    else {
        const QColor color = QColor(213, 228, 242);
         painter->fillRect(option.rect, color);
    }
   QStringList str = index.model()->data(index, Qt::DisplayRole).toStringList();
    if(option.state & QStyle::State_Selected){
      painter->drawText(option.rect.x()+15, option.rect.y()+20, str.at(0) + "  " + str.at(1) + "  " + str.at(2));
      //painter->drawRect(option.rect);
      return;
    }
    painter->drawText(option.rect.x()+15, option.rect.y()+20, str.at(0) + " " +  str.at(1) + " " + str.at(2));
}

QSize SongDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(size,size);
}

void SongDelegate::setWidth(int m_size)
{
    size = m_size;
}

