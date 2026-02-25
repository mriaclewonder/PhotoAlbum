#include "mainwindow.h"

#include <QApplication>

#include <QFile>
#include <QDebug>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QFile file(":/style/style.qss");
    if (file.open(QFile::ReadOnly))
    {
        qDebug() << "open style success";
        QString stylesheet = QString(file.readAll());
        a.setStyleSheet(stylesheet);
    }
    else
    {
        qDebug() << "open style failed";
    }
    file.close();

    w.setWindowTitle("Album");
    w.showMaximized();
    w.show();
    return a.exec();
}
