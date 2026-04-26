#include "MultiTCPServer.h"

#include <arpa/inet.h>   // sockaddr_in, inet_ntoa
#include <sys/socket.h>  // socket, bind, listen, accept
#include <unistd.h>      // close(server)

#include <iostream>
#include "ExampleRegistry.h"

void MultiTCPServer::acceptLoop() {
  while (isRunning()) {
    sockaddr_in client_addr{};
    socklen_t client_add_len = sizeof(client_addr);

    int client_fd =
        accept(getServerFD(), reinterpret_cast<sockaddr*>(&client_addr),
               &client_add_len);

    if (client_fd < 0) {
      if (!isRunning())
        break;
      std::cerr << "[MultiTCPServer] accept failed\n";
      continue;
    }

    std::cout << "[MultiTCPServer] client " << inet_ntoa(client_addr.sin_addr)
              << " connected\n";

    client_threads_.emplace_back([this, client_fd]() {
      try {
        handleClient(client_fd);
      } catch (const std::exception& e) {
        std::cerr << "[MultiTCPServer] client error: " << e.what() << "\n";
        close(client_fd);
      }
    });
  }

  for (auto& t : client_threads_) {
    if (t.joinable()) {
      t.join();
    }
  }
}

void MultiTCPServer::run() {
  setPort(8080);

  try {
    start();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    stop();
  }
}

REGISTER_EXAMPLE(MultiTCPServer, "socket/tcp", "MultiTCPServer");