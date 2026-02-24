#include <iostream>
#include "pid.h"

#include "ExampleRegistry.h"

namespace {
void run() {
  PID pid = PID(0.1, 100, -100, 0.1, 0.01, 0.5);
  double setpoint = 100;
  double val = 20;
  for (int i = 0; i < 200; i++) {
    double inc = pid.calculate(setpoint, val);
    std::cout << "setpoint:" << setpoint << " - val:" << val << " - inc:" << inc
              << std::endl;
    val += inc;
  }
}
}  // namespace

class PIDSim : public IExample {
 public:
  std::string group() const override { return "controller"; }
  std::string name() const override { return "PIDSim"; }
  std::string description() const override { return "PID example"; }
  void execute() override { run(); }
};

REGISTER_EXAMPLE(PIDSim, "controller", "PIDSim");
