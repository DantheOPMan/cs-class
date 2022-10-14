#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include "lex.cpp"

using namespace std;

int main(int argc, char **argv)
{
    vector<string> arguments = CommandArg(argc, argv);
    LexItem token;
    ifstream file;

    file.open(argv[0]);

    vector<LexItem> tokens;
    int lineNumber = 0;
    int tokenCount = 0;

    if (file.is_open()){
        while (true){
            token = getNextToken(file, lineNumber);
            if (token == DONE){
                break;
            }

            tokenCount++;

            if (arguments[1] == "true"){
                cout << token << endl;
            }else if (arguments[2] == "true" && token.GetToken() == ICONST){
                tokens.push_back(token);
            }else if (arguments[3] == "true" && token.GetToken() == RCONST){
                tokens.push_back(token);
            }else if (arguments[4] == "true" && token.GetToken() == SCONST){
                tokens.push_back(token);
            }else if (arguments[5] == "true" && token.GetToken() == IDENT){
                tokens.push_back(token);
            }
            if (token == ERR){
                cout << "ERROR ON LINE " << token.GetLinenum() << " " << token.GetLexeme() << endl;
                exit(1);
            }
        }
    }
}

void BoolArgs(std::vector<std::string> &arguments, int index){
     for (int i = 1; i < arguments.size(); i++){
        arguments[i] = i == index ? "true" : "false";
     }
}
vector<string> CommandArg(int argc, char **argv){
    vector<string> properties{"file", "false", "false", "false", "false", "false"};
    for (int i = 1; i < argc; i++){
        string arg = argv[i];
        if (arg == "-v"){
            BoolArgs(properties, 1);
        }else if (arg == "-iconsts"){
            BoolArgs(properties, 2);
        }else if (arg == "-rconsts"){
            BoolArgs(properties, 3);
        }else if (arg == "-sconsts"){
            BoolArgs(properties, 4);
        }else if (arg == "-ids"){
            BoolArgs(properties, 5);
        }else if (arg.find(".txt") != -1){
            if (properties[0] != "file"){
                cout << "ONLY ONE FILE NAME ALLOWED" << endl;
                exit(1);
            }
            properties[0] = arg;
        }else{
            cout << "UNRECOGNIZED FLAG " << arg << endl;
            exit(1);
        }
    }
    return properties;
}