#pragma once
#include <stdint.h>
#include <string>

class TCPClient {
 public:
  TCPClient(const std::string& host, uint16_t port);

  bool connect();
  void close();
  void send(const std::string& msg);
  std::string receive();

 private:
  std::string host_;
  uint16_t port_;
  int client_fd_;
};