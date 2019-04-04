#include "Gamers.h"
#include "ui_Gamers.h"

#include <data/User.h>

Gamers::Gamers(QWidget* parent) : QDialog(parent), ui(new Ui::Gamers) {
  ui->setupUi(this);
  QSqlQueryModel* model = new QSqlQueryModel(this);
  Login::Instance().getGamers(model);
  QSortFilterProxyModel* proxy = new QSortFilterProxyModel(this);
  proxy->setSourceModel(model);

  ui->gamerTableView->setModel(proxy);
  ui->gamerTableView->horizontalHeader()->setSectionResizeMode(
      QHeaderView::Stretch);
  ui->gamerTableView->verticalHeader()->hide();
  ui->gamerTableView->setSortingEnabled(true);
  ui->gamerTableView->setShowGrid(false);
  ui->gamerTableView->setSelectionMode(QAbstractItemView::NoSelection);

  connect(ui->close, &QPushButton::clicked, this, &Gamers::accept);

  setFixedSize(this->width(), this->height());
}

Gamers::~Gamers() {
  delete ui;
}
