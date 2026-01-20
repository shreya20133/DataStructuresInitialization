#include <iostream>
void print(const int& value){
    std::cout << "Value: " << value << std::endl;
    //value = 10 is invalid as value is a const lvalue reference and cannot be modified.
}
int main(){

    //lvalue is an object that occupies some identifiable location in memory (i.e., has a name)
    int x = 10; // 'x' is an lvalue
    int& lvalueRef = x; // lvalue reference to x --> lvalueRef is a reference to an int x.
    const int& constLvalueRef = x; // const lvalue reference to x means this constLvalueRef cannot modify x.
    const int& tempConstLvalueRef = 15; // const lvalue reference can bind to an rvalue (temporary)
    std::cout << "Lvalue x: " << x << ", Lvalue Reference: " << lvalueRef << ", Const Lvalue Reference: " << constLvalueRef << std::endl;
    lvalueRef = 20; // Modifying x through lvalue reference
    std::cout << "After modifying lvalueRef, x: " << x << std::endl;
    print(x);
    print(25); // 25 is an rvalue but can bind to const lvalue reference in print function
    //rvalue is a temporary object or value that does not have a persistent state (i.e., typically unnamed)
    int y = 30; // 'y' is an lvalue and 30 is an rvalue
    int&& rvalueRef = 40; // rvalue reference to a temporary rvalue
    std::cout << "Rvalue Reference: " << rvalueRef << std::endl;
    rvalueRef = 50; // Modifying the rvalue reference
    std::cout << "After modifying rvalueRef: " << rvalueRef << std::endl;

    int num1 = 2;
    int num2 = 20000000;
    int result = num1 + num2; // 'num1 + num2' is an rvalue
    std::cout << "Result of num1 + num2: " << result << std::endl;

    int &&resultRef = num1 + num2; // rvalue reference binding to the rvalue 'num1 + num2'
    std::cout << "Rvalue Reference to (num1 + num2): " << resultRef << std::endl;
    return 0;
}