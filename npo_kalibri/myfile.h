#ifndef MYFILE_H
#define MYFILE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>

class MyFile : public QObject
{
    Q_OBJECT
public:
    MyFile(QObject *parent = nullptr);
    ~MyFile();
    void set_name_file(const QString &name);
    void read_file();
    void write_file(const QString &data);
    void clear_file();
    void check_exsist_file();
    void check_is_open_file();
signals:
    void sig_send_message_box(const QString &message);
    void sig_send_data_file(const QString &data);
private:
    QFile *file_;
};

#endif // MYFILE_H
