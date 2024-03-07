#include "mainwindow_3.h"
#include "ui_mainwindow_3.h"

MainWindow_3::MainWindow_3(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_3)
{
    ui->setupUi(this);
    // --
    ui->comboBox->addItem("均值");
    ui->comboBox->addItem("高斯");
    ui->comboBox->addItem("中值");
    ui->comboBox->addItem("双边");
    ui->label->setScaledContents(true);
    ui->label_2->setScaledContents(true);
}

MainWindow_3::~MainWindow_3()
{
    delete ui;
}

void MainWindow_3::on_pushButton_clicked()
{
    //
    QSettings setting("./Setting.ini", QSettings::IniFormat);          //为了能记住上次打开的路径
    QString lastPath = setting.value("LastFilePath").toString();
    QString fileName = QFileDialog::getOpenFileName(this,tr("打开图像"), lastPath, tr("图像格式(*.png *.jpg *.bmp)"));
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


void MainWindow_3::on_pushButton_2_clicked()
{
    cv::Mat image2;
    switch (ui->comboBox->currentIndex())
    {
    case 0:
    {
        cv::blur(image, image2, cv::Size(3,3), cv::Point(-1,-1));
        break;
    }
    case 1:
    {
        cv::GaussianBlur(image, image2, cv::Size(3,3), 0, 0);
        break;
    }
    case 2:
    {
        cv::medianBlur(image, image2, 3);
        break;
    }
    case 3:
    {
        cv::bilateralFilter(image, image2, 3, 3*2, 3/2);
        break;
    }
    }
    QImage image_q = QImage((const unsigned char*)(image2.data), image2.cols, image2.rows, image2.cols*image2.channels(), QImage::Format_RGB888);
    ui->label_2->setPixmap(QPixmap::fromImage(image_q));
}

