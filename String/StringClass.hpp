#include<iostream>

class String {
    private:
        /*
        Char pointer to hold the string data.
        Heap-allocated buffer to store the actual string characters.
        */
        char *data;
         /*
        Wny size_t length instead of int?
        Using size_t for length is a common practice in C++ because:
        1. size_t is an unsigned type, which means it can only represent non-negative values. This is important for sizes and lengths, as they should never be negative.
        2. size_t is guaranteed to be able to represent the size of the largest possible object on the target platform, making it more suitable for memory-related operations.
        3. Using size_t helps avoid potential issues with signed/unsigned comparisons and arithmetic that can arise when using int for sizes.
        4. It aligns with standard library conventions, as many standard library functions (like sizeof, strlen, etc.) return size_t for sizes and lengths.
        |    Feature      	        |         int	              |   size_t
        ----------------------------|-----------------------------|-------------------   
            Max String Size(64-bit)	        ~2.1 GB	                ~18.4 Billion GB
            Can be negative?	        Yes (Logically incorrect)	No (Correct)
            Standard Compatibility	    Poor (Requires casting)	    Native
            Portability	               Fixed at 32-bit usually	    Adjusts to system (32 or 64 bit)
        */
        // length of the string excluding null-terminator. We will keep data null-terminated by default.
        size_t length;  

        public:
        /* 
            Following the Rule of Five:
            If your class manually manages a resource, you must define how it is copied, moved, and destroyed.
            “Resource” = memory, file, mutex, socket, GPU handle, etc.
            1. Destructor
            2. Copy Constructor
            3. Copy Assignment Operator
            4. Move Constructor
            5. Move Assignment Operator

            | Situation                   | Function        |
            | --------------------------- | --------------- |
            | Object dies                 | Destructor      |
            | New object from existing    | Copy ctor       |
            | Existing object overwritten | Copy assignment |
            | Temporary → object          | Move ctor       |
            | Temporary → existing        | Move assignment |

            Owning memory of class means that the class is responsible for managing the memory allocation and deallocation for its resources. This includes:
            1. Allocating memory when an object of the class is created.
            2. Deallocating memory when the object is destroyed to prevent memory leaks.
            3. Implementing copy and move semantics to ensure that when objects are copied or moved, the memory is handled correctly (deep copy for copy operations, transferring ownership for move operations).

            For non owning memory, the class would not be responsible for managing the memory lifecycle.
        */
        
        //Constructors 
        String();   //Default Constructor
        String(const char *str); // from C-style string
        String(const String &stringToCopy); // Copy Constructor
        String(String &&stringToMove) noexcept; // Move Constructor

        /* Exception-safety */
        /*
        Exception safety guarantees define how a program behaves in the presence of exceptions. There are generally three levels of exception safety:
            1. Allocate Before Deleting: This is a basic exception safety technique. The idea is simple:
- Problem: If you delete old memory first and then try to allocate new memory, an exception during allocation leaves your object in a broken state (no valid data).
- Solution: Always allocate the new resource first. Only after successful allocation do you release the old one.
            2. Strong Guarantee: The strong exception safety guarantee ensures that if an operation fails (throws an exception), the program state remains unchanged as if the operation was never attempted. This is often achieved through techniques like copy-and-swap, where a temporary copy of the object is created and modified, and only if all operations succeed is the original object updated.
            3. No-Throw Guarantee: The no-throw guarantee ensures that certain operations will never throw exceptions. This is typically achieved by using only operations that are guaranteed not to throw, such as operations on built-in types or using noexcept functions.
        */
       
        //Assignment Operators
        //Traditional Copy Assignment Operator
        String& operator=(const String &stringToCopy); // Copy Assignment Operator
        
       // Copy-and-swap form assignment operator
        String& operator=(String other);
        //How is this different from traditional copy assignment operator?
        /*
            1. Exception Safety: The copy-and-swap idiom provides strong exception safety guarantees.
            2. Code Simplicity: The copy-and-swap idiom can lead to simpler and more maintainable code.
            3. Self-Assignment Safety: The copy-and-swap idiom inherently handles self-assignment correctly.
        
            MyString&          // returns a reference to *this
            operator=          // assignment operator
            ( MyString other ) // parameter passed BY VALUE

            To assign one String to another, first make a copy of the source String(RHS string) then swap its data with the current String(LHS string).
            If any exception occurs during the copy, the current String remains unchanged.
            After the swap, the temporary copy goes out of scope and its destructor is called, releasing the old resources of the current String.
        */


       
};