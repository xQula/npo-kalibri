#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include "mybite.h"
#include "myfile.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void check_all_fields();
    void start_this_program();
    void start_timer();
    void check_equality_names();

private slots:
    void on_chb_startTimer_stateChanged(int arg1);
    void on_pb_start_clicked();
    void sl_send_message_box(const QString &str);
    void sl_send_data_byte(const QString &data);
    void sl_send_file_out(const QString &data);

    void on_pb_stop_clicked();

private:
    QMessageBox *message_box_;
    Ui::MainWindow *ui;
    MyBite *my_byte;
    MyFile *my_file_out;
    MyFile *my_file_in;
    QTimer *timer_;
};
#endif // MAINWINDOW_H
