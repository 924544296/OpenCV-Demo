#include "mainwindow_6.h"
#include "ui_mainwindow_6.h"

MainWindow_6::MainWindow_6(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_6)
{
    ui->setupUi(this);
    // --
    ui->label->setScaledContents(true);
    ui->label_2->setScaledContents(true);
    pworker->moveToThread(pthread);
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

MainWindow_6::~MainWindow_6()
{
    delete ui;
    // --
    on_pushButton_3_clicked();
}

void MainWindow_6::on_pushButton_clicked()
{
    QString name = QFileDialog::getOpenFileName(this, "选择视频", "", "视频格式(*.avi *.mp4)");
    pworker->open_video(name, pframeCount, pfps);
    ptimer->start(1000/(*pfps));
}


void MainWindow_6::on_pushButton_2_clicked()
{
    pworker->set_flag_start(true);
    pthread->start();
}


void MainWindow_6::on_pushButton_3_clicked()
{
    pworker->set_flag_start(false);
    pthread->quit();
    pthread->wait();
}


void MainWindow_6::on_pushButton_4_clicked()
{
    if (pworker->get_flag_start() == false)
    {
        QMessageBox::information(this,
                                 tr("老哥"),
                                 tr("你要开启播放才能截图。"),
                                 QMessageBox::Ok | QMessageBox::Cancel,
                                 QMessageBox::Ok);
        return;
    }
    pworker->set_flag_send(true);
}

