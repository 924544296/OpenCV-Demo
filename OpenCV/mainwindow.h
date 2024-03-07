#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QFileDialog>
#include <opencv2/opencv.hpp>
#include <QDebug>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // --
    void imgProc();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    // --
    cv::Mat image;
    cv::Mat myImg;              //缓存图片（供程序代码引用和处理）
    QImage myQImg;
};
#endif // MAINWINDOW_H
