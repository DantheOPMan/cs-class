#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include "lex.cpp"

using namespace std;

vector<string> CommandArg(int argc, char **argv);
void BoolArgs(vector<string> &arguments, int index);

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

            cout << endl;
            cout << "Lines: " << lineNumber << endl;

            if (tokenCount != 0){
                cout << "Tokens: " << tokenCount << endl;
            }
            cout << endl;
            if (tokens.size() > 0){
                if (arguments[4] == "true"){
                    cout << "STRINGS:" << endl;
                }else if (arguments[2] == "true"){
                    cout << "INTEGERS:" << endl;
                }else if (arguments[3] == "true"){
                    cout << "REALS:" << endl;
                }else if (arguments[5] == "true"){
                    cout << "IDENTIFIERS: ";
                }
            }
            if (tokens.size() != 0){
                if (tokens.size() == 1){
                    return;
                }
                for (int i = 0; i < tokens.size() - 1; i++){
                    for (int j = i + 1; j < tokens.size(); j++){
                        if (tokens.at(i).GetLexeme() == tokens.at(j).GetLexeme()){
                            tokens.erase(tokens.begin() + j);
                            i--;
                            break;
                        }
                    }
                }
                for (int i = 0; i < tokens.size(); i++){
                    for (int j = i; j < tokens.size(); j++){
                        LexItem remove = tokens.at(j);
                        bool erase = false;
                        if (tokens.at(i).GetToken() == ICONST){
                            int alpha = stoi(tokens.at(j).GetLexeme());
                            int beta = stoi(tokens.at(i).GetLexeme());
                            if (alpha < beta){
                                erase = true;
                            }
                        }else if (tokens.at(i).GetToken() == RCONST){
                            int alpha = stof(tokens.at(j).GetLexeme());
                            int beta = stof(tokens.at(i).GetLexeme());
                            if (alpha < beta){
                                erase = true;
                            }
                        }else if (tokens.at(j).GetLexeme() < tokens.at(i).GetLexeme()){
                            erase = true;
                        }
                        if (erase){
                            tokens.erase(tokens.begin() + j);
                            tokens.insert(tokens.begin() + i, remove);
                        }
                    }
                }
                if (tokens[0].GetToken() != IDENT){
                    for (int i = 0; i < tokens.size(); i++){
                        cout << tokens.at(i).GetLexeme() << endl;
                    }
                }else{
                    for (int i = 0; i < tokens.size() - 1; i++){
                        cout << tokens.at(i).GetLexeme() << ", ";
                    }
                    cout << tokens.at(tokens.size() - 1).GetLexeme() << endl;
                }
            }
        }
    }else{
        cout << "CANNOT OPEN THE FILE " << arguments[0] << endl;
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