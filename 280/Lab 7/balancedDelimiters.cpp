#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

bool BalancedDelimiters(string & inputString){
    stack<char> myStack;
    char inputChar[inputString.length() + 1] ;
    strcpy(inputChar, inputString.c_str());
    for(int i = 0; i < inputString.length(); i++){
        if(inputChar[i] == '('){

        }
    }
}