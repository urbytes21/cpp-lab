## 1. Smart Pointers
- The STL includes smart pointers, which are defined in the <memory> to help ensure that programs are free of memory and resource leaks.
- Raw pointers are only used in small code blocks where performance is critical and we can control the ownership stuff.
- e.g.
```cpp
void UseRawPointer()
{
    // Using a raw pointer -- not recommended.
    Song* pSong = new Song(L"Nothing on You", L"Bruno Mars"); 

    // Use pSong...

    // Delete
    delete pSong;   
}

void UseSmartPointer()
{
    // Declare a smart pointer on stack and pass it the raw pointer.
    unique_ptr<Song> song2(new Song(L"Nothing on You", L"Bruno Mars"));

    // Use song2...
    wstring s = song2->duration_;
    //...

} // song2 is deleted automatically here.
```

- After being initialized, the smart pointer owns the raw pointer.
- Use the overloaded `->` and `*` operators to access the object.
- Use `get()` to access the raw pointer directly.
- There are some kinds of the smart pointer:
    - `unique_ptr`: this is the default choice for POCO, **one owner**
    - `shared_ptr`: **multiple owners**, the raw pointer deleted when all owners have gone out of scope or have otherwise given up ownership.
    - `weak_ptr`: provides access to an object that is owned by one or more `shared_ptr`, but holds a **non-owning** reference to this object.

## 2. unique_ptr
- It can only be moved and cannot be passed by value, copied.
- e.g.
```cpp
unique_ptr<Song> SongFactory(const std::wstring& artist, const std::wstring& title)
{
    // Implicit move operation into the variable that stores the result.
    return make_unique<Song>(artist, title);
}

void MakeSongs()
{
    // Create a new unique_ptr with a new object.
    auto song = make_unique<Song>(L"Mr. Children", L"Namonaki Uta");

    // Use the unique_ptr.
    vector<wstring> titles = { song->title };

    // Move raw pointer from one unique_ptr to another.
    unique_ptr<Song> song2 = std::move(song);

    // Obtain unique_ptr from function that returns by value.
    auto song3 = SongFactory(L"Michael Jackson", L"Beat It");
}

// Create a unique_ptr to an array of 5 integers.
auto p = make_unique<int[]>(5);

// Initialize the array.
for (int i = 0; i < 5; ++i)
{
    p[i] = i;
    wcout << p[i] << endl;
}
```

## 3. shared_ptr
- It is designed for scenarios in which more than one owner needs to manage the lifetime of an object.
- It can be copied, passed by value in function arguments, and assigned to other `shared_ptr` instances.
- All the instances point to the same object, and share access to one "control block" that increments and decrements the reference count whenever a new shared_ptr is added, goes out of scope, or is reset. When the reference count reaches zero, the control block deletes the memory resource and itself.
- e.g.
```cpp
// Use make_shared function when possible.
auto sp1 = make_shared<Song>(L"The Beatles", L"Im Happy Just to Dance With You");

// Ok, but slightly less efficient. 
// Note: Using new expression as constructor argument
// creates no named variable for other code to access.
shared_ptr<Song> sp2(new Song(L"Lady Gaga", L"Just Dance"));

// When initialization must be separate from declaration, e.g. class members, 
// initialize with nullptr to make your programming intent explicit.
shared_ptr<Song> sp5(nullptr);
//Equivalent to: shared_ptr<Song> sp5;
//...
sp5 = make_shared<Song>(L"Elton John", L"I'm Still Standing");

//Initialize with copy constructor. Increments ref count.
auto sp3(sp2);

//Initialize via assignment. Increments ref count.
auto sp4 = sp2;

//Initialize with nullptr. sp7 is empty.
shared_ptr<Song> sp7(nullptr);

// Initialize with another shared_ptr. sp1 and sp2
// swap pointers as well as ref counts.
sp1.swap(sp2);
```

## 4. weak_ptr
- It's used to to access the underlying object of a shared_ptr without causing the reference count to be incremented.
- If the memory has already been deleted, the weak_ptr's bool operator returns false.
- e.g. 
> std::weak_ptr is a very good way to solve the dangling pointer problem. By just using raw pointers it is impossible to know if the referenced data has been deallocated or not. Instead, by letting a std::shared_ptr manage the data, and supplying std::weak_ptr to users of the data, the users can check validity of the data by calling expired() or lock().
You could not do this with std::shared_ptr alone, because all std::shared_ptr instances share the ownership of the data which is not removed before all instances of std::shared_ptr are removed. Here is an example of how to check for dangling pointer using lock():
```cpp
// Source - https://stackoverflow.com/a/21877073
// Posted by sunefred, modified by community. See post 'Timeline' for change history
// Retrieved 2026-02-06, License - CC BY-SA 4.0

#include <iostream>
#include <memory>

int main()
{
    // OLD, problem with dangling pointer
    // PROBLEM: ref will point to undefined data!

    int* ptr = new int(10);
    int* ref = ptr;
    delete ptr;

    // NEW
    // SOLUTION: check expired() or lock() to determine if pointer is valid

    // empty definition
    std::shared_ptr<int> sptr;

    // takes ownership of pointer
    sptr.reset(new int);
    *sptr = 10;

    // get pointer to data without taking ownership
    std::weak_ptr<int> weak1 = sptr;

    // deletes managed object, acquires new pointer
    sptr.reset(new int);
    *sptr = 5;

    // get pointer to new data without taking ownership
    std::weak_ptr<int> weak2 = sptr;

    // weak1 is expired!
    if(auto tmp = weak1.lock())
        std::cout << "weak1 value is " << *tmp << '\n';
    else
        std::cout << "weak1 is expired\n";
    
    // weak2 points to new data (5)
    if(auto tmp = weak2.lock())
        std::cout << "weak2 value is " << *tmp << '\n';
    else
        std::cout << "weak2 is expired\n";
}
```