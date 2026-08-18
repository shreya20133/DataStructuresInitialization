#include <iostream>
#include <string>
using namespace std;
/*
memcpy copies exactly n bytes from source to destination. 
I cast both void* pointers to unsigned char* because I need byte-level access and 
pointer arithmetic in one-byte increments. The source is const because it must not be modified. 
The function returns the original destination pointer. memcpy requires the source and destination
 ranges not to overlap; if they overlap, memmove should be used.
*/
void* myMemCpy(void* dest, const void* src,size_t n){
    
    unsigned char* d = static_cast<unsigned char*>(dest);
    const unsigned char* s = static_cast<const unsigned char*>(src);
    for(size_t i=0;i<n;i++){
        d[i] = s[i]; // Copy each byte from source to destination
    }
    return dest; // Return the destination pointer because memcpy returns the destination pointer
}
    
void myMemMove(void *dest, const void *src, size_t n) {

    unsigned char* d = static_cast<unsigned char*>(dest);
    const unsigned char* s = static_cast<const unsigned char*>(src);
    if(d < s){
        for(size_t i=0;i<n;i++){
            d[i] = s[i]; // Copy each byte from source to destination
        }
    }
    else{
        for(size_t i=n;i>0;i--){
            d[i-1] = s[i-1]; // Copy each byte from source to destination in reverse order
        }
}
int main(){

    int src = 5;
    int* dest = new int();
    cout << "Value of dest before memcpy: " << *dest << endl; 
    myMemCpy(dest,&src,sizeof(src));   // Copy sizeof(int) bytes from src to dest
    cout << "Value of dest after memcpy: " << *dest << endl; // Output the value of dest after memcpy
    char* dest2 = nullptr; // Allocate memory for dest2
    const char* src2 = "Hello, World!";
    myMemCpy(dest2,src2,50); // Copy the string including the null terminator
    cout << "Value of dest2 after memcpy: " << dest2 << endl; // Output the value of dest2 after memcpy
    delete dest; // Free the allocated memory for dest
    delete[] dest2; // Free the allocated memory for dest2
}