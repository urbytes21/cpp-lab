// global constants as inline variables:

// If you need global constants and your compiler is C++17 capable, prefer defining inline constexpr global variables in a header file.
// Advantages:
//     Can be used in constant expressions in any translation unit that includes them.
//     Only one copy of each variable is required.
// Downsides:
//     Only works in C++17 onward.
//     Changing anything in the header file requires recompiling files including the header.

#ifndef ICONSTANTS_H
#define ICONSTANTS_H

// define your own namespace to hold constants
namespace inline_constants {
inline constexpr double kPi{3.14159};  // note: now inline constexpr
inline constexpr double kAvogadro{6.0221413e23};
inline constexpr double kMyGravity{
    9.2};  // m/s^2 -- gravity is light on this planet
           // ... other related constants
}  // namespace inline_constants
#endif