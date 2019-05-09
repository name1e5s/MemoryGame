#ifndef GAMER_HANDLER_H
#define GAMER_HANDLER_H

#include <QObject>
#include <common.h>
#include <user_handler.h>

class GamerHandler : public UserHandler
{
    Q_OBJECT

public:
    explicit GamerHandler(QObject *parent = nullptr);
    Q_INVOKABLE QString getNewWord(int difficulty);
};

#endif // GAMER_HANDLER_H
