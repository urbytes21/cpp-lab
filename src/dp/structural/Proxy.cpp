// Proxy is a structural design pattern that lets you provide a substitute or
// placeholder for another object. A proxy controls access to the original
// object, allowing you to perform something either before or after the request
// gets through to the original object. A proxy receives client requests, does
// some work (access control, caching, etc.) and then passes the request to a
// service object. Appicability:
// (*)   Lazy initialization (virtual proxy) /  Logging requests (logging proxy)
// / Caching request results (caching proxy)
// (**)  Access control (protection proxy).
// (***) Local execution of a remote service (remote proxy). This is when the
// service object is located on a remote server.

// Composition - lazy
// Aggregation - x
// UML: docs/uml/patterns_structural_proxy.drawio.svg

#include <iostream>
#include <utility>

#include "ExampleRegistry.h"

namespace {
namespace problem {
const std::string kAdmin = "admin";

class IServer {
 public:
  virtual ~IServer() = default;
  virtual void request1() = 0;
  virtual void request2() = 0;
  virtual void request3() = 0;
};

class Server : public IServer {
 private:
  std::string id_;

 public:
  explicit Server(std::string id) : id_{std::move(id)} {
    // [P1] Heavy or complex construction, so ideally should be lazy-loaded
    std::cout << "[Server] Constructor: " << id_ << "\n";
  }

  // [P2] Need access control
  // [P3] Need to log requests without modifying the Server itself
  void request1() override {
    if (id_ != kAdmin) {
      std::cout << "[Server] Invalid ID: " << id_ << "\n";
      return;
    }
    std::cout << "[Server] Handling request-1 for: " << id_ << "\n";
  }

  void request2() override {
    if (id_ != kAdmin) {
      std::cout << "[Server] Invalid ID: " << id_ << "\n";
      return;
    }
    std::cout << "[Server] Handling request-2 for: " << id_ << "\n";
  }

  void request3() override {
    if (id_ != kAdmin) {
      std::cout << "[Server] Invalid ID: " << id_ << "\n";
      return;
    }
    std::cout << "[Server] Handling request-3 for: " << id_ << "\n";
  }
};

namespace client {
void clientCode(IServer* s) {
  if (s != nullptr) {
    s->request1();
    s->request2();
    s->request3();
  }
}
}  // namespace client

void run() {
  std::cout << "\n\n";

  {
    std::string connection_id = "admin";
    // [P4] The Server is constructed immediately even if we do not call any
    // requests
    IServer* server = new Server(connection_id);
    std::cout << "User request\n";
    client::clientCode(server);
    delete server;
  }

  {
    // [P4] Server is constructed even for invalid ID, wasting resources
    std::string invalid_id = "xxx";
    auto* server = new Server(invalid_id);
    client::clientCode(server);
    delete server;
  }
}
}  // namespace problem

namespace proxy_pattern {
const std::string kAdmin = "admin";

class IServer {
 public:
  virtual ~IServer() = default;
  virtual void request1() = 0;
  virtual void request2() = 0;
  virtual void request3() = 0;
};

class Server : public IServer {
 private:
  std::string id_;

 public:
  explicit Server(std::string id) : id_{std::move(id)} {
    std::cout << "[Server] Constructor: " << id_ << "\n";
  }

  void request1() override {
    std::cout << "[Server] Handling request-1 for: " << id_ << "\n";
  }

  void request2() override {
    std::cout << "[Server] Handling request-2 for: " << id_ << "\n";
  }

  void request3() override {
    std::cout << "[Server] Handling request-3 for: " << id_ << "\n";
  }
};

class ServerProxy : public IServer {
 private:
  std::string id_;
  Server* server_{};

  bool checkAccess() {
    std::cout << "[Proxy] Checking access before forwarding request.\n";
    if (id_ != kAdmin) {
      return false;
    }

    // Lazy initialization: construct Server only on first access
    if (server_ == nullptr) {
      server_ = new Server(id_);
    }
    return true;
  }

  void logAccess() const {
    std::cout << "[Proxy] Logging request time: " << id_ << " .\n";
  }

 public:
  explicit ServerProxy(std::string id) : id_{std::move(id)} {
    std::cout << "[Proxy] Constructor: " << id_ << "\n";
  }

  ~ServerProxy() override {
    std::cout << "[Proxy] Destructor: " << id_ << "\n";

    delete server_;
  }

  void request1() override {
    if (checkAccess()) {
      server_->request1();
      logAccess();
    }
  }

  void request2() override {
    if (checkAccess()) {
      server_->request2();
      logAccess();
    }
  }

  void request3() override {
    if (checkAccess()) {
      server_->request3();
      logAccess();
    }
  }
};

namespace client {
void clientCode(IServer* s) {
  if (s != nullptr) {
    s->request1();
    s->request2();
    s->request3();
  }
}
}  // namespace client

void run() {
  std::cout << "\n\n";

  {
    std::string connection_id = "admin";
    // Server is not constructed until first request is made
    IServer* server = new ServerProxy(connection_id);
    std::cout << "User request\n";
    client::clientCode(server);
    delete server;
  }

  // Server is not constructed if id is invalid
  std::string invalid_id = "xxx";
  auto* server = new Server(invalid_id);
  client::clientCode(server);
  delete server;
}
}  // namespace proxy_pattern

class ProxyExample : public IExample {
 public:
  std::string group() const override { return "dp/structural"; }
  std::string name() const override { return "Proxy"; }
  std::string description() const override { return "Proxy Pattern Example"; }
  void execute() override {
    problem::run();
    proxy_pattern::run();
  }
};

REGISTER_EXAMPLE(ProxyExample);
}  // namespace
