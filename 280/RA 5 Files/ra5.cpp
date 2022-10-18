#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include "lex.h"
//#include "tokenListing.cpp"
#include <cctype>
#include <string>
using std::map;

using namespace std;

LexItem id_or_kw(const string& lexeme, int linenum){
    return LexItem(IDENT, lexeme, linenum);
}

ostream& operator<<(ostream& out, const LexItem& tok){
    
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
    map<Token,string> tokenPrint {
		{PROGRAM, "PROGRAM"},
		{PRINT, "PRINT"},
		{INT, "INT"},
		{ END, "END" },
		{ FLOAT, "FLOAT"},
		{ BOOL, "BOOL" },
		
		{ ELSE, "ELSE" },
		{ IF, "IF" },
		
		{THEN, "THEN"},
		{ TRUE, "TRUE" },
		{ FALSE, "FALSE" },
		
		{ IDENT, "IDENT" },

		{ ICONST, "ICONST" },
		{ RCONST, "RCONST" },
		{ SCONST, "SCONST" },
		{ BCONST, "BCONST" },
		
		{ PLUS, "PLUS" },
		{ MINUS, "MINUS" },
		{ MULT, "MULT" },
		{ DIV, "DIV" },
		{ ASSOP, "ASSOP" },
		{ EQUAL, "EQUAL" },
		{ GTHAN, "GTHAN" },
		{ LTHAN, "LTHAN" },
		{ AND, "AND" },
		{ OR, "OR" },
		{ NOT, "NOT" },
            
		{ COMMA, "COMMA" },
		{ LPAREN, "LPAREN" },
		{ RPAREN, "RPAREN" },
		
		
		{ SEMICOL, "SEMICOL" },
		
		{ ERR, "ERR" },

		{ DONE, "DONE" },
    };
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

    if(tok.GetToken() == RCONST || tok.GetToken() == BCONST || tok.GetToken() == ICONST){
        out << tokenPrint[tok.GetToken()] << ": ("<< tok.GetLexeme() << ") at Line " << tok.GetLinenum() << endl;
    }else if(tok.GetToken() == ERR){
        out << "Error: : \""<< tok.GetLexeme() << "\" at Line " << tok.GetLinenum() << endl;
    }else if(kwmap.find(tok.GetLexeme()) != kwmap.end()){
        out << "KEYWORD: " << tok.GetLexeme() << " at Line " << tok.GetLinenum() << endl;
    }else if(tok.GetToken() == SCONST || tok.GetToken() == ERR) {
        out << tokenPrint[tok.GetToken()] << ": \""<< tok.GetLexeme() << "\" at Line " << tok.GetLinenum() << endl;
    }else if(tok.GetToken() == IDENT){
        out << tokenPrint[tok.GetToken()] << ": "<< tok.GetLexeme() << " at Line " << tok.GetLinenum() << endl;
    } else{
        out << tokenPrint[tok.GetToken()] << ": '"<< tok.GetLexeme() << "' at Line " << tok.GetLinenum() << endl;
    }
    
    return out;
}