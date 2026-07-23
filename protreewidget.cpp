#include "protreewidget.h"

#include <QDir>
#include <QDebug>
#include <qguiapplication.h>
#include <QMenu>
#include <qfiledialog.h>

#include "protreeitem.h"
#include "const.h"

ProTreeWidget::ProTreeWidget(QWidget* parent): QTreeWidget(parent)
{
    // 隐藏表头
    this->header()->hide();

    connect(this, &ProTreeWidget::itemPressed, this, &ProTreeWidget::slot_itemPressed);

    _action_import = new QAction(QIcon(":/icon/import.png"), tr("导入文件"), this);
    _action_setstart = new QAction(QIcon(":/icon/core.png"), tr("设置活动项目"), this);
    _action_closepro = new QAction(QIcon(":/icon/close.png"), tr("关闭项目"), this);
    connect(_action_import, &QAction::triggered, this, &ProTreeWidget::slot_import);
    connect(_action_setstart, &QAction::triggered, this, &ProTreeWidget::slot_setActive);
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
            menu.addAction(_action_setstart);
            menu.addAction(_action_closepro);
            menu.exec(QCursor::pos());   //菜单弹出位置为鼠标点击位置
        }
    }
}

void ProTreeWidget::slot_import()
{
    QFileDialog file_dialog;
    file_dialog.setFileMode(QFileDialog::Directory);
    file_dialog.setWindowTitle("选择要导入的文件夹");
    QString path = "";
    if (!_right_btn_item)
    {
        qDebug() << "ProTreeWidget::slot_import right btn item is empty!";
        path = QDir::currentPath();
        return;
    }

    path = dynamic_cast<ProTreeItem*>(_right_btn_item)->GetPath();

    file_dialog.setDirectory(path);
    file_dialog.setViewMode(QFileDialog::Detail);

    QStringList file_names;
    if (file_dialog.exec())
    {
        file_names = file_dialog.selectedFiles();
    }

    if (file_names.length() <= 0)
    {
        return;
    }

    // 获取文件名
    QString import_path = file_names.at(0);
    int file_count = 0 ;

    // 创建模态对话框
    _dialog_progress = new QProgressDialog(this);

    _thread_create_pro = QSharedPointer<ProTreeThread>::create(std::ref(import_path), std::ref(path), _right_btn_item, std::ref(file_count), this, _right_btn_item, nullptr);

    connect(_thread_create_pro.get(), &ProTreeThread::sig_updateProgress, this, &ProTreeWidget::slot_updateProgress);

    connect(_thread_create_pro.get(), &ProTreeThread::sig_FinishProgress, this, &ProTreeWidget::slot_finishProgress);

    connect(_dialog_progress, &QProgressDialog::canceled, this, &ProTreeWidget::slot_cancelProgress);

    connect(this, &ProTreeWidget::sig_cancleProgress, _thread_create_pro.get(), &ProTreeThread::slot_cancleProgress);

    // 启动cpoy线程
    _thread_create_pro->start();

    _dialog_progress->setWindowTitle("Please wait....");
    _dialog_progress->setFixedWidth(PROGRESS_WIDTH);
    _dialog_progress->setRange(0, PROGRESS_MAX);
    _dialog_progress->exec();
}

void ProTreeWidget::slot_setActive()
{
    if (!_right_btn_item)
    {
        return;
    }

    QFont null_font;
    null_font.setBold(false);
    if (_active_item)
    {
        _active_item->setFont(0, null_font);
    }

    _active_item = _right_btn_item;
    null_font.setBold(true);
    _active_item->setFont(0, null_font);
}

void ProTreeWidget::slot_updateProgress(int count)
{
    qDebug() << "ProTreeWidget::slot_updateProgress count is" << count;
    if (!_dialog_progress)
    {
        qDebug() << "ProTreeWidget::slot_updateProgress dialog_progress is empty";
        return;
    }
    _dialog_progress->setValue(count % PROGRESS_MAX);
}

void ProTreeWidget::slot_cancelProgress()
{
    emit sig_cancleProgress();
    delete _dialog_progress;
    _dialog_progress = nullptr;
}

void ProTreeWidget::slot_finishProgress()
{
    _dialog_progress->setValue(PROGRESS_MAX);
    _dialog_progress->deleteLater();
}
