#include "mainwindow.h"
#include <DApplication>
#include <DWidgetUtil>  //Dtk::Widget::moveToCenter(&w); 要调用它，就得引用DWidgetUtil
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMenuBar>
#include <DTitlebar>
#include <QUrl>
#include <QDesktopServices>
#include <QObject>
#include <QInputDialog>
#include <DMessageBox>
#include <DAboutDialog>

DWIDGET_USE_NAMESPACE
int main(int argc, char *argv[])
{
    DApplication::loadDXcbPlugin();  //让bar处在标题栏中
    DApplication::setAttribute(Qt::AA_EnableHighDpiScaling);    // 开启 Hidpi 支持
    // 程序内强制添加"-platformtheme deepin"参数喂给Qt让Qt正确使用Deepin主题修复各种奇怪样式问题
     QVector<char*> fakeArgs(argc + 2);
     fakeArgs[0] = argv[0];
     fakeArgs[1] = "-platformtheme";
     fakeArgs[2] = "deepin";
     for(int i = 1; i < argc; i++) fakeArgs[i + 2] = argv[i];
        int fakeArgc = argc + 2; // 为啥DApplication的argc要用引用啊？
     DApplication a(fakeArgc, fakeArgs.data());
    // 信息读取
     QFile information(QCoreApplication::applicationDirPath() + "/information.json");
     information.open(QIODevice::ReadOnly);
    QJsonDocument info = QJsonDocument::fromJson(information.readAll());
    QJsonObject object = info.object();
    DAboutDialog *about = new DAboutDialog();
    about->setLicense("程序协议：GPLV3");
    //about->setWindowTitle("spark-webapp-runtime 运行器");
    about->setProductName("spark-webapp-runtime 运行器");
    about->setProductIcon(QIcon(":/images/icon.png"));
    //about->setWebsiteLink("https://gitee.com/gfdgd-xi/spark-webapp-runtime-runner");
    about->setDescription("一个为了方便使用 spark-webapp-runtime 的运行工具");
    //about->setDescription("Hello World!");
    information.close();
     a.setAttribute(Qt::AA_UseHighDpiPixmaps);
     a.loadTranslator();
     a.setOrganizationName("gfdgd xi、为什么您不喜欢熊出没和阿布呢");
     a.setApplicationVersion(DApplication::buildVersion(object.value("Version").toString()));
     a.setApplicationAcknowledgementPage("https://gitee.com/gfdgd-xi/spark-webapp-runtime-runner");
     a.setProductIcon(QIcon(":/images/icon.png"));  //设置Logo
     a.setProductName("spark-webapp-runtime 运行器");
     a.setApplicationDescription("一个为了方便使用 spark-webapp-runtime 的运行工具");
     a.setApplicationName("spark-webapp-runtime 运行器"); //只有在这儿修改窗口标题才有效
     a.setAboutDialog(about);

    MainWindow w;
    QMenu *menu = new QMenu();
    QAction *updateThings = new QAction("更新内容");
    QObject::connect(updateThings, &QAction::triggered, &w, [&w, object](){
        DMessageBox::information(&w, "更新内容", object.value("UpdateThings").toString().replace("\\n", "\n"));
    });
    menu->addAction(updateThings);
    QAction *thank = new QAction("谢明列表");
    QObject::connect(thank, &QAction::triggered, &w, [&w, object](){
        DMessageBox::information(&w, "谢明列表", object.value("Thank").toString().replace("\\n", "\n"));
    });
    menu->addAction(thank);
    QMenu *websize = new QMenu("程序官网");
    QAction *gitee = new QAction("Gitee");
    QObject::connect(gitee, &QAction::triggered, &w, [](){QDesktopServices::openUrl(QUrl("https://gitee.com/gfdgd-xi/spark-webapp-runtime-runner"));});
    websize->addAction(gitee);
    QAction *github = new QAction("Github");
    QObject::connect(github, &QAction::triggered, &w, [](){QDesktopServices::openUrl(QUrl("https://github.com/gfdgd-xi/spark-webapp-runtime-runner"));});
    websize->addAction(github);
    QAction *gitlink = new QAction("Gitlink");
    QObject::connect(gitlink, &QAction::triggered, &w, [](){QDesktopServices::openUrl(QUrl("https://gitlink.org.cn/gfdgd_xi/spark-webapp-runtime-runner"));});
    websize->addAction(gitlink);

    menu->addMenu(websize);
    w.titlebar()->setMenu(menu);
    w.show();

    //让打开时界面显示在正中
    Dtk::Widget::moveToCenter(&w);


    return a.exec();
}
