#include "CustomWidget.h"
#include <QPropertyAnimation>

void CustomWidget::rightColorAnimation(void) {
  QPropertyAnimation* animation =
      new QPropertyAnimation(this, "backgroundColor");
  animation->setStartValue(defaultColor);
  animation->setEndValue(defaultColor);
  animation->setKeyValueAt(0.618, rightColor);
  animation->setEasingCurve(QEasingCurve::OutInQuad);
  animation->setDuration(animationTime);
  animation->start();
}

void CustomWidget::wrongColorAnimation(void) {
  QPropertyAnimation* animation =
      new QPropertyAnimation(this, "backgroundColor");
  animation->setStartValue(defaultColor);
  animation->setEndValue(defaultColor);
  animation->setKeyValueAt(0.618, wrongColor);
  animation->setEasingCurve(QEasingCurve::OutInQuad);
  animation->setDuration(animationTime);
  animation->start();
}
