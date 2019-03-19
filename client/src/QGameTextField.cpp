#include <QPropertyAnimation>
#include <QTimer>

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

void QGameTextField::showAnswer() {
  setEnabled(false);
  showAnswerAnimation();
  QTimer::singleShot(618 * (4 - difficulty), this, SLOT(hideAnswerAnimation()));
}

void QGameTextField::gameOver() {
  setEnabled(false);
  setText("Game Over :)");
  setAlpha(0);
  QPropertyAnimation* animation = new QPropertyAnimation(this, "alpha");
  animation->setStartValue(0);
  animation->setEndValue(255);
  animation->setDuration(157);
  animation->setEasingCurve(QEasingCurve::OutSine);

  animation->start();
}

void QGameTextField::showAnswerAnimation() {
  setAlpha(0);
  QPropertyAnimation* animation = new QPropertyAnimation(this, "alpha");
  animation->setStartValue(0);
  setText(answer);
  animation->setEndValue(255);
  animation->setDuration(157);
  animation->setEasingCurve(QEasingCurve::OutSine);

  animation->start();
}

void QGameTextField::hideAnswerAnimation() {
  QPropertyAnimation* animation = new QPropertyAnimation(this, "alpha");
  animation->setStartValue(255);
  animation->setEndValue(0);
  animation->setDuration(157);
  animation->setEasingCurve(QEasingCurve::InSine);

  animation->start();
  QTimer::singleShot(157, this, SLOT(hideAnswer()));
}

void QGameTextField::hideAnswer() {
  setText("");
  setAlpha(255);
  setEnabled(true);
  setFocus(Qt::OtherFocusReason);
}

int QGameTextField::getAlpha() const {
  return alpha;
}

void QGameTextField::setAlpha(int value) {
  alpha = value;
  setStyleSheet(
      QString(
          "background:transparent; border: none;color: rgba(255,255,255,%1);")
          .arg(value));
}
