#include "protreewidget.h"

#include <QDir>
#include <QDebug>
#include "protreeitem.h"
#include "const.h"

ProTreeWidget::ProTreeWidget(QWidget* parent): QTreeWidget(parent)
{
    // 隐藏表头
    this->header()->hide();
}

void ProTreeWidget::addProToTree(const QString &name, const QString &path)
{
    qDebug() << "ProTreeWidget::AddProToTree name is " << name << " path is " << path;
    QDir dir(path);
    QString file_path = dir.absoluteFilePath(name);
    if(_set_path.find(file_path) != _set_path.end())
    {
        qDebug() << "file has loaded";
        return;
    }

    QDir pro_dir(file_path);
    if(!pro_dir.exists())
    {
        bool enable = pro_dir.mkpath(file_path);
        if(!enable)
        {
            qDebug() << "pro_dir make path failed";
            return;
        }
    }

    _set_path.insert(file_path);
    auto * item = new ProTreeItem(this, name, file_path, TreeItemType::TreeItemPro);
    item->setData(0, Qt::DisplayRole, name);
    item->setData(0, Qt::DecorationRole, QIcon(":/icon/dir.png"));
    item->setData(0, Qt::ToolTipRole, file_path);
    // this->addTopLevelItem(item);
}
