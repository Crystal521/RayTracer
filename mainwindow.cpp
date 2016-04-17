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
    //���ô��ڴ�С

	//������Ⱦ
    wr.Build();
	wr.pCamera->RenderScene(wr);
	
    //����ͼ����ʾλ��
    ui->view->setPixmap(QPixmap::fromImage(*(wr.renderArea)));
    ui->view->setFrameShape(QFrame::Box);
    ui->view->show();
}

MainWindow::~MainWindow()
{
	delete ui;
}
