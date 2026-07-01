#ifndef PROTREEITEM_H
#define PROTREEITEM_H

#include <QObject>
#include <QTreeWidgetItem>
#include <QWidget>

/**
 * @brief 目录树项基类
 */

class ProTreeItem : public QTreeWidgetItem
{
public:
    explicit ProTreeItem(QTreeWidget* view, const QString &name, const QString &path, int type = Type);
    explicit ProTreeItem(QTreeWidgetItem* parent, const QString &name, const QString &path, QTreeWidgetItem* root, int type = Type);

    const QString& GetPath();
    QTreeWidgetItem* GetRoot();

    void SetPreItem(QTreeWidgetItem * item);
    void SetNextItem(QTreeWidgetItem* item);

    ProTreeItem* GetPreItem();
    ProTreeItem* GetNextItem();
    ProTreeItem* GetLastPicChild();
    ProTreeItem* GetFirstPicChild();

private:
    QString _name;
    QString _path;
    QTreeWidgetItem* _root = nullptr;
    QTreeWidgetItem* _prev_item = nullptr;
    QTreeWidgetItem* _next_item = nullptr;
};

#endif // PROTREEITEM_H
