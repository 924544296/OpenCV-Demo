#include "mainwindow_4.h"
#include "ui_mainwindow_4.h"

MainWindow_4::MainWindow_4(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_4)
{
    ui->setupUi(this);
    // --
    ui->label->setScaledContents(true);
    ui->label_2->setScaledContents(true);
    pworker->moveToThread(pthread);
    pworker->open_camera();
    ptimer->start(10);
    connect(ptimer, &QTimer::timeout, pworker, &WorkThread::read_image);
    connect(pworker, &WorkThread::done_read_image1, [=](QImage image1)
    {
        ui->label->setPixmap(QPixmap::fromImage(image1));
    });
    connect(pworker, &WorkThread::done_read_image2, [=](QImage image2)
    {
        ui->label_2->setPixmap(QPixmap::fromImage(image2));
    });
}

MainWindow_4::~MainWindow_4()
{
    // --
    on_pushButton_2_clicked();
    delete ui;
}

void MainWindow_4::on_pushButton_clicked()
{
    pworker->set_flag_start(true);
    pthread->start();
}


void MainWindow_4::on_pushButton_2_clicked()
{
    pworker->set_flag_start(false);
    pthread->quit();
    pthread->wait();
}


void MainWindow_4::on_pushButton_3_clicked()
{
    if (pworker->get_flag_start() == false)
    {
        QMessageBox::information(this,
            tr("老哥"),
            tr("你要打开摄像头才能截图。"),
            QMessageBox::Ok | QMessageBox::Cancel,
            QMessageBox::Ok);
        return;
    }
    pworker->set_flag_send(true);
}
