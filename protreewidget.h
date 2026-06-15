#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include <QObject>
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

private:
    QSet<QString> _set_path;
    QAction* _action_import = nullptr;

    QTreeWidgetItem* _right_btn_item = nullptr;
};

#endif // PROTREEWIDGET_H
