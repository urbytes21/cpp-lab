// cppcheck-suppress-file [functionStatic]

// Strategy is a behavioral design pattern that lets you define a family of
// algorithms, put each of them into a separate class, and make their objects
// interchangeable. Appicability:
// (*)    when you want to use different variants of an algorithm within an
// object and be able to switch from one algorithm to another during runtime.
// (**)   when you have a lot of similar classes that only differ in the way
// they execute some behavior.
// (***)  when your class has a massive conditional statement that switches
// between different variants of the same algorithm. UML:
// docs/uml/patterns_behavioral_strategy.drawio.svg

#include <iostream>
#include <string>
#include <utility>
#include "Logger.h"

namespace {
namespace strategy {
class IExportStrategy {
 public:
  virtual ~IExportStrategy() = default;
  virtual std::string executeExportData(const std::string& content) const = 0;
};

class ExportContext {
 private:
  std::string content_;
  IExportStrategy* strategy_;

 public:
  ~ExportContext() { delete strategy_; }

  explicit ExportContext(std::string content,
                         IExportStrategy* const strategy = nullptr)
      : content_(std::move(content)), strategy_(strategy) {}

  void setExportStrategy(IExportStrategy* const strategy) {
    delete strategy_;
    this->strategy_ = strategy;
  }

  // The old approach using if-else for each format is commented out:
  // if(format == "HTML") {
  //     // export HTML
  // } else if(format == "JSON") {
  //     // export JSON
  // } else if(format == "Markdown") {
  //     // export Markdown
  // }
  //
  // 1. This approach mixes data (Context) and behavior (export logic), which is
  // hard to maintain.
  // 2. Adding new formats requires modifying this function, violating the
  // Open/Closed Principle.
  // 3. Strategy Pattern allows each format to be a separate class, and Context
  // only holds data.
  // ======================================================================================
  std::string exportDocument() const {
    if (strategy_ != nullptr) {
      return this->strategy_->executeExportData(this->content_);
    }

    LOG("Strategy isn't set");
    return "";
  }
};

class JsonExportStrategy : public IExportStrategy {
 public:
  std::string executeExportData(const std::string& content) const override {
    return R"({"content": ")" + content + "\" }";
  }
};

class HtmlExportStrategy : public IExportStrategy {
 public:
  std::string executeExportData(const std::string& content) const override {
    return "<p>" + content + "</p>";
  }
};

void run() {
  auto client_code = [](const ExportContext& ctx) {
    LOG(ctx.exportDocument());
  };

  auto* ctx = new ExportContext("This is the report content.");
  client_code(*ctx);

  LOG("===HTML Export===");
  ctx->setExportStrategy(new HtmlExportStrategy());
  client_code(*ctx);

  LOG("===JSON Export===");
  ctx->setExportStrategy(new JsonExportStrategy());
  client_code(*ctx);

  delete ctx;
}
}  // namespace strategy
}  // namespace

#include "ExampleRegistry.h"

class StrategyExample : public IExample {
 public:
  std::string group() const override { return "dp/behavioral"; }
  std::string name() const override { return "Strategy"; }
  std::string description() const override {
    return "Strategy Pattern Example";
  }
  void execute() override { strategy::run(); }
};

REGISTER_EXAMPLE(StrategyExample);