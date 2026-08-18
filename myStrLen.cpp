#include <iostream>
#include <string>
using namespace std;

size_t myStrlen(const char* str){
    const char* start = str;
    while(*str!='\0')   str++;
    return str - start;
}

char* myStrCpy(char* dest, const char* src){

    char* d = dest;
    while(*src!= '\0'){
        *d = *src; // Copy each character from source to destination
        d++;
        src++;
    }
    *d = '\0'; // Add null terminator at the end of the destination string
    return dest; // Return the destination pointer

}

bool myStrCmp(const char* str1, const char* str2){
    while(*str1 && *str2 ){
        if(*str1 != *str2)   return false; // If characters are not equal, return false
        str1++;
        str2++;
    }
    return *str1 == *str2; // If both strings are equal, return true
}

int main() {

    cout <<"Length of \"Hello\" : " << myStrlen("Hello") <<"\n";
    string s = "Hello World";
    cout <<"Length of s : " << myStrlen(s.c_str()) << "\n";
    const char * s2 = "Shreya Garg";
    cout <<"Length of s2 : " << myStrlen(s2) << "\n";
    char s3[20] = "Learning";
    cout <<"Length of s3 : "<<myStrlen(s3) << "\n";

    char* res = myStrCpy(s3, "Programming");
    cout <<"s3 after copying \"Programming\" : " << s3 << "\n";

    myStrCmp("Hello", "Hello") ? cout << "\"Hello\" and \"Hello\" are equal\n" : cout << "\"Hello\" and \"Hello\" are not equal\n";
    myStrCmp("Hello", "World") ? cout << "\"Hello\" and \"World\" are equal\n" : cout << "\"Hello\" and \"World\" are not equal\n";
    myStrCmp("Hello", "HelloWorld") ? cout << "\"Hello\" and \"HelloWorld\" are equal\n" : cout << "\"Hello\" and \"HelloWorld\" are not equal\n";

    return 0;
}