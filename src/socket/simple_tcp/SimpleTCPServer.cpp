#include <iostream>

#include "ExampleRegistry.h"
#include "TCPServer.h"

namespace {

void run() {
  TCPServer server(8080);

  try {
    server.start();
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    server.stop();
  }
}

}  // namespace

class SimpleTCPServer : public IExample {
 public:
  std::string group() const override { return "socket/tcp"; }

  std::string name() const override { return "SimpleTCPServer"; }

  std::string description() const override {
    return "Simple TCP server listening on port 8080.\nRun `telnet localhost "
           "8080` to connect.";
  }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(SimpleTCPServer);