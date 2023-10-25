#include "mybite.h"

MyBite::MyBite(QObject *parent): QObject{parent}
{
}

MyBite::~MyBite()
{
}

void MyBite::processing_bits_xor(const QString &data_8byte, const QString &data_in_file)
{
    QByteArray byte_in_file = data_in_file.toUtf8();
    for(auto &i: byte_in_file){
        i ^= data_8byte.toInt();
    }
    emit sig_send_end_processing_byte(QString(byte_in_file));
}
\
