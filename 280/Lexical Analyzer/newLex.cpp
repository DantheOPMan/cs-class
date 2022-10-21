#include <iostream>
#include <regex>
#include <map>
#include <stdio.h>
#include <ctype.h>
#include <algorithm>
#include <string>
#include <boost/algorithm/string.hpp>
#include "lex.h"

using namespace std;

bool nextDone = false;

ostream& operator<<(ostream& out, const LexItem& tok){
    static map<Token, string> tokenPrint{
        {PROGRAM, "PROGRAM"},
        {PRINT, "PRINT"}, 
        {INT,"INT"},
        {END, "END"},
        {IF, "IF"},
        {FLOAT,"FLOAT"},
        {BOOL,"BOOL"},
        {ELSE,"ELSE"},
        {THEN,"THEN"},
        {TRUE,"TRUE"},
        {FALSE,"FALSE"},

        {IDENT, "IDENT"},

        {ICONST, "ICONST"},
        {RCONST, "RCONST"},
        {SCONST, "SCONST"},
        {BCONST,"BCONST"},
    
        {PLUS, "PLUS"},
        {MINUS, "MINUS"},
        {MULT, "MULT"},
        {DIV, "DIV"},
        {ASSOP, "ASSOP"},
        {LPAREN, "LPAREN"},
        {RPAREN, "RPAREN"},
        {COMMA, "COMMA"},
        {EQUAL, "EQUAL"},
        {GTHAN, "GTHAN"},
        {LTHAN, "LTHAN"},
        {SEMICOL, "SEMICOL"},
        {AND, "AND"},
        {OR, "OR"},
        {NOT, "NOT"},

        {ERR, "ERR"},

        {DONE, "DONE"}
    };
    string token = tokenPrint[tok.GetToken()];
    out << token;
    bool eval = 
        (tok.GetToken() == ICONST) || (tok.GetToken() == RCONST) || 
        (tok.GetToken() == SCONST) || (tok.GetToken() == BCONST) || 
        (tok.GetToken() == IDENT);
    if(tok.GetToken() == SCONST){
        out << "(" << tok.GetLexeme().substr(1,tok.GetLexeme().length()-1) << ")";
    }else if (eval){
        out << "(" << tok.GetLexeme() << ")";
    }
    return out;
}

LexItem id_or_kw(const string& lexeme, int linenum){
    map<string,Token> kwmap = {
		{ "PROGRAM", PROGRAM},
		{ "PRINT", PRINT},
		{ "INT", INT},
		{ "END", END },
		{ "FLOAT", FLOAT},
		{ "ELSE", ELSE },
		{ "IF", IF },
		{ "THEN", THEN},
		{ "TRUE", TRUE},
		{ "FALSE", FALSE},
		{ "BOOL", BOOL }
    };
    string data = lexeme;
    boost::to_upper(data);
    if(lexeme == "TRUE" || lexeme == "FALSE"){
        return LexItem(BCONST, lexeme, linenum);
    }
    if(kwmap.find(data) != kwmap.end()){
        return LexItem(kwmap[data], lexeme, linenum);
    }
    return LexItem(IDENT, lexeme, linenum);
}

LexItem getNextToken(istream& in, int& linenum){
    enum TokState { START, INID, INSTRING, ININT, INREAL, INCOMMENT}lexstate = START;
    string lexeme = "";
    char ch;
    while(in.get(ch)){
        switch(lexstate){
        case START:
            if(ch == ' ' && in.peek() == EOF){
                return LexItem(DONE, lexeme, linenum);
            }
            if(ch == '\n' && in.peek() == EOF){
                return LexItem(DONE, lexeme, linenum);
            }
            if(isalpha(ch)){
                ch = toupper(ch);
            }
            if(ch == '\n'){
                linenum++;
                continue;
            }
            if(isspace(ch)){
                continue;
            }
            lexeme = ch;
            if(ch == '/' && in.peek() == '*'){
                lexstate = INCOMMENT;
                continue;
            }
            if(lexeme =="=" && in.peek() == '='){
                in.get(ch);
                lexeme += ch;
                return LexItem(EQUAL, lexeme, linenum);
            }
            if(lexeme =="&" && in.peek() == '&'){
                in.get(ch);
                lexeme += ch;
                return LexItem(AND, lexeme, linenum);
            }
            if(lexeme =="|" && in.peek() == '|'){
                in.get(ch);
                lexeme += ch;
                return LexItem(OR, lexeme, linenum);
            }
            if (lexeme == "\""){
                lexstate = INSTRING;
                continue;
            }
            if(lexeme == "+"){
                return LexItem(PLUS, lexeme, linenum);
            }else if(lexeme == "-"){
                return LexItem(MINUS, lexeme, linenum);
            }else if(lexeme == "*"){
                return LexItem(MULT, lexeme, linenum);
            }else if(lexeme == "/"){
                return LexItem(DIV, lexeme, linenum);
            }else if(lexeme == "="){
                return LexItem(ASSOP, lexeme, linenum);
            }else if(lexeme == "("){
                return LexItem(LPAREN, lexeme, linenum);
            }else if(lexeme == ")"){
                return LexItem(RPAREN, lexeme, linenum);
            }else if(lexeme == ">"){
                return LexItem(GTHAN, lexeme, linenum);
            }else if(lexeme == "<"){
                return LexItem(LTHAN, lexeme, linenum);
            }else if(lexeme == "!"){
                return LexItem(NOT, lexeme, linenum);
            }else if(lexeme == ";"){
                return LexItem(SEMICOL, lexeme, linenum);
            }else if(lexeme == ","){
                return LexItem(COMMA, lexeme, linenum);
            }
            if (isdigit(ch)){
                lexstate = ININT;
                continue;
            }
            if(isalpha(ch) || ch == '_'){
                lexstate = INID;
                continue;
            }
            return LexItem(ERR, lexeme, linenum);
        break;
        case INID:
            if(isalpha(ch)){
                ch = toupper(ch);
            }
            if(isalnum(ch) || ch == '_' || ch == '@'){
                lexeme += ch;
                continue;
            }
            if((ch == '\n' && in.peek() == EOF) || isspace(in.peek()) || (!isalnum(in.peek()) || in.peek() != '_')){
                lexstate = START;
                in.putback(ch);
                return id_or_kw(lexeme,linenum);
            }

        break;
        case INSTRING: 
            if ((ch == '\n' && in.peek() == EOF)){
                lexstate = START;
                return LexItem(ERR, lexeme, linenum);
            }
            if (ch == '\"'){
                lexstate = START;
                return LexItem(SCONST, lexeme, linenum);
            }else if(ch == '\n'){
                lexstate = START;
                return LexItem(ERR, lexeme, linenum);
            }else if(ch == '\'' && in.peek() == ' '){
                lexstate = START;
                lexeme+=ch;
                in.get(ch);
                lexeme+=ch;
                return LexItem(ERR, lexeme, linenum);
            }else{
                lexeme += ch;
                continue;
            }
            break;
        break;
        case ININT:
            if(isalpha(ch)){
                lexeme += ch;
                lexstate = INID;
                continue;
            }else if(isdigit(ch)){
                lexeme += ch;
                continue;
            }else if(ch =='.' && isspace(in.peek())){
                lexeme += ch;
                return LexItem(ERR, lexeme, linenum);
            }else if(ch =='.'){
                lexstate = INREAL;
                lexeme += ch;
                continue;
            }
            if((ch == '\n' && in.peek() == EOF) || isspace(in.peek()) || (!isalnum(in.peek()) || in.peek() != '.')){
                lexstate = START;
                in.putback(ch);
                return LexItem(ICONST, lexeme, linenum);
            }else{
                
                return LexItem(ERR, lexeme, linenum);
            }
        break;
        case INREAL:
            if(isdigit(ch)){
                lexeme += ch;
                continue;
            }else if(ch == '.'){
                lexeme += ch;
                return LexItem(ERR, lexeme, linenum);
            }
            if(ch == '\n' || in.peek() == EOF || isspace(in.peek()) || (!isalnum(in.peek()))){
                lexstate = START;
                in.putback(ch);
                return LexItem(RCONST, lexeme, linenum);
            }
        break;
        case INCOMMENT:
            if (ch == '\n'){
                linenum++;
            }
            if((ch == '\n' && in.peek() == EOF)){
                
                return LexItem(ERR, lexeme, linenum);
            }
            if(ch == '*' && in.peek() == '/'){
                in.get(ch);
                lexstate = START;
            }
        continue;
        }
    }
    return LexItem(ERR, "", linenum);
}