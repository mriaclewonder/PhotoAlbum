#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include "protreethread.h"
#include <QObject>
#include <QProgressDialog>
#include <QTreeWidget>
#include <QWidget>

#include <QHeaderView>
#include <qaction.h>

/**
 * @brief 目录树基类
 */

class ProTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ProTreeWidget(QWidget* parent = nullptr);

    void addProToTree(const QString &name, const QString &path); // 添加新的item

private slots:
    void slot_itemPressed(QTreeWidgetItem* item, int cloumn);
    void slot_import();
    void slot_setActive();

    void slot_updateProgress(int count);
    void slot_cancelProgress();
    void slot_finishProgress();

signals:
    void sig_cancleProgress();

private:
    QSet<QString> _set_path;
    QAction* _action_import = nullptr;
    QAction* _action_setstart = nullptr;
    QAction* _action_closepro = nullptr;

    QTreeWidgetItem* _right_btn_item = nullptr;
    QTreeWidgetItem* _active_item = nullptr;
    QProgressDialog* _dialog_progress = nullptr;

    // copy文件线程
    QSharedPointer<ProTreeThread> _thread_create_pro = nullptr;
};

#endif // PROTREEWIDGET_H
