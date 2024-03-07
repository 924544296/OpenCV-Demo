#ifndef MAINWINDOW_3_H
#define MAINWINDOW_3_H

#include <QMainWindow>
#include <QSettings>
#include <QFileDialog>
#include <opencv2/opencv.hpp>


namespace Ui {
class MainWindow_3;
}

class MainWindow_3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_3(QWidget *parent = nullptr);
    ~MainWindow_3();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow_3 *ui;
    // --
    cv::Mat image;
};

#endif // MAINWINDOW_3_H
