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
   const char members and reference members must be initialized this way.
   If another class which only has parameterized constructors is a member, it must be initialized this way.
*/
// Default Constructor
String::String() : data(new char[1]),length(0) {
    data[0] = '\0'; // Null-terminate
}

// Constructor from C-style string
String::String(const char *str) : data(nullptr), length(0) {    //Here, if new throws exception, object is still in valid state with data as nullptr and length as 0.
    if(!str){
        // Handle null pointer input and return empty string i.e. null terminated string with length 0
        data = new char[1];
        data[0] = '\0';
        return;
    }
    
    length = std::strlen(str);
    data = new char[length + 1]; // +1 for null-terminator
    //std::strcpy(data,str); // Copy the string data from str to data- This is correct but strcpy rescans str until /0 but we know the length already
    std::memcpy(data, str, length + 1); // Copy including null-terminator

}

/*
A copy constructor creates a NEW object by copying an EXISTING object.
When is a copy constructor called? (VERY IMPORTANT)
A copy constructor is called when a new object is being created from an existing one.
Case 1: Direct initialization
String a;
String b = a;   // copy constructor
Case 2: Pass by value
void func(String x);  // x is a copy of the argument
func(a);   // copy constructor
Case 3: Return by value
String func(){
    String a;
    return a;  // copy constructor (may be optimized away by RVO)
}
Case 4: Explicitly using the copy constructor
String b(a);  // copy constructor

b = a;     // ❌ NOT copy constructor - this is copy assignment operator

Without a user-defined copy constructor, the compiler provides a default one that performs a shallow copy.
This means that the new object's data pointer would point to the same memory as the original object's data pointer.
This leads to issues like double deletion when both objects are destroyed.

String a(b); without copy constructor
a.data --> HEAP MEMORY BLOCK
b.data ------^
When a and b go out of scope, both will try to delete the same memory, causing undefined behavior.
Since, objects are destroyed in reverse order of creation, first b deletes the memory, then a tries to delete the already freed memory.
*/
// Copy Constructor
String::String(const String &stringToCopy)  : data(nullptr), length(stringToCopy.length) {
    data = new char[length + 1]; // Allocate memory for the copied string
    std::memcpy(data, stringToCopy.data, length + 1); // Copy including null-terminator
}

/* WRONG Copy Constructor implementation:
String::String(const String& other)
    : data(other.data), length(other.length) {}
Why this is BAD:

Shallow copy

Double delete

Aliasing bugs*/

size_t String::getLength() const {
    return length;
}

const char* String::c_str() const {
    return data;
}

void String::printString(const String& str) const {
    std::cout << "String: " << str.c_str() << ", Length: " << str.getLength() << std::endl;
}

String::~String() {
    delete[] data; // Free allocated memory
}
/* Move Constructor */
/*
lvalue vs rvalue:
An lvalue refers to an object that has a persistent state and can be addressed in memory (i.e., has a name).
An rvalue is a temporary object or value that does not have a persistent state and cannot be addressed in memory (i.e., typically unnamed).
Move constructor is invoked when an rvalue (temporary object) is used to initialize a new object.
String a = String("Temporary"); // Move constructor is called here
The move constructor transfers ownership of resources from the temporary object to the new object, leaving the temporary in a valid but unspecified state.
*/
String::String(String &&stringToMove) noexcept 
    : data(stringToMove.data), length(stringToMove.length) {
    // Leave stringToMove in a valid state
    stringToMove.data = new char[1]; // Allocate memory for empty string
    stringToMove.data[0] = '\0';
    stringToMove.length = 0;
}

//Copy Assignment Operator
String& String::operator=(String stringToCopy){
    if( this != &stringToCopy){
        //Self-assignment check eg. String a; a = a;
        delete[] data; // Free existing memory
        length = stringToCopy.length;
        data = new char[length + 1]; // Allocate new memory
        std::memcpy(data, stringToCopy.data, length + 1); // Copy including null-terminator
    }
    return *this;
}

//Move Assignment Operator


int main(){
    //Example usage of the String class
    String str1; // Default constructor
    std::cout << "str1: "<<str1.c_str()<<" Length: "<<str1.getLength()<<std::endl;

    String str2("Hello, World!"); //Passing string literal i.e. RO data/ // Constructor from C-style string
    std::cout << "str2: "<<str2.c_str()<<" Length: "<<str2.getLength()<<std::endl;

    String str3(str2);  // Copy Constructor
    std::cout << "str3 (copy of str2): "<<str3.c_str()<<" Length: "<<str3.getLength()<<std::endl;

    String str3_copy = str2;  // Copy Constructor via direct initialization
    std::cout << "str3_copy (copy of str2 via direct initialization): "<<str3_copy.c_str()<<" Length: "<<str3_copy.getLength()<<std::endl;

    String str4(nullptr); // Handle null pointer input
    std::cout << "str4 (from nullptr): "<<str4.c_str()<<" Length: "<<str4.getLength()<<std::endl;

    char array[] = "Sample C-Style String";
    String str5(array); // Constructor from C-style string
    std::cout << "str5: "<<str5.c_str()<<" Length: "<<str5.getLength()<<std::endl;

    const char *array2 = array;
    String str6(array2); // Constructor from C-style string
    std::cout << "str6: "<<str6.c_str()<<" Length: "<<str6.getLength()<<std::endl;  

    std::string str7 = "Reference std::string";
    std::string &refStr = str7;
    String str8(refStr.c_str()); // Copy Constructor using reference
    std::cout << "str8 (copy of str2 via reference): "<<str8.c_str()<<" Length: "<<str8.getLength()<<std::endl;

    String & str9 = str2; // Reference to existing String object
    String str10(str9); // Copy Constructor using String reference
    std::cout << "str10 (copy of str2 via String reference): "<<str10.c_str()<<" Length: "<<str10.getLength()<<std::endl;   

    //Move Constructor
    String str11(String("Temporary String")); // Move constructor
    std::cout << "str11 (moved from temporary): "<<str11.c_str()<<" Length: "<<str11.getLength()<<std::endl;    
    String str12(std::move(str2)); // Move constructor using std::move
    std::cout << "str12 (moved from str2): "<<str12.c_str()<<" Length: "<<str12.getLength()<<std::endl;    
    std::cout << "str2 after move: "<<str2.c_str()<<" Length: "<<str2.getLength()<<std::endl;

    //Copy Assignment Operator
    String str13;
    str13 = str3; // Copy Assignment Operator
    std::cout << "str13 (after copy assignment from str3): "<<str13.c_str()<<" Length: "<<str13.getLength()<<std::endl;

    //Overloading << and >> operators for printing and input can be added later

    return 0;
}
