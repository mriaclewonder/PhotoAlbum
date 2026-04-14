#ifndef PROTREEWIDGET_H
#define PROTREEWIDGET_H

#include <QObject>
#include <QTreeWidget>
#include <QWidget>

#include <QHeaderView>

class ProTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    explicit ProTreeWidget(QWidget* parent = nullptr);

    void addProToTree(const QString &name, const QString &path); // 添加新的item

private:
    QSet<QString> _set_path;
};

#endif // PROTREEWIDGET_H
