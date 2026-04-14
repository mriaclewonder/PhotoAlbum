#ifndef WIZARD_H
#define WIZARD_H

#include <QWizard>

#include <QWizardPage>

namespace Ui
{
    class Wizard;
}

class Wizard : public QWizard
{
    Q_OBJECT

public:
    explicit Wizard(QWidget *parent = nullptr);
    ~Wizard();

protected:
    void done(int result) override;

signals:
    void sig_prosettings(const QString &name, const QString& path);

private:
    Ui::Wizard* ui;
};

#endif // WIZARD_H
