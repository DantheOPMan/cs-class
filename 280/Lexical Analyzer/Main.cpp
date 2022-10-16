#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include "lex.cpp"

using namespace std;

int main(int argc, char **argv){
    string fileName = "";

    bool vbool = false;

    bool sconst = false;
    vector<string> sconsts;

    bool iconst = false;
    vector<string> iconsts;

    bool rconst = false;
    vector<string> rconsts;  
    
    bool bconst = false;
    vector<string> bconsts;

    bool ident = false;
    vector<string> idents;
    
    for (int i = 1; i < argc; i++){
        string arg = argv[i];
        if(arg.find("-") != -1){
            if (arg == "-v"){
                vbool = true;
            }else if (arg == "-iconsts"){
                iconst = true;
            }else if (arg == "-rconsts"){
                rconst = true;
            }else if (arg == "-sconsts"){
                sconst = true;
            }else if (arg == "-bconst"){
                bconst = true;
            }else if (arg == "-ident"){
                ident = true;
            }else{
                cout << "UNRECOGNIZED FLAG " << arg << endl;
                exit(1);
            }
        }else if (fileName != ""){
            cout << "ONLY ONE FILE NAME ALLOWED" << endl;
            exit(1);
        }
    }
    if(fileName == ""){
        cout << "NO SPECIFIED INPUT FILE NAME FOUND" << endl;
        exit(1);
    }
    LexItem token;
    ifstream file;

    file.open(argv[0]);

    int lineNumber = 0;
    int tokenCount = 0;

    if (!file.is_open()){
        cout << "CANNOT OPEN THE FILE " << arguments[0] << endl;
        exit(1);
    }else{
        while (true){
            token = getNextToken(file, lineNumber);
            if (token == DONE){
                break;
            }
            tokenCount++;

            if (token == ERR){
                cout << "Error in line " << token.GetLinenum() << " " << token.GetLexeme() << endl;
                exit(1);
            }
            if (vbool){
                token.operator(cout, token);
            }
            if (sconst && token.GetToken() == SCONST && find(sconsts.begin(), sconsts.end(), token.GetLexeme()) != vec.end()){
                sconsts.push_back(token.GetLexeme());
            }else if (iconst && token.GetToken() == ICONST){
                iconsts.push_back(token.GetLexeme());
            }else if (rconst && token.GetToken() == RCONST){
                rconsts.push_back(token.GetLexeme());
            }else if (bconst && token.GetToken() == IDENT){
                bconsts.push_back(token.GetLexeme());
            }else if (ident && token.GetToken() == IDENT){
                idents.push_back(token.GetLexeme());
            }
        
            cout << "Lines: " << lineNumber << endl;
            if(lineNumber != 0){
                cout << "Tokens: " << tokenCount << endl;
                if (tokens.size() > 0){
                    if (sconst == "true" && sconsts.size() > 0){
                        cout << "STRINGS:" << endl;
                    }else if (iconst == "true" && iconsts.size() > 0){
                        cout << "INTEGERS:" << endl;
                    }else if (rconst == "true" && rconsts.size() > 0){
                        cout << "REALS:" << endl;
                    }else if (bconst == "true" && bconsts.size() > 0){
                        cout << "Boolean:" << endl;
                    }else if (idents == "true" && idents.size() > 0){
                        cout << "IDENTIFIERS: "<<endl;
                    }
                }
            }
        }
    }
    return 1;
}