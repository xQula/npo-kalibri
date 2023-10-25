#include "myfile.h"

MyFile::MyFile(QObject *parent): QObject{parent}
{
    file_ = new QFile();
}

MyFile::~MyFile()
{
    delete file_;
}

void MyFile::set_name_file(const QString &name)
{
   file_->setFileName(name);
}

void MyFile::read_file()
{
    check_is_open_file();
    if(!(file_->open(QIODevice::ReadOnly | QIODevice::Text))){
        emit sig_send_message_box("Не открывается файл " + file_->fileName());
    }
    QTextStream in(file_);
    QString data;
    data = in.readAll();
    file_->close();
    emit sig_send_data_file(data);
}

void MyFile::write_file(const QString &data)
{
    check_is_open_file();
    if(!(file_->open(QIODevice::WriteOnly | QIODevice::Text))){
        emit sig_send_message_box("Не открывается файл " + file_->fileName());
    }
    QTextStream in(file_);
    in << data;
    file_->close();
}

void MyFile::clear_file()
{
    check_is_open_file();
    file_->open(QIODevice::WriteOnly | QIODevice::Truncate);
    file_->close();
}

void MyFile::check_exsist_file()
{
    if(!(file_->exists())){
        emit sig_send_message_box("Не существует такого файл " + file_->fileName());
    }
}

void MyFile::check_is_open_file()
{
    if(file_->isOpen()){
        emit sig_send_message_box("Файл открыт" + file_->fileName());
    }
}
