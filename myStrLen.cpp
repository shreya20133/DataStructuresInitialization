#include <iostream>
#include <string>
using namespace std;

size_t myStrlen(const char* str){
    const char* start = str;
    while(*str!='\0')   str++;
    return str - start;
}

int main() {

    cout <<"Length of \"Hello\" : " << myStrlen("Hello") <<"\n";
    string s = "Hello World";
    cout <<"Length of s : " << myStrlen(s.c_str()) << "\n";
    const char * s2 = "Shreya Garg";
    cout <<"Length of s2 : " << myStrlen(s2) << "\n";
    char s3[] = "Learning";
    cout <<"Length of s3 : "<<myStrlen(s3) << "\n";

    return 0;
}