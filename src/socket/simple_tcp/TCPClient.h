#pragma once
#include <cstdint>
#include <string>

class TCPClient {
 public:
  TCPClient(const std::string& host, uint16_t port);

  bool connect();
  void close();
  void send(const std::string& msg) const;
  std::string receive() const;

  const std::string& getHost() const;
  uint16_t getPort() const;

 private:
  std::string host_;
  uint16_t port_;
  int client_fd_;
};