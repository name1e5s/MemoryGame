#include "QGameTextField.h"

QString QGameTextField::getAnswer() const {
  return answer;
}

void QGameTextField::setAnswer(const QString& value) {
  answer = value;
}

void QGameTextField::checkAnswer() {
  if (QString::compare(text(), getAnswer(), Qt::CaseInsensitive)) {
    // Wrong Answer
    emit wrong();
  } else {
    emit right();
  }
  setText("");
}
