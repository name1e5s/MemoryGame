#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
#include <QVector>
#include <string>
std::string QVecQVecStrToStdStr(const QVector<QVector<QString>> &vector);
QVector<QVector<QString>> StdStrToQVecQVecStr(const std::string &string);
#endif // UTILITY_H
