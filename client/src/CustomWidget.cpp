#include <QPropertyAnimation>

#include "CustomWidget.h"

void CustomWidget::rightColorAnimation(void) {
  QPropertyAnimation* animation =
      new QPropertyAnimation(this, "backgroundColor");
  animation->setEndValue(defaultColor);
  animation->setKeyValueAt(0.618, rightColor);
  animation->setEasingCurve(QEasingCurve::OutInQuad);
  animation->setDuration(animationTime);
  animation->start();
}

void CustomWidget::wrongColorAnimation(void) {
  QPropertyAnimation* animation =
      new QPropertyAnimation(this, "backgroundColor");
  animation->setEndValue(defaultColor);
  animation->setKeyValueAt(0.618, wrongColor);
  animation->setEasingCurve(QEasingCurve::OutInQuad);
  animation->setDuration(animationTime);
  animation->start();
}
