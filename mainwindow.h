#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

#include <boost/asio.hpp>
#include "http_client.h"

using work_guard_type = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow
{
Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

public slots:
    void on_startTimerButton_clicked();
    void on_startHttpClientButton_clicked();

private:
    Ui::MainWindow *ui_;
    std::thread *t_;
    boost::asio::io_context *ioc_;
    work_guard_type *guard_;
    boost::asio::deadline_timer *timer1_ = nullptr;
    session *sess;
};

#endif // MAINWINDOW_H