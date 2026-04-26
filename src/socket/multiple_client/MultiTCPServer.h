#pragma once
#include <thread>
#include <vector>
#include "../simple_tcp/TCPServer.h"
#include "IExample.h"

class MultiTCPServer : public TCPServer, public IExample {
 public:
  std::string group() const override { return "socket/tcp"; }

  std::string name() const override { return "MultiTCPServer"; }

  std::string description() const override {
    return "Multi TCP server listening on port 8080.\nRun `telnet localhost "
           "8080` to connect.";
  }

  void execute() override { run(); }

 protected:
  void acceptLoop() override;
  void run();
  std::vector<std::thread> client_threads_;
};
