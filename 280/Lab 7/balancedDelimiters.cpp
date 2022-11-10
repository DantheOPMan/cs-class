#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

bool BalancedDelimiters(string & inputString){
    vector<string> myvector;
    for(int i = 0; i < inputString.length(); i++){
        if(inputString.substr(i,1) == "(" || inputString.substr(i,1) == "{" || inputString.substr(i,1) == "["){
            myvector.push_back(inputString.substr(i,1));
        }
        if(inputString.substr(i,1) == ")" && myvector.size() > 0){
            if(myvector[myvector.size()-1] != "("){
                if(i + 1 == inputString.length()){
                    cout << "Stack is not empty and the scanning of input string is completed." << endl;
                }else{
                    cout << "Stack is not empty and the scanning of input string is not completed." << endl;
                }
                return false;
            }
            myvector.pop_back();
        }else if(inputString.substr(i,1) == "}" && myvector.size() > 0){
            if(myvector[myvector.size()-1] != "{"){
                if(i + 1 == inputString.length()){
                    cout << "Stack is not empty and the scanning of input string is completed." << endl;
                }else{
                    cout << "Stack is not empty and the scanning of input string is not completed." << endl;
                }               
                return false;
            }
            myvector.pop_back();
        }else if(inputString.substr(i,1) == "]" && myvector.size() > 0){
            if(myvector[myvector.size()-1] != "["){
                if(i + 1 == inputString.length()){
                    cout << "Stack is not empty and the scanning of input string is completed." << endl;
                }else{
                    cout << "Stack is not empty and the scanning of input string is not completed." << endl;
                }
                return false;
            }
            myvector.pop_back();
        }else if(myvector.size() == 0 && (inputString.substr(i,1) == "]" || inputString.substr(i,1) == "}" || inputString.substr(i,1) == ")")){
            cout << "Stack is empty and the scanning of input string is not completed." << endl;
            return false;
        }
    }
    if(myvector.size() >= 1){
        cout << "Stack is not empty and the scanning of input string is completed." << endl;
        return false;
    }
    cout << "Stack is empty and the scanning of input string is completed." << endl;
    return true;
}