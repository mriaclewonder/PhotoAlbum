#include "protreethread.h"

#include "ProTreeItem.h"
#include "const.h"
#include <QDir>
#include <qdebug.h>

ProTreeThread::ProTreeThread(const QString &src_path, const QString &dis_path, QTreeWidgetItem *parent_item, int& file_count, QTreeWidget *self, QTreeWidgetItem *root, QObject *parent)
    : QThread(parent), _src_path(src_path), _dis_path(dis_path), _parent_item(parent_item), _file_count(file_count), _self(self), _root(root), _bstop(false)
{

}

ProTreeThread::~ProTreeThread()
{

}

void ProTreeThread::run()
{
    CreateProTree(_src_path, _dis_path, _parent_item, _file_count, _self, _root, nullptr, _dis_path);
    if(_bstop)
    {
        auto path = dynamic_cast<ProTreeItem*>(_root)->GetPath();
        auto index = _self->indexOfTopLevelItem(_root);
        delete _self->takeTopLevelItem(index);
        QDir dir(path);
        dir.removeRecursively(); // 整个目标目录及其下所有已复制的文件/文件夹彻底删除
        return;
    }
    emit sig_FinishProgress(_file_count);
}

void ProTreeThread::slot_cancleProgress()
{
    this->_bstop = true;
}

void ProTreeThread::CreateProTree(const QString &src_path, const QString &dis_path, QTreeWidgetItem *parent_item, int& file_count,
                                  QTreeWidget *self, QTreeWidgetItem *root, QTreeWidgetItem *pre_item, const QString& root_dis_path)
{
    if (_bstop)
    {
        return;
    }

    bool needcopy = true;
    if (src_path == dis_path)
    {
        needcopy = false;
    }

    QDir importDir(src_path);
    qDebug() << "ProTreeThread::CreateProTree: src_path is" << src_path << "dis_path is" << dis_path;
    // 设置文件过滤器，除文件和目录以外全过滤掉
    importDir.setFilter(QDir::Dirs | QDir::Files | QDir::NoDotAndDotDot);
    importDir.setSorting(QDir::Name); // 优先显示名字
    QFileInfoList list = importDir.entryInfoList();
    qDebug() << "ProTreeThread::CreateProTree: info list size is" << list.size();

    for(int i = 0; i < list.size(); ++i)
    {
        if (_bstop)
        {
            return;
        }

        QFileInfo info = list.at(i);
        if (info.isDir())
        {
            if (_bstop)
            {
                return;
            }

            QString info_abs = info.absoluteFilePath();
            if (root_dis_path == info_abs || root_dis_path.startsWith(info_abs + "/"))
            {
                continue;
            }

            file_count++;
            emit sig_updateProgress(file_count);

            QDir disDir(dis_path);
            // 构建子目录路径
            QString sub_dist_path = disDir.absoluteFilePath(info.fileName());
            qDebug() << "ProTreeThread::CreateProTree: sub_dist_path is" << sub_dist_path;
            QDir sub_dist_dir(sub_dist_path);
            if(!sub_dist_dir.exists())
            {
                if (!sub_dist_dir.mkpath(sub_dist_path))
                {
                    qDebug() << "ProTreeThread::CreateProTree: mkpath failed";
                    continue;
                }
            }
            auto* item = new ProTreeItem(parent_item, info.fileName(), sub_dist_path, root, TreeItemDir);
            item->setData(0, Qt::DisplayRole, info.fileName());
            item->setData(0, Qt::DecorationRole, QIcon(":/icon/dir.png"));
            item->setData(0, Qt::ToolTipRole, sub_dist_path);

            CreateProTree(info.absoluteFilePath(), sub_dist_path, item, file_count, self, root, pre_item, root_dis_path);
        }
        else
        {
            if(_bstop)
            {
                return;
            }

            const QString& suffix = info.completeSuffix();
            if(suffix != "png" && suffix != "jpg" && suffix != "jpeg")
            {
                qDebug() << "ProTreeThread::CreateProTree: suffix is no picture" << suffix;
                continue;
            }

            file_count++;
            emit sig_updateProgress(file_count);
            if(!needcopy)
            {
                continue;
            }

            QDir disDir(dis_path);
            QString dis_file_path = disDir.absoluteFilePath(info.fileName());
            if(!QFile::copy(info.absoluteFilePath(), dis_file_path))
            {
                qDebug() << "ProTreeThread::CreateProTree: file src to dist copy is failed";
                continue;
            }

            auto *item = new ProTreeItem(parent_item, info.fileName(), dis_file_path, root, TreeItemPic);
            item->setData(0, Qt::DisplayRole, info.fileName());
            item->setData(0, Qt::DecorationRole, QIcon(":/icon/pic.png"));
            item->setData(0, Qt::ToolTipRole, dis_file_path);

            if(pre_item)
            {
                auto* pre_proitem = dynamic_cast<ProTreeItem*>(pre_item);
                pre_proitem->SetNextItem(item);
            }

            item->SetPreItem(pre_item);
            pre_item = item;
        }
    }
    parent_item->setExpanded(true);
}
