#ifndef MYBITE_H
#define MYBITE_H

#include <QObject>
#include <QByteArray>
#include <QString>

class MyBite : public QObject
{
    Q_OBJECT
public:
    MyBite(QObject *parent = nullptr);
    ~MyBite();
    void processing_bits_xor(const QString &data_8byte, const QString &data_in_file);
signals:
    void sig_send_end_processing_byte(const QString &data);
};

#endif // MYBITE_H
