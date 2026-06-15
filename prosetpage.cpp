#include "prosetpage.h"
#include "ui_prosetpage.h"

#include <QDir>
#include <QFileDialog>

ProSetPage::ProSetPage(QWidget *parent)
    : QWizardPage(parent)
    , ui(new Ui::ProSetPage)
{
    ui->setupUi(this);

    registerField("proName", ui->lineEdit);
    registerField("proPath", ui->lineEdit_2);

    connect(ui->lineEdit, &QLineEdit::textEdited, this, &ProSetPage::completeChanged);
    connect(ui->lineEdit_2, &QLineEdit::textEdited, this, &ProSetPage::completeChanged);

    ui->lineEdit->setClearButtonEnabled(true);
    ui->lineEdit_2->setText(QDir::currentPath() + "/album");
    ui->lineEdit_2->setCursorPosition(ui->lineEdit_2->text().size());
    ui->lineEdit_2->setClearButtonEnabled(true);
}

ProSetPage::~ProSetPage()
{
    delete ui;
}

void ProSetPage::getProSettings(QString &name, QString &path)
{
    name = ui->lineEdit->text();
    path = ui->lineEdit_2->text();
}

bool ProSetPage::isComplete() const
{
    if (ui->lineEdit->text() == "" || ui->lineEdit_2->text() == "")
    {
        return false;
    }

    QDir dir(ui->lineEdit_2->text());
    if (!dir.exists())
    {
        ui->lbTips->setText("project path is not exists...");
        return false;
    }

    // 判断路径是否存在
    QString path = dir.absoluteFilePath(ui->lineEdit->text());
    QDir dir1(path);
    if (dir1.exists())
    {
        ui->lbTips->setText("project has exists, change path or name");
        return false;
    }

    ui->lbTips->setText("");
    return QWizardPage::isComplete();
}

// 选择文件夹
void ProSetPage::on_btnBrowse_clicked()
{
    QString startPath = ui->lineEdit_2->text();
    if (startPath.isEmpty() || !QDir(startPath).exists())
    {
        startPath = QCoreApplication::applicationDirPath();  // 或 QDir::currentPath()
    }

    QString selectedPath = QFileDialog::getExistingDirectory(
                               this,
                               tr("选择项目存放目录"),
                               startPath,
                               QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
                           );

    if (!selectedPath.isEmpty())
    {
        ui->lineEdit_2->setText(selectedPath);
    }
}
