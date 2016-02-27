#ifndef NOFOCUSDELEGATE_H
#define NOFOCUSDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>

class NoFocusDelegate : public QStyledItemDelegate{

protected:

    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
};


#endif
