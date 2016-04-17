#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "World.h"

namespace Ui {
class MainWindow;
}

using namespace std;


class MainWindow: public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();

    World wr;
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
