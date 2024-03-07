#ifndef MAINWINDOW_5_H
#define MAINWINDOW_5_H

#include <QMainWindow>
#include <QThread>
#include <QSettings>
#include <QFileDialog>
#include <opencv2/opencv.hpp>
#include "workthread.h"


namespace Ui {
class MainWindow_5;
}

class MainWindow_5 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_5(QWidget *parent = nullptr);
    ~MainWindow_5();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow_5 *ui;
    // --
    cv::Mat image_lr;
    cv::dnn::Net net;
    WorkThread *pworker = new WorkThread;
    QThread *pthread = new QThread;

signals:
    void start_lr2sr();
};

#endif // MAINWINDOW_5_H
