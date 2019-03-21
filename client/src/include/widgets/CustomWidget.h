#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H
#include <QColor>
#include <QtWidgets/QWidget>

class CustomWidget : public QWidget {
  Q_OBJECT
  Q_PROPERTY(
      QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor)
 public:
  CustomWidget(QWidget* parent = 0) : QWidget(parent) {
    setBackgroundColor(defaultColor);
  }
  ~CustomWidget() {}
  QColor getBackgroundColor() const { return backgroundColor; }
  void setBackgroundColor(QColor value) {
    backgroundColor = value;
    QPalette pal = palette();
    pal.setColor(QPalette::Background, backgroundColor);
    setAutoFillBackground(true);
    setPalette(pal);
  }
 public slots:
  void rightColorAnimation(void);
  void wrongColorAnimation(void);

 private:
  QColor backgroundColor;
  const QColor defaultColor = QColor("#616161");
  const QColor rightColor = QColor("#009688");
  const QColor wrongColor = QColor("#f44336");
  const int animationTime = 618;
};
#endif  // CUSTOMWIDGET_H
