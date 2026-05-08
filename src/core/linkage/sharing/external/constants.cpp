#include "constants.h"

namespace external_constants {
// We use extern to ensure these have external linkage
extern constexpr double kPi{3.14159};
extern constexpr double kAvogadro{6.0221413e23};
extern constexpr double kMyGravity{
    9.2};  // m/s^2 -- gravity is light on this planet
}  // namespace external_constants
