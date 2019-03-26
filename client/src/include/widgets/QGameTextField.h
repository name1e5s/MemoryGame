#ifndef QGAMETEXTFIELD_H
#define QGAMETEXTFIELD_H
#include <data/Word.h>
#include <qtmaterialtextfield.h>

class QGameTextField : public QLineEdit {
  Q_OBJECT
  Q_PROPERTY(QString answer READ getAnswer WRITE setAnswer)
  Q_PROPERTY(int alpha READ getAlpha WRITE setAlpha)

 public:
  QGameTextField(QWidget* parent = 0) : QLineEdit(parent) {
    this->setEnabled(false);
    connect(this, &QGameTextField::returnPressed, this,
            &QGameTextField::checkAnswer);
  }
  ~QGameTextField() {}

  QString getAnswer() const;
  void setAnswer(const QString& value);

  int getAlpha() const;
  void setAlpha(int value);
  void setDifficulty(int dif) {
    difficulty = dif;
    newWord();
  }
  void newWord() {
    setAnswer(
        QString::fromStdString(Word::Instance().nextWord(difficulty).word));
  }

 public slots:
  void gameOver();
  void checkAnswer();
  void gameStart();
  void hideAnswer();
  void showAnswerAnimation();
  void hideAnswerAnimation();

 signals:
  void right();
  void wrong();

 private:
  QString answer;
  int difficulty;
  int alpha;
};

#endif  // QGAMETEXTFIELD_H
