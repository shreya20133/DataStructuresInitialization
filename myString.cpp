#include <iostream>
#include <cstring>
using namespace std;

class myString{
    public :
        myString(): str(nullptr), length(0) {} // Default constructor - Empty string initialization
        myString(const char* s) : str(new char[strlen(s) + 1]), length(strlen(s)) { // Parameterized constructor
            strcpy(str, s); // Copy the input string to the member variable
        }   

        myString(const myString& other) : str(new char[other.length + 1]), length(other.length) { // Copy constructor
            strcpy(str, other.str); // Copy the string from the other object
        }

        myString& operator=(const myString& other){
            if(this != &other){ // check for self-assignment because if we assign an object to itself, we dont want to delete the memory of the object before copying it. This would lead to undefined behavior and potential crashes. 
                delete[] str; // Free the existing memory(Since this is copy assignment operator, we need to free the existing memory of the object before copying the new data from the other object. This is to avoid memory leaks and ensure that we are not holding onto memory that is no longer needed.)
                length = other.length; // Copy the length from the other object
                str = new char[length + 1]; // Allocate new memory for the string
                strcpy(str, other.str); // Copy the string from the other object
            }
            return *this;
        }

        bool operator==(const myString& other) const{
            return strcmp(str,other.str) == 0; // Compare the strings using strcmp
        }
        friend ostream& operator<<(ostream& os, const myString& s){//Declared as friend function so that it can access the private members of the class. This allows us to directly access the 'str' member variable of the 'myString' class and output its value to the output stream.
            os << s.str; // Output the string to the output stream
            return os;
        }
    private :
        char* str; // Pointer to hold the string data - Why not just use char str[length+1]? Because we want to allocate memory dynamically based on the length of the input string, and using a pointer allows us to do that. Using a fixed-size array would limit the maximum length of the string we can store.
        size_t length; // Length of the string
        //char str[length+1]; // Array to hold the string data - This is not valid C++ code. You cannot declare an array with a size that is not a compile-time constant. The size of the array must be known at compile time, but 'length' is determined at runtime. Therefore, this line will cause a compilation error. Instead, we should use a pointer to dynamically allocate memory for the string data, as shown in the parameterized constructor and copy constructor.
};

int main(){

    myString s1 = "Hello";
    myString s2("Shreya");
    myString s3 = s1;
    myString s4(s2);
    cout << "s1 : " << s1 << "\n s2: " << s2 << "\n s3 : " << s3 << "\n s4 : "<<s4<<endl;
    s4 = s1; //copy assignment operator will be called here
    s4 = "World"; //copy assignment operator will be called here
    if(s4 == s1) //comparison operator will be called here
        cout << "Strings are equal" << endl;
    else
        cout << "Strings are not equal" << endl;

}