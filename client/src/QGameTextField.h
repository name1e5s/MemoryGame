#ifndef QGAMETEXTFIELD_H
#define QGAMETEXTFIELD_H
#include <qtmaterialtextfield.h>

class QGameTextField : public QLineEdit {
  Q_OBJECT
  Q_PROPERTY(QString answer READ getAnswer WRITE setAnswer)
  Q_PROPERTY(int alpha READ getAlpha WRITE setAlpha)

 public:
  QGameTextField(QWidget* parent = 0) : QLineEdit(parent) {
    connect(this, &QGameTextField::returnPressed, this,
            &QGameTextField::checkAnswer);
  }
  ~QGameTextField() {}

  QString getAnswer() const;
  void setAnswer(const QString& value);

  int getAlpha() const;
  void setAlpha(int value);

 public slots:
  void checkAnswer();
  void showAnswer();
  void hideAnswer();
  void hideAnswerAnimation();

 signals:
  void right();
  void wrong();

 private:
  QString answer;
  int alpha;
};

#endif  // QGAMETEXTFIELD_H
