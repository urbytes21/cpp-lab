#pragma once
#include "Turtle.h"

class Painter {
public:
  explicit Painter(Turtle& turtle) : turtle_(turtle) {}

  void DrawSquare(int size) {
    turtle_.PenDown();
    for (int i = 0; i < 4; ++i) {
      turtle_.Forward(size);
      turtle_.Turn(90);
    }
    turtle_.PenUp();
  }

private:
  Turtle& turtle_;
};
