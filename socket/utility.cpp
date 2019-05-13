#include "utility.h"

std::string QVecQVecStrToStdStr(const QVector<QVector<QString>> &vector) {
  QString qString;
  for (int i = 0; i < vector.size(); i++) {
    for (int j = 0; j < vector.at(i).size(); j++) {
      qString.append(vector.at(i).at(j));
      if (j != vector.at(i).size() - 1)
        qString.append("$");
    }
    if (i != vector.size() - 1)
      qString.append("&");
  }
  return qString.toStdString();
}

QVector<QVector<QString>> StdStrToQVecQVecStr(const std::string &string) {
  QVector<QVector<QString>> result;
  if (string == "") {
    return result;
  }
  QStringList list = QString::fromStdString(string).split('&');
  for (int i = 0; i < list.size(); i++) {
    QVector<QString> tempVec;
    QStringList temp = list.at(i).split('$');
    for (int j = 0; j < temp.size(); j++) {
      tempVec.push_back(temp.at(j));
    }
    result.push_back(tempVec);
  }
  return result;
}
