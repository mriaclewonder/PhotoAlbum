#include "protreewidget.h"

#include <QDir>
#include <QDebug>
#include <qguiapplication.h>
#include <QMenu>

#include "protreeitem.h"
#include "const.h"

ProTreeWidget::ProTreeWidget(QWidget* parent): QTreeWidget(parent)
{
    // 隐藏表头
    this->header()->hide();

    connect(this, &ProTreeWidget::itemPressed, this, &ProTreeWidget::slot_itemPressed);

    _action_import = new QAction(QIcon(":/icon/import.png"), tr("导入文件"), this);
    connect(_action_import, &QAction::triggered, this, &ProTreeWidget::slot_import);
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
    // 添加item到左边文件夹
    this->addTopLevelItem(item);
}

void ProTreeWidget::slot_itemPressed(QTreeWidgetItem *item, int cloumn)
{
    qDebug() << "ProTreeWidget slot_itemPressed";
    if (QGuiApplication::mouseButtons() == Qt::RightButton)
    {
        QMenu menu(this);
        int itemtype = (int)item->type();
        if (itemtype == TreeItemType::TreeItemPro)
        {
            _right_btn_item = item;
            menu.addAction(_action_import);
            menu.exec(QCursor::pos());   //菜单弹出位置为鼠标点击位置
        }
    }
}

void ProTreeWidget::slot_import()
{

}
