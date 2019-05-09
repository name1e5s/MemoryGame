#ifndef DB_MODEL_H
#define DB_MODEL_H
#include <table_model.h>

class UserTableModel : public QmlAbstractTableModel
{
    Q_OBJECT

public:
    explicit UserTableModel(QObject *parent = nullptr);
    Q_INVOKABLE void searchGamer(QString query);
    Q_INVOKABLE void searchAdmin(QString query);
};
#endif // DB_MODEL_H
