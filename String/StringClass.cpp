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
Then, I'll implement the member functions accordingly.
*/
#include "StringClass.hpp"

int main(){
    //Example usage of the String class
    // String str1; // Default constructor
    // String str2("Hello, World!"); // C-style string constructor
    return 0;
}
