#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include "lex.h"

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
            }else if (arg == "-iconst"){
                iconst = true;
            }else if (arg == "-rconst"){
                rconst = true;
            }else if (arg == "-sconst"){
                sconst = true;
            }else if (arg == "-bconst"){
                bconst = true;
            }else if (arg == "-ident"){
                ident = true;
            }else{
                cout << "UNRECOGNIZED FLAG " << arg << endl;
                exit(1);
            }
        }else if (fileName == ""){
            fileName = arg;
        }else{
            cout << "ONLY ONE FILE NAME ALLOWED" << endl;
        exit(1);
        }
    }
    if(fileName == ""){
        cout << "NO SPECIFIED INPUT FILE NAME" << endl;
        exit(1);
    }
    LexItem token;
    ifstream file;

    file.open(fileName);

    int lineNumber = 0;
    int tokenCount = 0;

    if (!file.is_open()){
        cout << "CANNOT OPEN THE FILE " << fileName << endl;
        exit(1);
    }else{
        int count = 0;
        string noWhitespace = get(file);
        noWhitespace.erase(std::remove_if(noWhitespace.begin(), noWhitespace.end(), ::isspace), noWhitespace.end());
        if(noWhitespace.length() > 0){

        
        while (count < 40){
            count++;
            LexItem token = getNextToken(file, lineNumber);
            if (token == DONE){
                break;
            }
            tokenCount++;

            if (token == ERR){
                cout << "Error in line " << token.GetLinenum() << " " << token.GetLexeme() << endl;
                exit(1);
            }
            if (vbool){
                cout << token << endl;
            }
            if (sconst && token.GetToken() == SCONST && find(sconsts.begin(), sconsts.end(), token.GetLexeme()) != sconsts.end()){
                sconsts.push_back(token.GetLexeme());
            }else if (iconst && token.GetToken() == ICONST && find(iconsts.begin(), iconsts.end(), token.GetLexeme()) != iconsts.end()){
                iconsts.push_back(token.GetLexeme());
            }else if (rconst && token.GetToken() == RCONST  && find(rconsts.begin(), rconsts.end(), token.GetLexeme()) != rconsts.end()){
                rconsts.push_back(token.GetLexeme());
            }else if (bconst && token.GetToken() == IDENT && find(bconsts.begin(), bconsts.end(), token.GetLexeme()) != bconsts.end()){
                bconsts.push_back(token.GetLexeme());
            }else if (ident && token.GetToken() == IDENT && find(idents.begin(), idents.end(), token.GetLexeme()) != idents.end()){
                idents.push_back(token.GetLexeme());
            }
        }
        }
        cout << "Lines: " << lineNumber << endl;
        if(lineNumber != 0){
            cout << "Tokens: " << tokenCount << endl;
            if (sconst == true && sconsts.size() > 0){
                cout << "STRINGS:" << endl;
            }else if (iconst == true && iconsts.size() > 0){
                cout << "INTEGERS:" << endl;
            }else if (rconst == true && rconsts.size() > 0){
                cout << "REALS:" << endl;
            }else if (bconst == true && bconsts.size() > 0){
                cout << "Boolean:" << endl;
            }else if (ident == true && idents.size() > 0){
                cout << "IDENTIFIERS: "<<endl;
            }      
        }
    }
    return 1;
}