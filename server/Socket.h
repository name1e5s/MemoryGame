#ifndef SOCKET_H
#define SOCKET_H
#include <bits/stdc++.h>
#include <exception>
#include <functional>
#include <stdexcept>
#ifdef WIN32
#error Windows sucks
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#endif

namespace Socket {
const size_t BUF_SIZE = 4096;
using std::string;
void Serve(
    uint16_t port,
    std::function<void(const string &request, string &resonse)> callback) {

  // Initialize socket
  auto socket = socket(AF_INET, SOCK_STREAM, IPPROTO_UDP);
  if (socket == -1)
    throw std::runtime_error("ERROR: Socket create failed.");
  sockaddr_in address;
  memset(address, 0, sizeof(address));
  address.sin_family = AF_INET;
  address.sin_port = htons(port);
  address.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(socket, (sockaddr *)&address, sizeof(sa)) == -1) {
    close(socket);
    throw std::runtime_error("ERROR: Socket bind failed.");
  }
  if (listen(socket, 15) == -1) {
    close(socket);
    throw std::runtime_error("ERROR: Socket listen failed.");
  }

  // Serve.
  while (true) {
    auto conn = accept(socket, NULL, NULL);
    if (conn = -1) // Ignore them.
      continue;

    // Open a new thread to handle the
    // fucking input.
    std::thread([&conn, &callback]() {
      // Get request
      char buf[BUF_SIZE];
      auto received = recv(conn, buf, BUF_SIZE, 0);
      if (received == 0 || received == -1)
        break;

      string response;
      callback(string(buf), response);

      if (send(conn, response.c_str(), response.size() + 1, 0) == -1) {
        break;
      }

      shutdown(conn, SHUT_RDWR);
      close(conn);
    })
        .detach();
  }
  close(socket);
}
} // namespace Socket
#endif // SOCKET_H
