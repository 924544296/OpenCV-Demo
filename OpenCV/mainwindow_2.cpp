#include "mainwindow_2.h"
#include "ui_mainwindow_2.h"

MainWindow_2::MainWindow_2(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_2)
{
    ui->setupUi(this);
    // --
    //
    this->setFixedSize(this->width(),this->height());
    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(100);
    ui->horizontalSlider->setValue(50);
    ui->label->setScaledContents(true);
    ui->label_2->setScaledContents(true);
    //
    ptimer->start(100);
    //
//    connect(ui->horizontalSlider, &QSlider::sliderMoved, this, &MainWindow_2::fuse_image);
//    connect(ui->horizontalSlider, &QSlider::valueChanged, this, &MainWindow_2::fuse_image);
//    connect(this, &MainWindow_2::done_select_and_show_image, this, &MainWindow_2::fuse_image);
    connect(ptimer, &QTimer::timeout, this, &MainWindow_2::fuse_image);
}

MainWindow_2::~MainWindow_2()
{
    delete ui;
}


void MainWindow_2::on_pushButton_clicked()
{
    image1 = select_and_show_image(ui->lineEdit, ui->label);
}


void MainWindow_2::on_pushButton_2_clicked()
{
    image2 = select_and_show_image(ui->lineEdit_2, ui->label_2);
}


cv::Mat MainWindow_2::select_and_show_image(QLineEdit *lineEdit, QLabel *label)
{
    //
    QSettings setting("./Setting.ini", QSettings::IniFormat);          //为了能记住上次打开的路径
    QString lastPath = setting.value("LastFilePath").toString();
    QString fileName = QFileDialog::getOpenFileName(this,tr("打开图像"), lastPath, tr("图像格式(*.png *.jpg *.bmp)"));
    //
    lineEdit->setText(fileName);
    //
    cv::Mat image = cv::imread(fileName.toStdString());
    if (image.empty())
    {
        ui->statusbar->showMessage("图像不存在！");
        label->clear();
//        image = cv::Mat::zeros(cv::Size(400,400), image.type());
        image = cv::Mat(cv::Size(400, 400), CV_8UC3, cv::Scalar(255, 255, 255));
        return image;
    }
//    else
//    {
//        ui->statusbar->showMessage("图像已读取！");
//    }
    if (image.channels() == 3)
    {
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    }
    //
//    cv::resize(image, image, cv::Size(ui->label->width(),ui->label->height()), 0, 0, cv::INTER_CUBIC);
    cv::resize(image, image, cv::Size(400,400), 0, 0, cv::INTER_CUBIC);
    QImage image_q = QImage((const unsigned char*)(image.data), image.cols, image.rows, image.cols*image.channels(), QImage::Format_RGB888);
    label->setPixmap(QPixmap::fromImage(image_q));
    //
//    emit done_select_and_show_image();
    return image;
}


void MainWindow_2::fuse_image()
{
    float weight = ui->horizontalSlider->sliderPosition() / 100.0;
    if (image1.empty() || image2.empty())
    {
        return;
    }
    else
    {
        cv::Mat image = image1*(1-weight) + image2*weight;
        QImage image_q = QImage((const unsigned char*)(image.data), image.cols, image.rows, image.cols*image.channels(), QImage::Format_RGB888);
        ui->label_3->setPixmap(QPixmap::fromImage(image_q));
    }
//    try
//    {
//        cv::Mat image = image1*(1-weight) + image2*weight;
//        QImage image_q = QImage((const unsigned char*)(image.data), image.cols, image.rows, image.cols*image.channels(), QImage::Format_RGB888);
//        ui->label_3->setPixmap(QPixmap::fromImage(image_q));
//    }
//    catch (...)
//    {
//        ui->label_3->setText("ng");
//    }
//    cv::Mat image = image1*(1-weight) + image2*weight;
//    cv::Mat image = image1;
//    QImage image_q = QImage((const unsigned char*)(image.data), image.cols, image.rows, image.cols*image.channels(), QImage::Format_RGB888);
//    ui->label_3->setPixmap(QPixmap::fromImage(image_q));
}
