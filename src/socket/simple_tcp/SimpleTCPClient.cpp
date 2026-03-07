#include <iostream>
#include "ExampleRegistry.h"
#include "TCPClient.h"

namespace {

void run() {
  try {
    TCPClient client("127.0.0.1", 8080);

    if (!client.connect()) {
      std::cout << "connect failed\n";
      return;
    }

    client.send("Hello server\n");

    std::string response = client.receive();

    std::cout << "server: " << response << std::endl;

    client.close();
  } catch (const std::exception& e) {
    std::cout << "error: " << e.what() << std::endl;
  }
}

}  // namespace

class SimpleTCPClient : public IExample {
 public:
  std::string group() const override { return "socket/tcp"; }

  std::string name() const override { return "SimpleTCPClient"; }

  std::string description() const override { return "Simple TCP Client"; }

  void execute() override { run(); }
};

REGISTER_EXAMPLE(SimpleTCPClient, "socket/tcp", "SimpleTCPClient");