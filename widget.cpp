#include "widget.h"
#include "ui_widget.h"
#include <QProcess>
#include <DFileDialog>
#include <QFileDialog>
#include <QDebug>
#include <QLoggingCategory>
#include <QFile>
#include <QStandardPaths>
#include <DMessageBox>
#include <DInputDialog>
#include <QDateTime>
#include <QJsonDocument>
#include <QJsonObject>

DWIDGET_USE_NAMESPACE
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QProcess help;
    help.start("spark-webapp-runtime -h");
    help.waitForFinished();
    ui->moreHelp->setText(help.readAllStandardOutput());
    // 信息读取
     QFile information(QCoreApplication::applicationDirPath() + "/information.json");
     information.open(QIODevice::ReadOnly);
    QJsonDocument info = QJsonDocument::fromJson(information.readAll());
    informationJson = info.object();
    information.close();
    // 允许 qDebug() 输出
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
    // 设置开发者信息
    ui->information->setText("版本：" + informationJson.value("Version").toString() + "\n©2021~" + QDateTime::currentDateTime().toString("yyyy") + " gfdgd xi、为什么您不喜欢熊出没和阿布呢");
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_openButton_clicked()
{
    QProcess process;
    QStringList command;
    command << "-u" << ui->openUrl->text();
    process.startDetached("spark-webapp-runtime", command);
}

void Widget::on_moreOpen_clicked()
{
    QProcess process;
    QStringList command;

    command << "-u" << ui->openUrl->text() << "-t" << ui->openTitle->text() << "-d" << ui->openShowThings->text() << "-i" << iconPath << ui->openOtherOption->text().split(" ");
    process.startDetached("spark-webapp-runtime", command);
}

void Widget::on_label_7_linkActivated(const QString &link)
{
    QString path = DFileDialog::getOpenFileName(this, "浏览文件", "~", "图标文件(*.png *.svg);;全部文件(*.*)");
    iconPath = path;
    if(path == ""){
        ui->iconShow->setText("<img src=':/images/logo.svg' width=150>");
    }
    else {
        ui->iconShow->setText("<img src='" + iconPath + "' width=150>");
    }
}

void Widget::on_pushButton_4_clicked()
{
    WriteShell();
}

void Widget::WriteShell(){
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    if(QFile::exists(desktopPath + "/" + ui->shellName->text() + ".sh")){
        if(QMessageBox::question(this, "提示", "文件已存在，是否覆盖？") == DMessageBox::No){
            return;
        }
    }
    QFile file(desktopPath + "/" + ui->shellName->text() + ".sh");
    file.open(QIODevice::WriteOnly);
    file.write(("#!/bin/bash\n"\
               "spark-webapp-runtime -u '" + ui->openUrl->text() + "' -t '" + ui->openTitle->text() + "' -d '" + ui->openTitle->text() + "' -i '" + iconPath + "' " + ui->openOtherOption->text()).toUtf8());
    file.close();
    QProcess process;
    QStringList command;
    command << "777" << desktopPath + "/" + ui->shellName->text() + ".sh";
    process.start("chmod", command);
    DMessageBox::information(this, "提示", "写入完成！");
}

void Widget::WriteDesktop(int place){
    QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    QString homePath = QDir::homePath();
    QString bashPath;
    switch (place) {
    case 0:
        bashPath = desktopPath + "/" + ui->shellName->text() + ".sh";
        break;
    case 1:
        bashPath = homePath + "/.local/share/applications" + ui->shellName->text() + ".desktop";
        break;
    defult:
        bashPath = homePath + "/.local/share/applications" + ui->shellName->text() + ".desktop";
        break;
    }
    if(QFile::exists(bashPath)){
        if(QMessageBox::question(this, "提示", "文件已存在，是否覆盖？") == QMessageBox::No){
            return;
        }
    }
    QFile file(bashPath);
    file.open(QIODevice::WriteOnly);
    file.write(("[Desktop Entry]\nType=Application\n"\
               "Name=" + ui->openTitle->text() + \
               "\nComment=" + ui->openTitle->text() + \
               "\nExec=spark-webapp-runtime -u '" + ui->openUrl->text() + "' -t '" + ui->openTitle->text() + "' -d '" + ui->openTitle->text() + "' -i '" + iconPath + "' " + ui->openOtherOption->text() + \
               "\nIcon=" + iconPath).toUtf8());
    file.close();
    QMessageBox::information(this, "提示", "写入完成！");
}

void Widget::on_pushButton_3_clicked()
{
    WriteDesktop(0);
}

void Widget::on_pushButton_5_clicked()
{
    WriteDesktop(1);
}

void Widget::on_moreBuild_clicked()
{
    QString package = DInputDialog::getText(this, "输入信息", "请输入要打包的包名：");
    QString maker = DInputDialog::getText(this, "输入信息", "请输入要打包的维护者：");
    QString version = DInputDialog::getText(this, "输入信息", "请输入要打包的版本号：");
    QString informationList[3] = {package, maker, version};
    for (int i = 0; i < 3; i++) {
        if(informationList[i] == "") {
            QMessageBox::information(this, "提示", "信息未填写完整，无法继续");
            return;
        }
    }
    QProcess process;
    QStringList command;
    command << "deepin-terminal" << "-e" << QCoreApplication::applicationDirPath() + "/spark-web-packer" << ui->openUrl->text() << ui->openTitle->text() << iconPath << ui->openShowThings->text() << package << maker << version << ui->openOtherOption->text();
    process.startDetached(QCoreApplication::applicationDirPath() + "/launch.sh", command);
}
