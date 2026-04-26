#include "TCPClient.h"

#include <sys/socket.h>
#include <stdexcept>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

TCPClient::TCPClient(const std::string& host, uint16_t port)
    : host_{host}, port_{port}, client_fd_{-1} {}

bool TCPClient::connect() {
  client_fd_ = socket(AF_INET, SOCK_STREAM, 0);
  if (client_fd_ < 0) {
    throw std::runtime_error("socket failed.");
  }

  // specifying the address
  sockaddr_in server_address{};
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(port_);

  // serverAddress.sin_addr.s_addr = INADDR_ANY;
  if (::inet_pton(AF_INET, host_.c_str(), &server_address.sin_addr) <= 0) {
    throw std::runtime_error("invalid address");
  }

  // sending connection request
  return (
      ::connect(client_fd_,
                reinterpret_cast<sockaddr*>(&server_address),  // global syscall
                sizeof(server_address)) == 0);
}

void TCPClient::send(const std::string& msg) const {
  if (client_fd_ < 0) {
    throw std::runtime_error("socket not connected");
  }

  const char* data = msg.c_str();
  size_t total = 0;
  size_t len = msg.size();
  while (total < len) {
    ssize_t sent = ::send(client_fd_, data + total, len - total, 0);
    if (sent <= 0) {
      throw std::runtime_error("send failed");
    }
    total += sent;
  }
}

std::string TCPClient::receive() const {
  if (client_fd_ < 0) {
    throw std::runtime_error("socket not connected");
  }

  char buffer[1024];

  ssize_t bytes = recv(client_fd_, buffer, sizeof(buffer), 0);
  if (bytes < 0) {
    throw std::runtime_error("recv failed");
  }

  if (bytes == 0) {
    throw std::runtime_error("connection closed");
  }

  return std::string(buffer, bytes);
}

void TCPClient::close() {
  if (client_fd_ >= 0) {
    ::close(client_fd_);
    client_fd_ = -1;
  }
}

const std::string& TCPClient::getHost() const {
  return host_;
}

uint16_t TCPClient::getPort() const {
  return port_;
}