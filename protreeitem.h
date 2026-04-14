#ifndef PROTREEITEM_H
#define PROTREEITEM_H

#include <QObject>
#include <QTreeWidgetItem>
#include <QWidget>

class ProTreeItem : public QTreeWidgetItem
{
public:
    explicit ProTreeItem(QTreeWidget* view, const QString &name, const QString &path, int type = Type);
    explicit ProTreeItem(QTreeWidgetItem* parent, const QString &name, const QString &path, QTreeWidgetItem* root, int type = Type);
};

#endif // PROTREEITEM_H
