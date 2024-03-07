#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include "mainwindow_2.h"
#include "mainwindow_3.h"
#include "mainwindow_4.h"
#include "mainwindow_5.h"
#include "mainwindow_6.h"


Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    // --
    ui->comboBox->addItem("改变对比度和亮度");
    ui->comboBox->addItem("两张图像加权求和");
    ui->comboBox->addItem("滤波");
    ui->comboBox->addItem("摄像头");
    ui->comboBox->addItem("超分辨率");
    ui->comboBox->addItem("视频");
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    switch (ui->comboBox->currentIndex())
    {
    case 0:
    {
        MainWindow *w = new MainWindow(this);
        w->show();
        break;
    }
    case 1:
    {
        MainWindow_2 *w = new MainWindow_2(this);
        w->show();
        break;
    }
    case 2:
    {
        MainWindow_3 *w = new MainWindow_3(this);
        w->show();
        break;
    }
    case 3:
    {
        MainWindow_4 *w = new MainWindow_4(this);
        w->show();
        break;
    }
    case 4:
    {
        MainWindow_5 *w = new MainWindow_5(this);
        w->show();
        break;
    }
    case 5:
    {
        MainWindow_6 *w = new MainWindow_6(this);
        w->show();
        break;
    }
    }
}

