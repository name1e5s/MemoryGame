#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H
#include <socket_client.h>
#include <vector>

namespace RequestHandler {
extern std::vector<SocketClient *> clients;
void initilizeClient(SocketClient *client);
} // namespace RequestHandler
#endif // REQUEST_HANDLER_H
