#ifndef UTILITY_H
#define UTILITY_H
#include <QString>
#include <QVector>
#include <string>
std::string QVecQVecStrToStdStr(const QVector<QVector<QString>> &vector);
QVector<QVector<QString>> StdStrToQVecQVecStr(const std::string &string);
#if defined(__GNUC__)
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif
#endif // UTILITY_H
