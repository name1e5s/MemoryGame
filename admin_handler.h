#ifndef ADMIN_HANDLER_H
#define ADMIN_HANDLER_H

#include <user_handler.h>

class AdminHandler : public UserHandler
{
    Q_OBJECT

public:
    explicit AdminHandler(QObject *parent = nullptr);
};

#endif // ADMIN_HANDLER_H
