#include "protree.h"
#include "ui_protree.h"

ProTree::ProTree(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProTree)
{
    ui->setupUi(this);
}

ProTree::~ProTree()
{
    delete ui;
}

void ProTree::slot_addProToTree(const QString &name, const QString &path)
{
    ui->twPro->addProToTree(name, path);
}
