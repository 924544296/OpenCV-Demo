#ifndef MAINWINDOW_2_H
#define MAINWINDOW_2_H

#include <QMainWindow>
#include <QLineEdit>
#include <QLabel>
#include <QSettings>
#include <QFileDialog>
#include <QTimer>
#include <opencv2/opencv.hpp>


namespace Ui {
class MainWindow_2;
}

class MainWindow_2 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_2(QWidget *parent = nullptr);
    ~MainWindow_2();
    // --
    cv::Mat select_and_show_image(QLineEdit *lineEdit, QLabel *label);
    void fuse_image();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow_2 *ui;
    // --
    cv::Mat image1 = cv::Mat(cv::Size(400, 400), CV_8UC3, cv::Scalar(255, 255, 255));
    cv::Mat image2 = cv::Mat(cv::Size(400, 400), CV_8UC3, cv::Scalar(255, 255, 255));
//    cv::Mat image2 = cv::Mat(cv::Size(400, 400), CV_8UC3, cv::Scalar(0, 0, 0));
    QTimer *ptimer = new QTimer;

signals:
    void done_select_and_show_image();
};

#endif // MAINWINDOW_2_H
