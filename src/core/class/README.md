## 1. Friend
- Friend declaration (classes and functions) allows certain classes or functions to access the private and protected members of another class.

### 1.1. Non Member Function
- It serves the same kind of role as the package access specifier in Java.
- `a << b` C++ tries in this order:
```cpp
1 a.operator<<(b)
2 operator<<(a, b) (non-member function)

X OP Y
operator OP (type_of_X, type_of_Y)
```
### 1.2. Member of Another Class:
- It give access to only once specific function.
### 1.3. Class
- Friend Class : I trust this class to see my private data
- It give access to all member functions of another class.

## 2. Class Relationship
### 2.1. Composition
- **Part-of, strong ownership**
- The member is part of the class
- The member can only belong to one class at a time
- The member has its existence managed by the class
- The member does not know about the existence of the class

- UML:
```cpp
+------------------------+
|          Car           |
+------------------------+
| - engine : Engine      |
+------------------------+
            ♦
            │
            │
+------------------------+
|         Engine         |
+------------------------+
| + Engine()             |
| + ~Engine()            |
+------------------------+

class Engine
{
public:
    Engine() { std::cout << "Engine created\n"; }
    ~Engine() { std::cout << "Engine destroyed\n"; }
};

class Car
{
private:
    Engine engine; // composition

public:
    Car() { std::cout << "Car created\n"; }
    ~Car() { std::cout << "Car destroyed\n"; }
};
```

## 2.2. Aggregations
- **Has-a, weak ownership**
- The member is part of the class
- The member can belong to more than one class at a time
- The member does not have its existence managed by the class
- The member does not know about the existence of the class

- UML:
```cpp
+-----------------------------+
|        Department           |
+-----------------------------+
| - teacher : Teacher*        |
+-----------------------------+
            ◇
            │
            │
+-----------------------------+
|           Teacher           |
+-----------------------------+
| - name : std::string        |
+-----------------------------+

class Teacher
{
public:
    std::string name;
    Teacher(const std::string& n) : name(n) {}
};

class Department
{
private:
    Teacher* teacher; // aggregation

public:
    Department(Teacher* t) : teacher(t) {}
};
```

## 2.3. Associations 
- **Uses-a, loose relationship**
- The associated member is otherwise unrelated to the class
- The associated member can belong to more than one class at a time
- The associated member does not have its existence managed by the class
- The associated member may or may not know about the existence of the class
- UML
```cpp
+---------------------+                 +---------------------+
|       Doctor        |-----------------|       Patient       |
+---------------------+                 +---------------------+
| + treat(p:Patient&) |                 | - name : string     |
+---------------------+                 +---------------------+

class Patient
{
public:
    std::string name;
};

class Doctor
{
public:
    void treat(Patient& p)
    {
        std::cout << "Treating " << p.name << "\n";
    }
};
```

## 2.4. Dependency
- **Denpends-on**
-  One class uses another class to perform a task. 
-  It is temporarily created, used, and then destroyed, or passed into a member function from an external source.
- UML
```cpp
+---------------------+
|         Car         |
+---------------------+
| + start()           |
+---------------------+
           - - - - - - - - - - - - - - - - - - >
                           +---------------------+
                           |       Logger        |
                           +---------------------+
                           | + log(msg:string)   |
                           +---------------------+
class Logger
{
public:
    void log(const std::string& msg)
    {
        std::cout << msg << std::endl;
    }
};

class Car
{
public:
    void start()
    {
        Logger logger;  // dependency
        logger.log("Car started");
    }
};

```
## 2.5. Container
-  The class one class provides a container to hold multiple objects of another type
- UML
```cpp
#include <vector>

+-----------------------------+
|          Library1           |
+-----------------------------+
| - books : vector<string>    |
+-----------------------------+
              ♦
              │
              │
+-----------------------------+
|          string             |
+-----------------------------+
class Library1
{
private:
    std::vector<std::string> books; // copy values
};

+-----------------------------+
|          Library2           |
+-----------------------------+
| - teachers : vector<T*>     |
+-----------------------------+
              ◇
              │
              │
+-----------------------------+
|           Teacher           |
+-----------------------------+
class Library2
{
private:
    std::vector<Teacher*> teachers; // store pointers
};

```

## 2.6. Inheritance
- **Is-a**
```cpp
+----------------------+
|        Animal        |
+----------------------+
| + eat()              |
+----------------------+
           △
           │
           │
+----------------------+
|         Dog          |
+----------------------+
| + bark()             |
+----------------------+
class Animal
{
public:
    void eat() { std::cout << "Eating\n"; }
};

class Dog : public Animal
{
public:
    void bark() { std::cout << "Woof\n"; }
};
```

## 2.7 Embedded a.k.a Nested/Inner Class
- Type-level containment
```cpp
+----------------------+
|        Car           |
+----------------------+
|                      |
+----------------------+
           (+)
           │
           │
+----------------------+
|         Engine       |
+----------------------+
| + start()            |
+----------------------+

class Car
{
public:
    class Engine
    {
    public:
        void start();
    };
};
```

## Type Cast
- C-style cast is unsafe, so we should use dynamic_cast or static_cast instead. For example:
```cpp
#include <iostream>
using namespace std;

class Car {
public:
	virtual ~Car() {}
};

class PassCar : public Car {
private:
	int passengers = 5;
public:
	void display() {
		cout << passengers << endl;
	}
};

class Truck : public Car {
private:
	int a =1;
public:
	void setAxle1s() {
		cout << "Truck axles set1\n";
	}
	void setAxles() {
		cout << "Truck axles set\n";
	}
};

int main() {
	Car* car = new Truck();  

	// -style cast 
	PassCar* p = (PassCar*)car;

	p->display();

	delete car;
}
```