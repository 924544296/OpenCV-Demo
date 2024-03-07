#ifndef MAINWINDOW_6_H
#define MAINWINDOW_6_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include <QFileDialog>
#include <QMessageBox>
#include "workthread.h"


namespace Ui {
class MainWindow_6;
}

class MainWindow_6 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_6(QWidget *parent = nullptr);
    ~MainWindow_6();
    // --
    QTimer *ptimer = new QTimer(this);
    QThread *pthread = new QThread(this);
    WorkThread *pworker = new WorkThread(this);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow_6 *ui;
    // --
    double *pframeCount = new double;
    double *pfps = new double;
};

#endif // MAINWINDOW_6_H
