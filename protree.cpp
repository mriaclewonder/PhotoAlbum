#include "protree.h"
#include "ui_protree.h"

#include <QDir>

ProTree::ProTree(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ProTree)
{
    ui->setupUi(this);
    init();
}

ProTree::~ProTree()
{
    delete ui;
}

void ProTree::slot_addProToTree(const QString &name, const QString &path)
{
    ui->twPro->addProToTree(name, path);
}

void ProTree::init()
{
    const QString path = QDir::currentPath() + "/album";
    QDir dir(path);
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);

    // 获取子文件夹信息列表
    QFileInfoList subfolders = dir.entryInfoList();
    if (subfolders.isEmpty())
    {
        return;
    }

    for (QFileInfo &info : subfolders)
    {
        QString folderName = info.fileName();           // 文件夹名称
        QString fullPath = info.absoluteFilePath();     // 文件夹的完整路径
        ui->twPro->addProToTree(folderName, fullPath);
    }
}
