#include <iostream>
#include <thread>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


void print(const boost::system::error_code& /*e*/)
{
    std::cout << "Timer expired" << std::endl;
}

MainWindow::MainWindow()
{
    ui_ = new Ui::MainWindow;
    ui_->setupUi(this);
    ioc_ = new boost::asio::io_context();
    guard_ = new work_guard_type(ioc_->get_executor());
    t_ = new std::thread([&](){ioc_->run();});
    qDebug() << "MainWindow::MainWindow()";
}

MainWindow::~MainWindow()
{
    delete ui_;
    ioc_->stop();
    qDebug() << "MainWindow::~MainWindow()";
}

void MainWindow::on_startTimerButton_clicked()
{
    qDebug() << "clicked";
    timer1_ = new boost::asio::deadline_timer (*ioc_,boost::posix_time::seconds(1));
    timer1_->async_wait(&print);
    qDebug() << "done";
}

void MainWindow::on_startHttpClientButton_clicked()
{
    QString url = ui_->urlLineEdit->text();
    sess = new session(*ioc_);
    sess->run(url.toStdString().c_str(),"8000","/");
}