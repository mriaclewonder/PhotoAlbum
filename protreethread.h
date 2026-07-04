#ifndef PROTREETHREAD_H
#define PROTREETHREAD_H

#include <QObject>
#include <QThread>
#include <QTreeWidget>

class ProTreeThread : public QThread
{
    Q_OBJECT
public:
    ProTreeThread(const QString &src_path, const QString& dis_path, QTreeWidgetItem* parent_item, int& file_count, QTreeWidget* self,
                  QTreeWidgetItem *root, QObject *parent = nullptr);

    ~ProTreeThread();

protected:
    virtual void run() override;

public slots:
    void slot_cancleProgress();

signals:
    void sig_updateProgress(int);
    void sig_FinishProgress(int);

private:
    void CreateProTree(const QString &src_path, const QString& dis_path, QTreeWidgetItem* parent_item, int& file_count, QTreeWidget* self,
                       QTreeWidgetItem *root, QTreeWidgetItem* pre_item, const QString& root_dis_path);
    QString _src_path;
    QString _dis_path;
    int _file_count;
    QTreeWidgetItem* _parent_item = nullptr;
    QTreeWidget* _self = nullptr;
    QTreeWidgetItem* _root;
    // 判断是否停止copy
    bool _bstop;
};

#endif // PROTREETHREAD_H
