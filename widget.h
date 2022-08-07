#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:

    void on_openButton_clicked();

    void on_moreOpen_clicked();

    void on_label_7_linkActivated(const QString &link);

    void on_pushButton_4_clicked();

    void WriteShell();

    void WriteDesktop(int place);

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Widget *ui;
    QString iconPath = "";

};

#endif // WIDGET_H
