#include "Gamers.h"
#include "ui_Gamers.h"

#include <data/login.h>

Gamers::Gamers(QWidget* parent) : QDialog(parent), ui(new Ui::Gamers) {
  ui->setupUi(this);
  QSqlQueryModel* model = new QSqlQueryModel(this);
  Login::Instance().getGamers(model);
  ui->gamerTableView->setModel(model);
  ui->gamerTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->gamerTableView->setShowGrid(false);
  ui->gamerTableView->setSelectionMode(QAbstractItemView::NoSelection);
}

Gamers::~Gamers() {
  delete ui;
}
