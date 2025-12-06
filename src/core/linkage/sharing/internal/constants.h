
// global constants as internal variables:
// Advantages:
//     Works prior to C++16.
//     Can be used in constant expressions in any translation unit that includes them.
// Downsides:
//     Changing anything in the header file requires recompiling files including the header.
//     Each translation unit including the header gets its own copy of the variable.

#ifndef INCONSTANTS_H
#define INCONSTANTS_H

// Define your own namespace to hold constants
namespace InternalConstants {
// Global constants have internal linkage by default
constexpr double pi{3.14159};
constexpr double avogadro{6.0221413e23};
constexpr double myGravity{9.2};  // m/s^2 -- gravity is light on this planet
                                  // ... other related constants
}  // namespace InternalConstants
#endif