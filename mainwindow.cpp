#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMenu>
#include <QAction>
#include <QDebug>

#include "Wizard.h"
#include "protree.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建文件菜单栏
    QMenu* menu_file = menuBar()->addMenu(tr("file(&F)"));
    QAction* act_creat_pro = new QAction(QIcon(":/icon/createpro.png"), tr("create project"), this);
    act_creat_pro->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    menu_file->addAction(act_creat_pro);

    // 打开项目菜单
    QAction* act_open_pro = new QAction(QIcon(":/icon/openpro.png"), tr("open project"), this);
    act_open_pro->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    menu_file->addAction(act_open_pro);

    // 设置菜单
    QMenu* menu_set = menuBar()->addMenu(tr("setting(&S)"));
    QAction* act_set_music = new QAction(QIcon(":/icon/music.png"), tr("background music"), this);
    act_set_music->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    menu_set->addAction(act_set_music);

    _proTree = new ProTree();
    ui->proLayout->addWidget(_proTree, 0);

    connect(act_creat_pro, &QAction::triggered, this, &MainWindow::slot_createPro);
    connect(act_open_pro, &QAction::triggered, this, &MainWindow::slot_openPro);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_createPro()
{
    Wizard wizard(this);
    wizard.setWindowTitle(tr("创建项目"));
    auto *page = wizard.page(0);
    page->setTitle(tr("设置项目配置"));
    connect(&wizard, &Wizard::sig_prosettings, dynamic_cast<ProTree*>(_proTree), &ProTree::slot_addProToTree);
    wizard.show();
    wizard.exec();
    disconnect(&wizard);
}

void MainWindow::slot_openPro()
{

}
