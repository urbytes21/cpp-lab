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
    std::cout << "connected to " << "host: " << client.getHost()
              << " port:" << client.getPort() << "\n";
    std::string response = client.receive();
    std::cout << response << std::endl;
    std::string msg;
    while (true) {
      if (!std::getline(std::cin, msg)) {
        std::cout << "get line failed" << std::endl;
        break;
      };

      // TODO(phong-nguyen): why we need \n here
      client.send(msg + "\n");
      response = client.receive();
      std::cout << response;
    }

    client.close();
  } catch (const std::exception& e) {
    // Connection closed by foreign host
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

REGISTER_EXAMPLE(SimpleTCPClient);