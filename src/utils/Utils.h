#ifndef UTILS_H
#define UTILS_H
#include <QObject>
#include <QDateTime>

struct Message{
    QString id;
    QString user;
    QString content;
    QDateTime timestamp;
};

#endif // UTILS_H
