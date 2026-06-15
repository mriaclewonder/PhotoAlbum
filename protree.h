#ifndef PROTREE_H
#define PROTREE_H

#include <QDialog>


namespace Ui
{
    class ProTree;
}

/**
 * @brief 左侧相册目录树界面
 */

class ProTree : public QDialog
{
    Q_OBJECT

public:
    explicit ProTree(QWidget *parent = nullptr);
    ~ProTree();

public slots:
    void slot_addProToTree(const QString& name, const QString& path);

private:
    Ui::ProTree* ui;
};

#endif // PROTREE_H
