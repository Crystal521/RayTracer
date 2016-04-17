#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPixmap>
#include <QSize>
#include <QLabel>
#include <QTime>
#include <QFrame>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
    //设置窗口大小

	//调用渲染
    wr.Build();
	wr.pCamera->RenderScene(wr);
	
    //设置图形显示位置
    ui->view->setPixmap(QPixmap::fromImage(*(wr.renderArea)));
    ui->view->setFrameShape(QFrame::Box);
    ui->view->show();
}

MainWindow::~MainWindow()
{
	delete ui;
}
