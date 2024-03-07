#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // --
    ui->label->setScaledContents(true);
    ui->verticalSlider->setMinimum(0);
    ui->verticalSlider->setMaximum(100);
    ui->verticalSlider->setValue(50);
    ui->verticalSlider_2->setMinimum(0);
    ui->verticalSlider_2->setMaximum(100);
    ui->verticalSlider_2->setValue(50);
    connect(ui->verticalSlider, &QSlider::sliderMoved, this, &MainWindow::imgProc);
    connect(ui->verticalSlider, &QSlider::valueChanged, this, &MainWindow::imgProc);
    connect(ui->verticalSlider_2, &QSlider::sliderMoved, this, &MainWindow::imgProc);
    connect(ui->verticalSlider_2, &QSlider::valueChanged, this, &MainWindow::imgProc);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    //
    QSettings setting("./Setting.ini", QSettings::IniFormat);          //为了能记住上次打开的路径
    QString lastPath = setting.value("LastFilePath").toString();
    QString fileName = QFileDialog::getOpenFileName(this,tr("打开图像"), lastPath, tr("图像格式(*.png *.jpg *.bmp)"));
    //
    ui->lineEdit->setText(fileName);
    //
    image = cv::imread(fileName.toStdString());
    if (image.empty())
    {
        ui->statusbar->showMessage("图像不存在！");
        ui->label->clear();
        return;
    }
    else
    {
        ui->statusbar->showMessage("图像已读取！");
    }
    if (image.channels() == 3)
    {
        cv::cvtColor(image, image, cv::COLOR_BGR2RGB);
    }
    //
//    cv::resize(image, image, cv::Size(ui->label->width(),ui->label->height()), 0, 0, cv::INTER_CUBIC);
    QImage image_q = QImage((const unsigned char*)(image.data), image.cols, image.rows, image.cols*image.channels(), QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image_q));
}


void MainWindow::imgProc()
{
    float con = ui->verticalSlider->sliderPosition() / 33.3;
    int bri = ui->verticalSlider_2->sliderPosition();
    cv::Mat imgSrc = image;
    cv::Mat imgDst = cv::Mat::zeros(imgSrc.size(), imgSrc.type());
    imgSrc.convertTo(imgDst, -1, con, bri);
    //执行运算imgDst(i, j) = con * imgSrc(i, j) + bri
    /*
    for( int i = 0; i < imgSrc.rows; i++)
    {
        for( int j = 0; j < imgSrc.cols; j++)
        {
            for(int c = 0; c < 3; c++)
            {
                imgDst.at<Vec3b>(i, j)[c] = saturate_cast<uchar>(con * (imgSrc.at<Vec3b>(i, j)[c]) + bri);
            }
        }
    }
    */
    QImage image_q = QImage((const unsigned char*)(imgDst.data), imgDst.cols, imgDst.rows, imgDst.cols*imgDst.channels(), QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image_q));
}
