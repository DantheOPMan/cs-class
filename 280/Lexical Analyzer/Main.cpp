#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "lex.h"

using namespace std;

int main(int argc, char **argv){
    string fileName = "";

    bool vbool = false;

    bool sconst = false;
    vector<string> sconsts;

    bool iconst = false;
    vector<int> iconsts;

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
            cout << "ONLY ONE FILE NAME ALLOWED." << endl;
        exit(1);
        }
    }
    if(fileName == ""){
        cout << "NO SPECIFIED INPUT FILE NAME." << endl;
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
        lineNumber = 1;
        LexItem token;
        while ((token = getNextToken(file, lineNumber)).GetToken() != DONE && token != ERR){
            count++;
            if (token == DONE){
                break;
            }
            tokenCount++;

            if (vbool){
                cout << token << endl;
            }
            if (sconst && token.GetToken() == SCONST && find(sconsts.begin(), sconsts.end(), token.GetLexeme()) == sconsts.end()){
                sconsts.push_back(token.GetLexeme());
            }
            if (iconst && token.GetToken() == ICONST){
                int input = 0;
                if(token.GetLexeme().substr(0,1) == "0"){
                    input = stoi(token.GetLexeme().substr(1,token.GetLexeme().length()));
                }else{
                    input = stoi(token.GetLexeme());
                }
                if(find(iconsts.begin(), iconsts.end(), input) == iconsts.end()){
                    iconsts.push_back(input);
                }
            }
            if (rconst && token.GetToken() == RCONST  && find(rconsts.begin(), rconsts.end(), token.GetLexeme()) == rconsts.end()){
                rconsts.push_back(token.GetLexeme());
            }
            if (bconst && token.GetToken() == BCONST && find(bconsts.begin(), bconsts.end(), token.GetLexeme()) == bconsts.end()){
                bconsts.push_back(token.GetLexeme());
            }
            if (ident && token.GetToken() == IDENT && find(idents.begin(), idents.end(), token.GetLexeme()) == idents.end()){
                idents.push_back(token.GetLexeme());
            }
        }
        if (token == ERR){
            if(token.GetLexeme() == "/"){
                lineNumber--;
                cout << "\nMissing a comment end delimiters '*/' at line " << lineNumber << endl;
            }else if(token.GetLexeme() == ""){
                lineNumber--;
            }else if(token.GetLinenum() == 1 && tokenCount == 0){
                cout << "Lines: " << 0 << endl;
                exit(1);
            }else{
                cout << "Error in line " << token.GetLinenum() << " (" << token.GetLexeme() << ")" << endl;
                exit(1);
            }
        }
        cout << "Lines: " << lineNumber << endl;
        if(lineNumber != 0){
            cout << "Tokens: " << tokenCount << endl;
            if (sconst == true && sconsts.size() > 0){
                cout << "STRINGS:" << endl;
                sort(sconsts.begin(), sconsts.end());
                for(string v : sconsts) 
                    cout << "\"" << v.substr(1, v.length() -1)  << "\"" << endl;
            }
            if (iconst == true && iconsts.size() > 0){
                cout << "INTEGERS:" << endl;
                sort(iconsts.begin(), iconsts.end());
                for(int v : iconsts) 
                    cout << v << endl;
            }
            if (rconst == true && rconsts.size() > 0){
                cout << "REALS:" << endl;
                sort(rconsts.begin(), rconsts.end());
                for(string v : rconsts) 
                    cout << v << endl;
            }
            if (bconst == true && bconsts.size() > 0){
                cout << "Booleans:" << endl;
                sort(bconsts.begin(), bconsts.end());
                for(string v : bconsts) 
                    cout << v << endl;
            }
            if (ident == true && idents.size() > 0){
                cout << "IDENTIFIERS:"<<endl;
                sort(idents.begin(), idents.end());
                cout << idents[0] ;
                for(int v = 1; v < idents.size(); v++) 
                    cout << ", " << idents[v];
                cout << endl;
            }     
        }
    }
    return 1;
}