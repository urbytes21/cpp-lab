// global constants as external variables:

// Advantages:
//     Works prior to C++16.
//     Only one copy of each variable is required.
//     Only requires recompilation of one file if the value of a constant changes.
// Downsides:
//     Forward declarations and variable definitions are in separate files, and must be kept in sync.
//     Variables not usable in constant expressions outside of the file in which they are defined.

#ifndef ECONSTANTS_H
#define ECONSTANTS_H

namespace ExternalConstants {
// Since the actual variables are inside a namespace, the forward declarations need to be inside a namespace as well
// We can't forward declare variables as constexpr, but we can forward declare them as (runtime) const
extern const double pi;
extern const double avogadro;
extern const double myGravity;
}  // namespace ExternalConstants

#endif