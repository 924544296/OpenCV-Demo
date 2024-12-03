#ifndef MAINWINDOW_7_H
#define MAINWINDOW_7_H

#include <QMainWindow>
#include <QFileDialog>
#include <QSettings>
#include <QMessageBox>
#include <fstream>
#include <iomanip>
#include <limits>
#include "Eigen/Dense"
#include <opencv2/opencv.hpp>


namespace Ui {
class MainWindow_7;
}

class MainWindow_7 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_7(QWidget *parent = nullptr);
    ~MainWindow_7();
    //
    void get_roi(cv::Mat image, cv::Mat& thresh, cv::Mat& roi);
    Eigen::VectorXd polynomial_fit(std::string path, double weight, int n, double* c);
    double polynomial_predict(cv::Mat image, int n, Eigen::VectorXd x);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow_7 *ui;
    //
    cv::Mat image;
    int n;
    Eigen::VectorXd x;
};

#endif // MAINWINDOW_7_H
