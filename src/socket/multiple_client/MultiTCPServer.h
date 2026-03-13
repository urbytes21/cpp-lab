#pragma once
#include <thread>
#include <vector>
#include "ExampleRegistry.h"
#include "../simple_tcp/TCPServer.h"

class MultiTCPServer : public TCPServer, public IExample {
 public:
  std::string group() const override { return "socket/tcp"; }

  std::string name() const override { return "SimpleTCPServer"; }

  std::string description() const override {
    return "Simple TCP server listening on port 8080.\nRun `telnet localhost "
           "8080` to connect.";
  }

  void execute() override { run(); }

 protected:
  void acceptLoop() override;
  void run();
  std::vector<std::thread> client_threads_;
};
