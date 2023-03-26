#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <iomanip>
#include <cstring>

using namespace std; 

//states
struct state{
    int stateVal;
    std::map<char,int> charPointMap;
    std::map<char,string> pull;
    std::map<char,string> push;
};

int main(){

    //intro
    std::cout << "Project 2 for CS 341" << std::endl;
    std::cout << "Section number: 006" << std::endl;
    std::cout << "Semester: Spring 2023" << std::endl;
    std::cout << "Written by: Daniel Yankovich, dy27" << std::endl;
    std::cout << "Instructor: Marvin Nakayama, marvin@njit.edu\n" << std::endl;

    //setup the states through character mapping
    state states[10];
    char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    for(int i = 0; i< 10; i++){
        states[i].stateVal = i;
        if(i==0){
            states[i].charPointMap['$'] = 1;
            states[i].pull['$'] = "";
            states[i].push['$'] = "$";
        }else if(i==1){
            states[i].charPointMap['$'] = 2;
            states[i].pull['$'] = "";
            states[i].push['$'] = "$";
        }else if(i==2){
            states[i].charPointMap['('] = 2;
            states[i].pull['('] = "";
            states[i].push['('] = "(";
            states[i].charPointMap['.'] = 4;
            states[i].pull['.'] = "";
            states[i].push['.'] = "";
            for(int j = 0; j<=9; j++){
                states[i].charPointMap[digits[j]] = 3;
                states[i].pull[digits[j]] = "";
                states[i].push[digits[j]] = "";
            }
        }else if(i==3){
            states[i].charPointMap['.'] = 5;
            states[i].pull['.'] = "";
            states[i].push['.'] = "";
            for(int j = 0; j<=9; j++){
                states[i].charPointMap[digits[j]] = 3;
                states[i].pull[digits[j]] = "";
                states[i].push[digits[j]] = "";
            }
        }else if(i==4){
            for(int j = 0; j<=9; j++){
                states[i].charPointMap[digits[j]] = 5;
                states[i].pull[digits[j]] = "";
                states[i].push[digits[j]] = "";
            }
        }else if(i==5){
            states[i].charPointMap['+'] = 7;
            states[i].pull['+'] = "";
            states[i].push['+'] = "";
            states[i].charPointMap['-'] = 7;
            states[i].pull['-'] = "";
            states[i].push['-'] = "";
            states[i].charPointMap['*'] = 7;
            states[i].pull['*'] = "";
            states[i].push['*'] = "";
            states[i].charPointMap['/'] = 7;
            states[i].pull['/'] = "";
            states[i].push['/'] = "";
            for(int j = 0; j<=9; j++){
                states[i].charPointMap[digits[j]] = 5;
                states[i].pull[digits[j]] = "";
                states[i].push[digits[j]] = "";
            }
            states[i].charPointMap[')'] = 6;
            states[i].pull[')'] = "(";
            states[i].push[')'] = "";
            states[i].charPointMap['$'] = 8;
            states[i].pull['$'] = "$";
            states[i].push['$'] = "";
        }else if(i==6){
            states[i].charPointMap['+'] = 7;
            states[i].pull['+'] = "";
            states[i].push['+'] = "";
            states[i].charPointMap['-'] = 7;
            states[i].pull['-'] = "";
            states[i].push['-'] = "";
            states[i].charPointMap['*'] = 7;
            states[i].pull['*'] = "";
            states[i].push['*'] = "";
            states[i].charPointMap['/'] = 7;
            states[i].pull['/'] = "";
            states[i].push['/'] = "";
            states[i].charPointMap[')'] = 6;
            states[i].pull[')'] = "(";
            states[i].push[')'] = "";
            states[i].charPointMap['$'] = 8;
            states[i].pull['$'] = "$";
            states[i].push['$'] = "";
        }else if(i==7){
            for(int j = 0; j<=9; j++){
                states[i].charPointMap[digits[j]] = 3;
                states[i].pull[digits[j]] = "";
                states[i].push[digits[j]] = "";
            }
            states[i].charPointMap['.'] = 4;
            states[i].pull['.'] = "";
            states[i].push['.'] = "";
            states[i].charPointMap['('] = 7;
            states[i].pull['('] = "";
            states[i].push['('] = "(";
        }else if(i==8){
            states[i].charPointMap['$'] = 9;
            states[i].pull['$'] = "$";
            states[i].push['$'] = "";
        }else if(i==9){
            
        }
    }
    
    //state logic to iterate through all the states
    char c = 0;
    const int endState = 9;
    int curState = 0;
    string stack = "";
    string input;
    do{
        std::cout << "Do you want to enter a string?" << std::endl;
        cin >> input;
        if(input == "y"){
            cout << "Enter a string over Σ:" << endl;
            cin >> input;
            cout << input << endl;
            cout << "q" << curState << "\n";
            for(int i =0; i < input.length(); i++){
                if(states[curState].pull.find(input[i]) != states[curState].pull.end() && states[curState].charPointMap.find(input[i]) != states[curState].charPointMap.end()){
                    cout << "Symbol: "<< input[i] << " Popped: " << states[curState].pull[input[i]] << " Pushed: " << states[curState].push[input[i]] <<" Current State: q" << states[curState].charPointMap[input[i]] << "\n";
                    if(states[curState].pull[input[i]] == ""){
                        curState = states[curState].charPointMap[input[i]];
                        stack.append(states[curState].push[input[i]]);
                    }else if(stack.length() == 0){
                        curState = states[curState].charPointMap[input[i]];
                        stack.append(states[curState].push[input[i]]);
                    }else if(stack.substr(stack.size() - 1) == states[curState].pull[input[i]]){
                        curState = states[curState].charPointMap[input[i]];
                        stack = stack.substr(0, stack.length()-1);
                        stack.append(states[curState].push[input[i]]);
                    }else{
                        cout << "Symbol: "<< input[i] << " Popped: " << " Pushed: " << " Current State:"<< "\n";
                        cout << "Rejected\n" << endl;
                        break;
                    }
                }else{
                    cout << "Symbol: "<< input[i] << " Popped: " << " Pushed: " << " Current State:"<< "\n";
                    cout << "Rejected\n" << endl;
                    break;
                }
            }
            if(curState == endState){

                cout << "Accepted\n" << endl;
            }
            stack = "";
            curState = 0;
        }
    }while (input != "n");
    cout << "Terminated" << endl;
    return 0;
}