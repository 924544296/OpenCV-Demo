#include "mainwindow_7.h"
#include "ui_mainwindow_7.h"

MainWindow_7::MainWindow_7(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow_7)
{
    ui->setupUi(this);
    //
    // ui->label_2->setAlignment(Qt::AlignCenter); // 设置label文字居中
    ui->lineEdit->setEnabled(false);
    ui->textEdit->setEnabled(false);
    ui->lineEdit_4->setEnabled(false);
    ui->lineEdit_5->setEnabled(false);
}


MainWindow_7::~MainWindow_7()
{
    delete ui;
}


void MainWindow_7::on_pushButton_clicked()
{
    QSettings setting("./Setting.ini", QSettings::IniFormat);          //为了能记住上次打开的路径
    QString lastPath = setting.value("LastFilePath").toString();
    QString folder = QFileDialog::getExistingDirectory(this, "选择文件夹", lastPath);
    ui->lineEdit->setText(folder);
}


void MainWindow_7::on_pushButton_2_clicked()
{
    //
    std::string path = ui->lineEdit->text().toLocal8Bit().constData();
    // double weight = 24.0;
    if (ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty())
    {
        QMessageBox::information(this,
                                 tr("老登"),
                                 tr("有没有反思？"),
                                 QMessageBox::Ok | QMessageBox::Cancel,
                                 QMessageBox::Ok);
        return;
    }
    double weight = ui->lineEdit_2->text().toDouble();
    // double c[n];
    n = ui->lineEdit_3->text().toInt();
    double* c = new double[n];
    x = polynomial_fit(path, weight, n, c);
    delete[] c;
    //
    std::ofstream c_file("./c.txt");
    std::ostringstream c_strings;
    for (int i=0; i<n; i++)
    {
        // 设置输出流的精度
        c_strings << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10) << x(i) << std::endl;
        c_file << std::fixed << std::setprecision(std::numeric_limits<double>::max_digits10) << x(i) << std::endl;
    }
    c_file.close();
    //
    ui->textEdit->setText(QString::fromStdString(c_strings.str()));
}


void MainWindow_7::on_pushButton_3_clicked()
{
    //
    QSettings setting("./Setting.ini", QSettings::IniFormat);          //为了能记住上次打开的路径
    QString lastPath = setting.value("LastFilePath").toString();
    QString fileName = QFileDialog::getOpenFileName(this,tr("打开图像"), lastPath, tr("图像格式(*.png *.jpg *.bmp)"));
    //
    image = cv::imread(fileName.toStdString(), 1);
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
    //
    //    cv::resize(image, image, cv::Size(ui->label->width(),ui->label->height()), 0, 0, cv::INTER_CUBIC);
    QImage image_q = QImage((const unsigned char*)(image.data), image.cols, image.rows, image.cols*image.channels(), QImage::Format_RGB888);
    ui->label->setPixmap(QPixmap::fromImage(image_q));
    //
    ui->lineEdit_4->setText(fileName);
}


void MainWindow_7::on_pushButton_4_clicked()
{
    if (ui->textEdit->toPlainText().isEmpty() || ui->lineEdit_3->text().isEmpty())
    {
        QMessageBox::information(this,
                                 tr("老登"),
                                 tr("有没有反思？"),
                                 QMessageBox::Ok | QMessageBox::Cancel,
                                 QMessageBox::Ok);
        return;
    }
    n = x.size();
    double weight_predict = polynomial_predict(image.clone(), n, x);
    ui->lineEdit_5->setText(QString::number(weight_predict));
}


void MainWindow_7::get_roi(cv::Mat image, cv::Mat& thresh, cv::Mat& roi)
{
    //
    cv::threshold(image, thresh, 250, 255, cv::THRESH_BINARY_INV);
    thresh.convertTo(thresh, CV_64F, 1.0 / 255.0);
    //
    //image.convertTo(image, CV_64F, 1.0 / 255.0);
    image.convertTo(image, CV_64F);
    //
    cv::multiply(image, thresh, roi);
}


Eigen::VectorXd MainWindow_7::polynomial_fit(std::string path, double weight, int n, double* c)
{
    // read images
    std::vector<cv::Mat> images;
    std::vector<cv::String> fn;
    cv::glob(path, fn, false);
    for (int i = 0; i < fn.size(); i++) {
        images.push_back(cv::imread(fn[i], 1));
    }
    // calculate coefficients
    Eigen::MatrixXd A(images.size(), n);
    Eigen::VectorXd b(images.size());
    for (int i = 0; i < images.size(); i++)
    {
        cv::Mat image = 255 - images[i];
        image.convertTo(image, CV_64F);
        cv::Mat image_i;
        for (int j = 0; j < n; j++)
        {
            cv::pow(image, j+1, image_i);
            c[j] = cv::sum(image_i)[0];
        }
        A.row(i).segment(0, n) = Eigen::Map<Eigen::RowVectorXd>(c, n);
        b(i) = weight;
    }
    Eigen::VectorXd x = A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b);

    return x;
}


double MainWindow_7::polynomial_predict(cv::Mat image, int n, Eigen::VectorXd x)
{
    //
    image = 255 - image;
    image.convertTo(image, CV_64F);
    //
    double weight_predict = 0.0;
    cv::Mat image_i;
    for (int i = 0; i < n; i++)
    {
        cv::pow(image, i+1, image_i);
        weight_predict += cv::sum(image_i)[0] * x(i);
    }

    return weight_predict;
}
