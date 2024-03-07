#ifndef MAINWINDOW_4_H
#define MAINWINDOW_4_H

#include <QMainWindow>
#include <QTimer>
#include <QThread>
#include <QMessageBox>
#include "WorkThread.h"


namespace Ui {
class MainWindow_4;
}

class MainWindow_4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_4(QWidget *parent = nullptr);
    ~MainWindow_4();
    // --
    QTimer *ptimer = new QTimer(this);
    QThread *pthread = new QThread(this);
    WorkThread *pworker = new WorkThread(this);

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

private:
    Ui::MainWindow_4 *ui;
};

#endif // MAINWINDOW_4_H
