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
};

int main(int argc, char *argv[]){

    //intro
    std::cout << "Project 1 for CS 341" << std::endl;
    std::cout << "Section number: 006" << std::endl;
    std::cout << "Semester: Spring 2023" << std::endl;
    std::cout << "Written by: Daniel Yankovich, dy27" << std::endl;
    std::cout << "Instructor: Marvin Nakayama, marvin@njit.edu\n" << std::endl;

    //setup the states and each character mapping
    state states[12];

    for(int i = 0; i< 12; i++){
        states[i].stateVal = i;
        if(i==0){
            states[i].charPointMap['.'] = 11;
            states[i].charPointMap['@'] = 11;
        }else if(i==1){
            states[i].charPointMap['.'] = 2;
            states[i].charPointMap['@'] = 4;
        }else if(i==2){
            states[i].charPointMap['.'] = 11;
            states[i].charPointMap['@'] = 11;
        }else if(i==3){
            states[i].charPointMap['.'] = 2;
            states[i].charPointMap['@'] = 4;
        }else if(i==4){
            states[i].charPointMap['.'] = 11;
            states[i].charPointMap['@'] = 11;
        }else if(i==5){
            states[i].charPointMap['.'] = 6;
            states[i].charPointMap['@'] = 11;
        }else if(i==6){
            states[i].charPointMap['.'] = 11;
            states[i].charPointMap['@'] = 11;
        }else if(i==7){
            states[i].charPointMap['.'] = 6;
            states[i].charPointMap['@'] = 11;
        }else if(i==8){
            states[i].charPointMap['.'] = 11;
            states[i].charPointMap['@'] = 11;
        }else if(i==9){
            states[i].charPointMap['.'] = 11;
            states[i].charPointMap['@'] = 11;
        }else if(i==10){
            states[i].charPointMap['.'] = 6;
            states[i].charPointMap['@'] = 11;
        }else if(i==11){
            states[i].charPointMap['.'] = 11;
            states[i].charPointMap['@'] = 11;
        }
        for(char j = 'a'; j <= 'z'; j++){
            if(i==0){
                states[i].charPointMap[j] = 1;
            }else if(i==1){
                states[i].charPointMap[j] = 1;
            }else if(i==2){
                states[i].charPointMap[j] = 3;
            }else if(i==3){
                states[i].charPointMap[j] = 3;
            }else if(i==4){
                states[i].charPointMap[j] = 5;
            }else if(i==5){
                states[i].charPointMap[j] = 5;
            }else if(i==6){
                if(j == 'e' ){
                    states[i].charPointMap[j] = 8;
                }else{
                    states[i].charPointMap[j] = 7;
                }
            }else if(i==7){
                states[i].charPointMap[j] = 7;
            }else if(i==8){
                if(j == 'd'){
                    states[i].charPointMap[j] = 9;
                }else{
                    states[i].charPointMap[j] = 7;
                }
            }else if(i==9){
                if(j == 'u'){
                    states[i].charPointMap[j] = 10;
                }else{
                    states[i].charPointMap[j] = 7;
                }
            }else if(i==10){
                states[i].charPointMap[j] = 7;
            }else if(i==11){
                states[i].charPointMap[j] = 11;
            }
        }
        for(char j = '0'; j <= '9'; j++){
            if(i==0){
                states[i].charPointMap[j] = 11;
            }else if(i==1){
                states[i].charPointMap[j] = 1;
            }else if(i==2){
                states[i].charPointMap[j] = 11;
            }else if(i==3){
                states[i].charPointMap[j] = 3;
            }else if(i==4){
                states[i].charPointMap[j] = 11;
            }else if(i==5){
                states[i].charPointMap[j] = 5;
            }else if(i==6){
                states[i].charPointMap[j] = 11;
            }else if(i==7){
                states[i].charPointMap[j] = 7;
            }else if(i==8){
                states[i].charPointMap[j] = 7;
            }else if(i==9){
                states[i].charPointMap[j] = 7;
            }else if(i==10){
                states[i].charPointMap[j] = 7;
            }else if(i==11){
                states[i].charPointMap[j] = 11;
            }
        }
    }
    
    //state logic to iterate through all the
    char c = 0;
    const int endState = 10;
    int currentState = 0;
    string input;
    do{
        std::cout << "Do you want to enter a string?" << std::endl;
        cin >> input;
        if(input == "y"){
            cout << "Enter a string over Σ:" << endl;
            cin >> input;
            cout << input << endl;
            cout << "q" << currentState << " ";
            for(int i =0; i < input.length(); i++){
                currentState = states[currentState].charPointMap[input[i]];
                cout << input[i] << " q" << currentState << " ";
            }
            
            if(currentState == endState){
                cout << "Accepted\n" << endl;
            }else{
                cout << "Rejected\n" << endl;
            }
            currentState = 0;       
        }
    }while (input != "n");
    cout << "Terminated" << endl;

    return 0;
}