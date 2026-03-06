#pragma once
#include <stdint.h>
#include <stdexcept>
#include <string>

class TCPServer {
 public:
  explicit TCPServer(uint16_t port = 80);
  ~TCPServer();

  void start() noexcept(false);
  void stop();

  void setPort(uint16_t port);
  uint16_t getPort() const;

 private:
  /**
   * @brief  Create the server socket and configure basic options
   */
  void createSocket();

  /**
   * @brief Bind the socket to a port and network interface
   */
  void bindSocket();

  /**
   * @brief Put the socket into listening mode
   */
  void listenSocket();

  /**
   * @brief Loop waiting for client connections
   */
  void acceptLoop();

  /**
   * @brief Handle communication with a single client
   * 
   * @param
   *  [in] client_fd client file descriptor 
   */
  void handleClient(int client_fd);

 private:
  uint16_t port_;      // TCP ports are in 0 - 65535
  int server_fd_{-1};  // socket descriptor
  bool running_{false};
};