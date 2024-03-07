#include "mainwindow_5.h"
#include "ui_mainwindow_5.h"

MainWindow_5::MainWindow_5(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_5)
{
    ui->setupUi(this);
    // --
    ui->label->setScaledContents(true);
    ui->label_2->setScaledContents(true);
    ui->lineEdit->setEnabled(false);
    net = cv::dnn::readNetFromONNX("./data/net.onnx");
    pworker->moveToThread(pthread);
    pthread->start();
    connect(this, &MainWindow_5::start_lr2sr, pworker, &WorkThread::lr2sr);
    connect(pworker, &WorkThread::done_lr2sr, [=](QImage image_sr_q)
    {
        ui->label_2->setPixmap(QPixmap::fromImage(image_sr_q));
        ui->statusbar->showMessage("已生成图像！");});
}

MainWindow_5::~MainWindow_5()
{
    // --
    pthread->quit();
    pthread->wait();
    delete ui;
}

void MainWindow_5::on_pushButton_clicked()
{
    // 记住上次打开的路径
    QSettings setting("./Setting.ini", QSettings::IniFormat);
    QString lastPath = setting.value("LastFilePath").toString();
    QString fileName = QFileDialog::getOpenFileName(this,tr("打开图像"), lastPath, tr("图像格式(*.png *.jpg *.bmp)"));
    //
    ui->lineEdit->setText(fileName);
    //
    image_lr = cv::imread(fileName.toStdString());
    ui->label_2->clear();
    if (image_lr.empty())
    {
        ui->statusbar->showMessage("图像不存在！");
        ui->label->clear();
        return;
    }
    if (image_lr.channels() == 3)
    {
        cvtColor(image_lr, image_lr, cv::COLOR_BGR2RGB);
    }
    cv::resize(image_lr, image_lr, cv::Size(100,100), 0, 0, cv::INTER_CUBIC);
    // graphicsView 显示图像
    QImage image_lr_q = QImage((const unsigned char*)(image_lr.data), image_lr.cols, image_lr.rows, image_lr.cols*image_lr.channels(), QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image_lr_q));
    ui->statusbar->showMessage("已读取图像！");
}


void MainWindow_5::on_pushButton_2_clicked()
{
    //
    if (image_lr.empty())
    {
        ui->statusbar->showMessage("未选择图像！");
        return;
    }
    if (net.empty())
    {
        ui->statusbar->showMessage("未读取模型！");
        return;
    }
    else
    {
        ui->statusbar->showMessage("已读取模型！");
    }
    //
//    pthread->start();
    pworker->set_variable(image_lr, net, true);
    emit start_lr2sr();
}

