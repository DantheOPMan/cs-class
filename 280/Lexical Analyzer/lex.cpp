#include <iostream>
#include <regex>
#include <map>
#include <stdio.h>
#include <ctype.h>
#include "lex.h"

using namespace std;


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
    if (eval){
        out << " (" << tok.GetLexeme() << ")";
    }
    return out;
}

LexItem id_or_kw(const string& lexeme, int linenum){
    map <string, Token> tokString {
		{"PROGRAM", PROGRAM},
		{"PRINT", PRINT},
		{"INT", INT},
		{ "END", END },
		{ "FLOAT", FLOAT},
		{ "BOOL", BOOL },
		
		{ "ELSE", ELSE },
		{ "IF", IF },
		
		{"THEN", THEN},
		{ "TRUE", TRUE },
		{ "FALSE", FALSE },
		
		{ "IDENT", IDENT },

		{ "ICONST", ICONST },
		{ "RCONST", RCONST },
		{ "SCONST", SCONST },
		{ "BCONST", BCONST },
		
		{ "PLUS", PLUS },
		{ "MINUS", MINUS },
		{ "MULT", MULT },
		{ "DIV", DIV },
		{ "ASSOP", ASSOP},
		{ "EQUAL", EQUAL },
		{ "GTHAN", GTHAN },
		{ "LTHAN", LTHAN },
		{ "AND", AND },
		{ "OR", OR },
		{ "NOT", NOT },
            
		{ "COMMA", COMMA},
		{ "LPAREN", LPAREN },
		{ "RPAREN", RPAREN },
		
		
		{ "SEMICOL", SEMICOL },
		
		{ "ERR", ERR },

		{ "DONE", DONE },
	};

    LexItem output = LexItem(ERR, lexeme,linenum);
    if(lexeme == "+"){
        output = LexItem(PLUS, lexeme, linenum);
    }else if(lexeme == "-"){
        output = LexItem(MINUS, lexeme, linenum);
    }else if(lexeme == "*"){
        output = LexItem(MULT, lexeme, linenum);
    }else if(lexeme == "/"){
        output = LexItem(DIV, lexeme, linenum);
    }else if(lexeme == "="){
        output = LexItem(ASSOP, lexeme, linenum);
    }else if(lexeme == "("){
        output = LexItem(LPAREN, lexeme, linenum);
    }else if(lexeme == ")"){
        output = LexItem(RPAREN, lexeme, linenum);
    }else if(lexeme == ">"){
        output = LexItem(GTHAN, lexeme, linenum);
    }else if(lexeme == "<"){
        output = LexItem(LTHAN, lexeme, linenum);
    }else if(lexeme == "!"){
        output = LexItem(NOT, lexeme, linenum);
    }else if(lexeme == ";"){
        output = LexItem(SEMICOL, lexeme, linenum);
    }else if(lexeme == ","){
        output = LexItem(COMMA, lexeme, linenum);
    }
    return output;
}

LexItem getNextToken(istream& in, int& linenum){
    enum TokState { START, INID, INSTRING, ININT, INREAL, INCOMMENT}lexstate = START;
    string lexeme = "";
    char ch;
    char nextChar;
    while(in.get(ch)) {
        nextChar = in.peek();
        switch(lexstate){
        case START:
            if(ch == -1){
                return LexItem(DONE, lexeme, linenum);
            }
            if( ch == '\n' ){
                linenum++;
            }
            if(isspace(ch)){
                continue;
            }
            lexeme = ch;
            
            if(ch == '/' && nextChar == '*'){
                lexstate = INCOMMENT;
                continue;
            }
            if(lexeme =="=" && nextChar == '='){
                in.get(ch);
                lexeme += ch;
                return LexItem(EQUAL, lexeme, linenum);
            }
            if(lexeme =="&" && nextChar == '&'){
                in.get(ch);
                lexeme += ch;
                return LexItem(AND, lexeme, linenum);
            }
            if(lexeme =="|" && nextChar == '|'){
                in.get(ch);
                lexeme += ch;
                return LexItem(OR, lexeme, linenum);
            }
            if (lexeme == "\""){
                lexstate = INSTRING;
                continue;
            }
            if (isdigit(ch)){
                lexstate = ININT;
                continue;
            }
            if(lexeme == "."){
                lexstate=INREAL;
                continue;
            }
            if(isalpha(ch)){
                lexstate = INID;
                continue;
            }
            return id_or_kw(lexeme,linenum);
        
        case INID:
            if(isalnum(ch) || ch == '_'){
                lexeme += ch;
            }
            if (nextChar == -1 || isspace(nextChar) || (!isalnum(ch) || ch != '_')) {
                lexstate = START;
                //in.putback(ch);
                if(lexeme =="PROGRAM"){
                    return LexItem(PROGRAM, lexeme, linenum);
                }else if (lexeme == "print"){
                    return LexItem(PRINT, lexeme, linenum);
                }else if (lexeme == "end"){
                    return LexItem(END, lexeme, linenum);
                }else if (lexeme == "if"){
                    return LexItem(IF, lexeme, linenum);
                }else if (lexeme == "then"){
                    return LexItem(THEN, lexeme, linenum);
                }else if (lexeme == "float"){
                    return LexItem(FLOAT, lexeme, linenum);
                }else if (lexeme == "int"){
                    return LexItem(INT, lexeme, linenum);
                }else if (lexeme == "bool"){
                    return LexItem(BOOL, lexeme, linenum);
                }else if (lexeme == "else"){
                    return LexItem(ELSE, lexeme, linenum);
                }else if (lexeme == "true"){
                    return LexItem(TRUE, lexeme, linenum);
                }else if (lexeme == "false"){
                    return LexItem(FALSE, lexeme, linenum);
                }else{
                    return LexItem(IDENT, lexeme, linenum);
                }
            }
        break;
        case INSTRING: 
            if (nextChar == -1){
                return LexItem(ERR, lexeme, linenum);
            }
            lexeme += ch;
            if (ch == '\"'){
                lexeme += ch;
                in.get(ch);
                lexeme += ch;
                lexstate = START;
                return LexItem(SCONST, lexeme, linenum);
            }else{
                lexeme += ch;
                continue;
            }
            break;
        case ININT:
            if(isalpha(ch)){
                return LexItem(ERR, lexeme + ch, linenum);
            }
            if(regex_match(lexeme+ch, regex("[0-9]+"))){
                lexeme += ch;
            }else if(ch =='.'){
                lexstate = INREAL;
                in.putback(ch);
                continue;
            }else{
                lexstate = START;
                //in.putback(ch);
                return LexItem(ICONST, lexeme, linenum);   
            }
        break;
        case INREAL:
            if (isalpha(ch)){
                return LexItem(ERR, lexeme + ch, linenum);
            }
            if (regex_match(lexeme + ch, regex("[0-9]*\\.[0-9]+"))){
                lexeme += ch;
            }else if (regex_match(lexeme + ch, regex("[0-9]*\\.[0-9]*"))){
                lexeme += ch;
            }else{
                if (lexeme[lexeme.length() - 1] == '.')

                    return LexItem(ERR, lexeme, linenum);

                lexstate = START;

                in.putback(ch);

                return LexItem(RCONST, lexeme, linenum);
            }
            break;
        case INCOMMENT:
            if (ch == '\n'){
                linenum++;
            }
            if(ch == '*' && nextChar == '/'){
                lexstate = START;
            }
            continue;
        }
    }
    return LexItem(ERR, "", 0);
}