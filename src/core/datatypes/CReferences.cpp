#include <iostream>
using namespace std;
// A type defined in terms of other types

void increment(int &x)
{
    x += 1;
}

void incrementConst(const int &x)
{
    // s cannot be modified here
    // x += 1;
}

static int global = 42;
int &returnRef()
{
    return global; // the object must outlive the reference.
}

void references()
{
    cout << "\n--- References Type Examples ---\n";
    int a = 10;
    cout << "a = " << a << "\n";

    // *1. Reference basics
    // int &ref_error; // reference must be initialized
    int &ref_a = a;

    ref_a = 20;                             // modifies 'a', since ref is just an alias
    cout << "ref_a =20, a = " << a << "\n"; // prints 20

    // Cannot reseat: once 'ref' is bound to 'a', it cannot be bound to another variable
    // int b = 30;
    // ref = &b;   invalid, would assign value instead of rebinding

    // *2. Pass by reference
    increment(a);                                     // avoids making a copy
    std::cout << "a after increment = " << a << "\n"; // prints 21

    // *3. Pass by const reference
    incrementConst(a);

    // *4. Return by reference
    int const &b = returnRef();
    std::cout << "By reference: " << b << '\n';
}

// A struct that runs code when its object is created
struct CReferences
{
    CReferences()
    {
        cout << "\n"
             << "\n"
             << "Compound type: References\n";

        references();
    }
};

// All global and static objects are constructed before main() begins.
static CReferences autoRunInstance;
