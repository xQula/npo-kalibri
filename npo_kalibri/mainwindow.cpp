#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my_byte = new MyBite(this);
    my_file_in = new MyFile(this);
    my_file_out = new MyFile(this);
    message_box_ = new QMessageBox(this);
    timer_ = new QTimer(this);

    connect(my_file_out, &MyFile::sig_send_message_box, this, &MainWindow::sl_send_message_box);
    connect(my_file_in, &MyFile::sig_send_message_box, this, &MainWindow::sl_send_message_box);
    connect(my_file_in, &MyFile::sig_send_data_file,  this, &MainWindow::sl_send_data_byte);
    connect(my_byte, &MyBite::sig_send_end_processing_byte, this, &MainWindow::sl_send_file_out);
    connect(timer_, &QTimer::timeout, this, &MainWindow::start_this_program);

    ui->le_timer->setEnabled(false);
    ui->le_bit->setMaxLength(8);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check_all_fields()
{
    if(ui->le_bit->text() == ""){
        sl_send_message_box("Нет данных в поле 8 бит");
    }
    if(ui->le_inFormat->text() == ""){
        sl_send_message_box("Нет пути к входным данным");
    }
    if(ui->le_outFormat->text() == ""){
        sl_send_message_box("Нет пути к сохранениям");

    }if(ui->chb_startTimer->isChecked()){
        if(ui->le_timer->text() == ""){
            sl_send_message_box("Не установленно время");
        }
        start_timer();
    }
}

void MainWindow::sl_send_message_box(const QString &str)
{
    message_box_->setIcon(QMessageBox::Critical);
    message_box_->setText(str);
    message_box_->setStandardButtons(QMessageBox::Ok);
    message_box_->show();
    if(message_box_->exec() == QMessageBox::Ok){
        QApplication::exit(EXIT_FAILURE);
    }
}

void MainWindow::sl_send_data_byte(const QString &data)
{
    my_byte->processing_bits_xor(ui->le_bit->text(), data);
}

void MainWindow::sl_send_file_out(const QString &data)
{
    my_file_out->set_name_file(ui->le_outFormat->text() + ui->cb_outFormat->currentText());
    my_file_out->write_file(data);
}

void MainWindow::start_this_program()
{
    check_all_fields();
    check_equality_names();
    my_file_in->set_name_file(ui->le_inFormat->text() + ui->cb_inFormat->currentText());
    my_file_in->check_exsist_file();
    my_file_in->read_file();
    if(ui->chb_clearInData->isChecked()){
        my_file_in->clear_file();
    }
}

void MainWindow::start_timer()
{
    timer_->setInterval(ui->le_timer->text().toInt());
    timer_->start();
}

void MainWindow::check_equality_names()
{
    if(ui->le_inFormat->text() == ui->le_outFormat->text()){
        ui->le_outFormat->setText(ui->le_inFormat->text() + "1");
    }
}

void MainWindow::on_chb_startTimer_stateChanged(int arg1)
{
    if(ui->chb_startTimer->isChecked()){
        ui->le_timer->setEnabled(true);
    }else{
        ui->le_timer->setEnabled(false);
    }
}

void MainWindow::on_pb_start_clicked()
{
    start_this_program();
    ui->chb_startTimer->setEnabled(false);
    ui->chb_clearInData->setEnabled(false);
}


void MainWindow::on_pb_stop_clicked()
{
    if(timer_->isActive()){
        timer_->stop();
    }
    ui->chb_startTimer->setEnabled(true);
    ui->chb_clearInData->setEnabled(true);
}

