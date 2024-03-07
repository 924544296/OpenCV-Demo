//#include "mainwindow.h"
#include "form.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    MainWindow *w = new MainWindow;
    Form *w = new Form;
    w->show();
    return a.exec();
    delete w;
}
