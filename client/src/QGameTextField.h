#ifndef QGAMETEXTFIELD_H
#define QGAMETEXTFIELD_H
#include <qtmaterialtextfield.h>

class QGameTextField : public QLineEdit {
  Q_OBJECT
  Q_PROPERTY(QString answer READ getAnswer WRITE setAnswer)
 public:
  QGameTextField(QWidget* parent = 0) : QLineEdit(parent) {
    connect(this, &QGameTextField::returnPressed, this,
            &QGameTextField::checkAnswer);
  }
  ~QGameTextField() {}

  QString getAnswer() const;
  void setAnswer(const QString& value);

 public slots:
  void checkAnswer();

 signals:
  void right();
  void wrong();

 private:
  QString answer;
};

#endif  // QGAMETEXTFIELD_H
