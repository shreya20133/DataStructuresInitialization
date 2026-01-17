/*
IMPLEMENTATION NOTE: This file is an implementation of the String class.
It provides definitions for the member functions declared in StringClass.h.

Clarification Questions:
1. Functional Requirements:
    - Mutable string ?
    - Null-terminated strings or length-prefixed ?
    - Support for Unicode or just ASCII ?
    - Thread safety requirements ?
    - Ownership semantics (copy-on-write, reference counting, etc.) ?
    - Copyable/movable objects ?
2. Based on the above Functional Requirements, what specific features should be implemented?
    - Construction (default, from const char*)
    - Destruction
    - Assignment operator overloading
    - Copy Constructor
    - Move Constructor
    - Concatenation operator overloading
    - Substring extraction
    - Comparison operators
    - Length retrieval
    - Character access (operator[])
    - Find/replace functions
    - Input/Output stream operators
    - Additional utility functions (e.g., toUpperCase, toLowerCase)
3. Performance Requirements:
    - Expected time complexity for common operations (e.g., O(1) for length retrieval, O(n) for concatenation)
    - Memory usage constraints
    - Thread safety considerations
    - Exception safety guarantees

I'll implement a basic version of the String class based on common requirements which will
1. own memory to avoid dangling pointers,
2. Retrieve length in O(1) time,
3. Support basic operations like construction, destruction, assignment, concatenation, and comparison.

Now, in my class first, we'll define the private members to hold the string data and its length.
Then, I'll implement the member functions accordingly. This is added in StringClass.hpp file.
*/
#include "StringClass.hpp"
// Default Constructor
/*
Members are default-initialized first

    1. data → uninitialized (garbage pointer)
    2. length → uninitialized (garbage value)

Then constructor body runs:

    1.data is assigned a valid heap pointer
    2.length is assigned 0
*/
/*String::String(){
    // Default Constructor
    data = new char[1]; // Allocate memory for empty string
    data[0] = '\0'; // Null-terminate
    length = 0; // Length is 0
}*/

/*OR using member initializer list */
/* Member initializer list */
/*
   Preferred way:
   Member initializer list is a more efficient way to initialize member variables.
   It initializes members directly rather than assigning values in the constructor body.
   Members are constructed directly. data gets heap memory immediately.length is initialized to 0.
   Constructor body runs afterward. No invalid temporary states.
*/
String::String() : data(new char[1]),length(0) {
    data[0] = '\0'; // Null-terminate
}

String::String(const char *str) : data(nullptr), length(0) {    //Here, if new throws exception, object is still in valid state with data as nullptr and length as 0.
    if(!str){
        // Handle null pointer input and return empty string i.e. null terminated string with length 0
        data = new char[1];
        data[0] = '\0';
        return;
    }

    /* I initialize data to nullptr and length to zero to keep the object in a safe state in case of early returns or exceptions, 
       then I allocate and copy inside the constructor body.” */
    
       length = std::strlen(str);
       data = new char[length + 1]; // +1 for null-terminator
    //    std::strcpy(data,str); // Copy the string data from str to data- This is correct but strcpy rescans str until /0 but we know the length already
       std::memcpy(data, str, length + 1); // Copy including null-terminator

}

int main(){
    //Example usage of the String class
    // String str1; // Default constructor
    // String str2("Hello, World!"); // C-style string constructor
    return 0;
}
