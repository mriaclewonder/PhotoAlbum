#ifndef PROSETPAGE_H
#define PROSETPAGE_H

#include <QWizardPage>


namespace Ui
{
    class ProSetPage;
}

/**
 * @brief 向导页创建相册目录界面
 */

class ProSetPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ProSetPage(QWidget *parent = nullptr);
    ~ProSetPage();

    // 获取项目名字和路径
    void getProSettings(QString& name, QString& path);

protected:
    // 发送completeChanged信号时，会自动触发isComplete函数
    bool isComplete() const override;

private slots:
    void on_btnBrowse_clicked();

private:
    Ui::ProSetPage* ui;
};

#endif // PROSETPAGE_H
