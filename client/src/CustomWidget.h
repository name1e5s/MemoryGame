#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H
#include <QColor>
#include <QtWidgets/QWidget>

class CustomWidget : public QWidget {
  Q_OBJECT
  Q_PROPERTY(
      QColor backgroundColor READ getBackgroundColor WRITE setBackgroundColor)
 public:
  CustomWidget(QWidget* parent = 0)
      : QWidget(parent), backgroundColor(QColor("#000000")) {}
  ~CustomWidget() {}
  QColor getBackgroundColor() const { return backgroundColor; }
  void setBackgroundColor(QColor value) {
    backgroundColor = value;
    QPalette pal = palette();
    pal.setColor(QPalette::Background, backgroundColor);
    setAutoFillBackground(true);
    setPalette(pal);
  }

 private:
  QColor backgroundColor;
};
#endif  // CUSTOMWIDGET_H
