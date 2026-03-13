#pragma once
#include <stdint.h>
#include <stdexcept>
#include <string>

class TCPServer {
 public:
  explicit TCPServer(uint16_t port = 80);
  virtual ~TCPServer();

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

  static void sendAll(int fd, const char* data, size_t len);

 protected:
  /**
   * @brief Handle communication with a single client
   * 
   * @param
   *  [in] client_fd client file descriptor 
   */
  void handleClient(int client_fd);

  /**
   * @brief Loop waiting for client connections
   */
  virtual void acceptLoop();

  bool isRunning() const;
  int getServerFD() const;
  void setServerFD(int fd);

 private:
  uint16_t port_;      // TCP ports are in 0 - 65535
  int server_fd_{-1};  // socket descriptor
  volatile bool running_{false};
};