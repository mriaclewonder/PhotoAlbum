#ifndef PROSETPAGE_H
#define PROSETPAGE_H

#include <QWizardPage>

namespace Ui
{
    class ProSetPage;
}

class ProSetPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit ProSetPage(QWidget *parent = nullptr);
    ~ProSetPage();

protected:
    bool isComplete() const override; // 发送completeChanged信号时，会自动触发isComplete函数

private slots:
    void on_btnBrowse_clicked();

private:
    Ui::ProSetPage* ui;
};

#endif // PROSETPAGE_H
