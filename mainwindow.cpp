#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMenu>
#include <QAction>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 创建文件菜单栏
    QMenu* menu_file = menuBar()->addMenu(tr("file(&F)"));

    // 创建项目动作
    QAction* act_creat_pro = new QAction(QIcon(":/icon/createpro.png"), tr("create project"), this);
    act_creat_pro->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    menu_file->addAction(act_creat_pro);

    // 打开项目动作
    QAction* act_open_pro = new QAction(QIcon(":/icon/openpro.png"), tr("open project"), this);
    act_open_pro->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
    menu_file->addAction(act_open_pro);

    // 创建设置菜单
    QMenu* menu_set = menuBar()->addMenu(tr("setting(&S)"));

    // 设置背景音乐动作
    QAction* act_set_music = new QAction(QIcon(":/icon/music.png"), tr("background music"), this);
    act_set_music->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_M));
    menu_set->addAction(act_set_music);

    // 创建项目
    connect(act_creat_pro, &QAction::triggered, this, &MainWindow::slot_createPro);
    // 打开项目
    connect(act_open_pro, &QAction::triggered, this, &MainWindow::slot_openPro);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 创建项目
void MainWindow::slot_createPro()
{

}

// 打开项目
void MainWindow::slot_openPro()
{

}
