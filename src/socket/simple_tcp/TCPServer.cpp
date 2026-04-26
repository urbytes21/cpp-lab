#include "TCPServer.h"

#include <arpa/inet.h>   // sockaddr_in, inet_ntoa
#include <sys/socket.h>  // socket, bind, listen, accept
#include <unistd.h>      // close(server)

#include <iostream>

TCPServer::TCPServer(uint16_t port) : port_{port} {}

TCPServer::~TCPServer() {
  if (server_fd_ >= 0) {
    close(server_fd_);
  }
}

void TCPServer::createSocket() {
  // create the TCP socket (file descriptor IPv4 + stream socket)
  server_fd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd_ < 0) {
    throw std::runtime_error("socket creation failed");
  }

  // allow the port to be reused immediately after the server stop
  // otherwise, the OS may keep the port reserved for 60 seconds
  int reuse = 1;
  if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) <
      0) {
    throw std::runtime_error("setsockopt(SO_REUSEADDR) failed");
  }
}

void TCPServer::bindSocket() const {
  sockaddr_in server_addr{};
  server_addr.sin_family = AF_INET;  // IPv4
  // server_addr.sin_addr.s_addr = INADDR_ANY;  // accept connections on all network interfaces
  // e.g. if the machine has multiple IP addresses:
  //   127.0.0.1     (localhost / loopback)
  //   192.168.1.50  (LAN IP)
  // binding with INADDR_ANY means the server will listen on ALL of them.
  //
  // If we instead bind to 127.0.0.1, the server only accepts connections
  // from the same machine (localhost).
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(port_);  // onvert port to network byte order

  // associate the socket with the address/port
  if (bind(server_fd_, reinterpret_cast<sockaddr*>(&server_addr),
           sizeof(server_addr)) < 0) {
    throw std::runtime_error(
        "bind failed");  // TODO(phong-nguyen): anyway to know what kind of the error
  }

  std::cout << "Server running on " << inet_ntoa(server_addr.sin_addr) << ":"
            << ntohs(server_addr.sin_port) << "\n";
}

void TCPServer::listenSocket() const {
  // (128) is the maximum number of queued connection requests
  if (listen(server_fd_, 128) < 0) {
    throw std::runtime_error("listen failed");
  }

  std::cout << "[TCPServer] listening on port " << port_ << "\n";
}

void TCPServer::acceptLoop() {
  while (running_) {
    sockaddr_in client_addr{};
    socklen_t client_add_len = sizeof(client_addr);

    // this block until a client connect
    int client_fd = accept(
        server_fd_, reinterpret_cast<sockaddr*>(&client_addr), &client_add_len);

    if (client_fd < 0) {  // connection failed
      std::cerr << "[TCPServer] accept failed\n";
      continue;
    }

    std::cout << "[TCPServer] client " << inet_ntoa(client_addr.sin_addr)
              << " connected\n";

    try {
      handleClient(client_fd);
    } catch (const std::exception& e) {
      std::cerr << "[TCPServer] client error: " << e.what() << "\n";
      close(client_fd);
    }
  }
}

void TCPServer::sendAll(int fd, const char* data, size_t len) {
  size_t total = 0;
  while (total < len) {
    ssize_t sent = send(fd, data + total, len - total, 0);
    if (sent <= 0) {
      throw std::runtime_error("send failed");
    }
    total += sent;
  }
}

void TCPServer::handleClient(int client_fd) const {
  char buffer[1024];

  // send a notify to the client
  std::string welcome = "Connected to the TCP Server on port " +
                        std::to_string(port_) +
                        "\nType 'Q' to stop the connection.\n";

  sendAll(client_fd, welcome.c_str(), welcome.size());

  while (true) {
    // receive data from the client
    int bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);

    if (bytes == 0) {  // : client closed connection
      std::cout << "[TCPServer] client closed connection\n";
      break;
    }

    if (bytes < 0) {  // : error
      throw std::runtime_error("recv failed");
    }

    buffer[bytes] = '\0';

    // print out
    std::cout << "client " << client_fd << ": " << buffer;

    sendAll(client_fd, buffer, bytes);

    // stop connection if client sends 'Q'
    std::string line(buffer, bytes);
    line.erase(line.find_last_not_of("\r\n") + 1);  // remove \r\n
    if (line == "Q") {
      std::cout << "[TCPServer] client disconnected\n";
      break;
    }
  }

  // close connection after the client session end
  close(client_fd);
}

void TCPServer::start() noexcept(false) {
  std::cout << "[TCPServer] Starting...\n";
  createSocket();
  bindSocket();
  listenSocket();

  running_ = true;

  acceptLoop();
}

void TCPServer::stop() {
  if (running_) {
    // how to close client
    close(server_fd_);
    running_ = false;
  }
}

uint16_t TCPServer::getPort() const {
  return port_;
}

void TCPServer::setPort(uint16_t port) {
  if (!running_) {
    port_ = port;
  }
}

bool TCPServer::isRunning() const {
  return running_;
}

int TCPServer::getServerFD() const {
  return server_fd_;
}

void TCPServer::setServerFD(int fd) {
  server_fd_ = fd;
}