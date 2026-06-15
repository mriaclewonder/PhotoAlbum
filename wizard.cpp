#include "wizard.h"
#include "ui_wizard.h"

#include <QMessageBox>

Wizard::Wizard(QWidget *parent)
    : QWizard(parent)
    , ui(new Ui::Wizard)
{
    ui->setupUi(this);

}

Wizard::~Wizard()
{
    delete ui;
}

void Wizard::accept()
{
    QString name, path;
    ui->wizardPage1->getProSettings(name, path);
    emit sig_prosettings(name, path);
    QWizard::accept();
}

void Wizard::reject()
{
    if (QMessageBox::question(this, "确认", "确定要取消吗？") == QMessageBox::Yes)
    {
        QWizard::reject();
    }
}
