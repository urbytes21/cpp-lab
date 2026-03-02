# 1. Core C Basics for Embedded Systems

**Topics Covered:**

- 1.1 Variables & Data Types
- 1.2 Operators & Control Flow
- 1.3 Functions
- 1.4 Arrays & Strings
- 1.5 Basic Input/Output
- 1.6 Practice Problems

## 1.1 Variables & Data Types

**What is a Variable?**

A variable is a named location in memory that stores data. Think of it as a labeled box
where you can put values and retrieve them later.

**Note:** In embedded systems, understanding how much memory each data type uses is
CRITICAL because microcontrollers have limited RAM.

**Common Data Types in C**

| Data Type       | Size (Typical) | Range                              | Use Case                          |
|-----------------|---------------|------------------------------------|-----------------------------------|
| char            | 1 byte        | -128 to 127                        | Single characters, small integers |
| unsigned char   | 1 byte        | 0 to 255                           | Sensor readings, register values  |
| int (16-bit)    | 2 bytes       | -32,768 to 32,767                  | Counters, calculations            |
| unsigned int    | 2 bytes       | 0 to 65,535 (16-bit)               | Always positive values            |
| long            | 4 bytes       | -2,147,483,648 to 2,147,483,647    | Large numbers, timestamps         |
| float           | 4 bytes       | ±3.4e±38 (~6–7 digits precision)   | Decimal numbers (avoid in embedded!) |

**Example Code:**
```c
// Declaring variables
int sensorValue = 0; // 16 or 32-bit integer
unsigned char ledState = 1; // 8-bit (0-255)
float temperature = 25.5; // Floating point
char deviceStatus = 'A'; // Single character

// Why size matters in embedded:
unsigned char counter = 0; // Uses only 1 byte of RAM
int bigCounter = 0; // Uses 2 or 4 bytes of RAM
```

<br>

## 1.2. Operators & Control Flow

**Arithmetic Operators**

Used for mathematical calculations: + (add), - (subtract), * (multiply), / (divide), %
(modulus/remainder)
```c
int a = 10, b = 3;
int sum = a + b; // 13
int diff = a - b; // 7
int product = a * b; // 30
int quotient = a / b; // 3 (integer division!)
int remainder = a % b; // 1
```

**Comparison Operators**

Compare values and return true (1) or false (0):
```c
==      (equal),
!=      (not equal),
>       (greater),
<       (less),
>=, <=
```

**Logical Operators**

Combine multiple conditions: && (AND), || (OR),! (NOT)

```c
int temperature = 75;
int humidity = 60;

// AND operator - both conditions must be true
if (temperature > 70 && humidity > 50) {
    printf("Hot and humid!\n");
}
```

**Control Flow: if/else**

Makes decisions in your program based on conditions.

```c
int temperature = 75;
if (temperature > 80) {
    // Turn on cooling fan
    fanState = 1;
} else if (temperature < 60) {
    // Turn on heater
    heaterState = 1;
} else {
    // Temperature is fine
    fanState = 0;
    heaterState = 0;
}
```

**Loops: for and while**

Repeat code multiple times. Essential for embedded systems!
```c
// for loop - when you know how many times to repeat
for (int i = 0; i < 10; i++) {
    printf("%d ", i); // Prints: 0 1 2 3 4 5 6 7 8 9
}

// while loop - repeat while condition is true
int count = 0;
while (count < 5) {
    printf("Count: %d\n", count);
    count++;
}
```

> **Embedded Tip:** In embedded systems, you'll often use infinite loops: while(1) { } to
keep the microcontroller running continuously!

## 1.3. Functions

**What are Functions?**

Functions are reusable blocks of code that perform a specific task. They help you
organize code and avoid repetition.

**Function Structure**

```c
return_type function_name(parameters) {
    // code to execute
    return value; // optional
}
```

**Example: Simple Functions**

```c
// Function that returns sum of two numbers
int add(int a, int b) {
    return a + b;
}

// Function that doesn't return anything (void)
void blinkLED(int times) {
    for (int i = 0; i < times; i++) {
        // Turn LED on
        // Delay
        // Turn LED off
        // Delay
    }
}

// Using the functions
int main() {
    int result = add(5, 3); // result = 8
    blinkLED(5); // Blink LED 5 times
    return 0;
}
```

> **Why Functions Matter in Embedded:** Real embedded projects have functions like
readSensor(), updateDisplay(), checkButton() - breaking complex tasks into simple,
manageable pieces.

## 1.4. Arrays & Strings

**What is an Array?**

An array is a collection of elements of the same type stored in consecutive memory
locations. Think of it as a row of boxes, each holding a value.

**Declaring and Using Arrays**

```c
// Declare an array of 5 integers
int sensorReadings[5];

// Initialize array with values
int ledPins[4] = {2, 3, 4, 5};

// Access array elements (index starts at 0!)
sensorReadings[0] = 100; // First element
sensorReadings[1] = 105; // Second element
sensorReadings[4] = 120; // Fifth element

// Loop through array
for (int i = 0; i < 5; i++) {
    printf("%d ", sensorReadings[i]);
}
```

**Strings in C**

In C, strings are arrays of characters ending with a null terminator ('\0'). This is different
from other languages!

```c
// Declaring strings
char deviceName[] = "Arduino"; // Automatically adds \
char message[20] = "Hello World"; // Reserve 20 chars

// Character array vs string
char name[6] = {'C', 'l', 'a', 'u', 'd', '\0'}; // Must add \

// Common string operations (need string.h)
#include <string.h>
char str1[50] = "Hello";
char str2[50] = "World";
strcat(str1, str2); // Concatenate: str1 becomes "HelloWorld"
int len = strlen(str1); // Get length: 10
strcpy(str1, "New"); // Copy: str1 becomes "New"
```

> **Important:** In embedded systems, you'll often use character arrays to store sensor
data, messages for displays, or communication buffers.

## 1.5. Basic Input/Output

**Console Output: printf()**

`printf()` is used to print formatted output to the console. Essential for debugging
embedded systems!

```c
#include <stdio.h>

int temperature = 25;
float voltage = 3.3;
char status = 'A';

// Format specifiers:
printf("Temperature: %d°C\n", temperature); // %d for integers
printf("Voltage: %.2f V\n", voltage); // %f for floats (.2 = 2 decimals)
printf("Status: %c\n", status); // %c for characters
printf("Hex value: 0x%X\n", 255); // %X for hexadecimal

// Multiple values:
printf("Temp: %d, Voltage: %.1f\n", temperature, voltage);
```

**Console Input: scanf()**

`scanf()` reads formatted input from the console.

```c
int age;
char name[50];

printf("Enter your age: ");
scanf("%d", &age); // Note the & symbol!

printf("Enter your name: ");
scanf("%s", name); // No & for arrays

printf("Hello %s, you are %d years old!\n", name, age);
```

**Common Format Specifiers**

| Specifier      | Data Type       | Example                    |
|---------------|----------------|------------------------------|
| %d or %i      | int            | printf("%d", 42);            |
| %ld           | long           | printf("%lu", 255);          |
| %u            | unsigned int   | printf("%u", 255);           |
| %lu           | uint32_t       | printf("%lu", 255);           |
| %f            | float/double   | printf("%.2f", 3.14);        |
| %c            | char           | printf("%c", 'A');           |
| %s            | string         | printf("%s", "Hello");       |
| %x or %X      | hexadecimal    | printf("0x%X", 255);         |
| %p            | pointer        | printf("%p", &var);          |


## 1.6. Practice Problems

**Problem 1: Temperature Converter**

Write a program that converts temperature from Celsius to Fahrenheit using the
formula: F = (C × 9/5) + 32

// Your code here:
// 1. Declare a float variable for celsius
// 2. Use scanf to get input
// 3. Calculate fahrenheit
// 4. Print the result


**Problem 2: Even or Odd Checker**

Write a program that takes a number and prints whether it's even or odd. (Hint: Use the
modulus operator %)

**Problem 3: Sum Calculator with Loop**

Write a program that takes a number N and calculates the sum of all numbers from 1 to
N using a for loop.
Example: If N = 5, sum = 1+2+3+4+5 = 15

**Problem 4: Array Average**

Create an array of 5 sensor readings. Write a function that calculates and returns the
average value.

**Problem 5: LED Blink Function**

Write a function void blinkPattern(int count, int delayMs) that simulates blinking an LED.
Use printf to show LED ON/OFF states.

**Problem 5: Write a program that**
- Takes 5 temperature readings into an array
- Calculates the average temperature
- If average > 75°F, print "COOLING NEEDED"
- If average < 65°F, print "HEATING NEEDED"
- Otherwise, print "TEMPERATURE OK"
