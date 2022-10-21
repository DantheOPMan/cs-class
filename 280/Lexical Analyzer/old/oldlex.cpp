#include <iostream>
#include <regex>
#include <map>
#include "lex.h"

using namespace std;

LexItem currentToken;

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

    return LexItem();
}

LexItem getNextToken(istream& in, int& linenum){
    enum TokState { START, INID, INSTRING, ININT, INREAL, INCOMMENT}lexstate = START;
    string lexeme;
    char ch;
    while(in.get(ch)) {
        switch(lexstate){
        case START:
            if( ch == '\n' ){
                linenum++;
            }

            if( isspace(ch)){
                continue;
            }
            lexeme = ch;

            if(ch == '/' && char(in.peek()) == '*'){
                lexstate = INCOMMENT;
                lexeme += in.get(ch);
                continue;
            }
            if(ch == '+' ){
                currentToken = LexItem(PLUS, lexeme, linenum);
                return currentToken;
            } 
            if(ch =='-'){
                currentToken = LexItem(MINUS, lexeme, linenum);
                return currentToken;
            }
            if(ch =='*'){
                currentToken = LexItem(MULT, lexeme, linenum);
                return currentToken;
            }
            if(ch =='/'){
                currentToken = LexItem(DIV, lexeme, linenum);
                return currentToken;
            }
            if(ch =='=' && char(in.peek()) == '='){
                currentToken = LexItem(EQUAL, lexeme, linenum);
                return currentToken;
            }
            if(ch =='='){
                currentToken = LexItem(ASSOP, lexeme, linenum);
                return currentToken;
            }
            if(ch =='('){
                currentToken = LexItem(LPAREN, lexeme, linenum);
                return currentToken;
            }
            if(ch ==')'){
                currentToken = LexItem(RPAREN, lexeme, linenum);
                return currentToken;
            }
            if(ch =='>'){
                currentToken = LexItem(GTHAN, lexeme, linenum);
                return currentToken;
            }
            if(ch =='<'){
                currentToken = LexItem(LTHAN, lexeme, linenum);
                return currentToken;
            }
            if(ch =='&' && char(in.peek()) == '&'){
                currentToken = LexItem(AND, lexeme, linenum);
                return currentToken;
            }
            if(ch =='|' && char(in.peek()) == '|'){
                currentToken = LexItem(OR, lexeme, linenum);
                return currentToken;
            }
            if(ch =='!'){
                currentToken = LexItem(NOT, lexeme, linenum);
                return currentToken;
            }
            if(ch ==';'){
                currentToken = LexItem(SEMICOL, lexeme, linenum);
                return currentToken;
            }
            if(ch ==','){
                currentToken = LexItem(COMMA, lexeme, linenum);
                return currentToken;
            }

            if (ch == '\"'){
                lexstate = INSTRING;
                continue;
            }
            if (isdigit(ch)){
                lexstate = ININT;
                continue;
            }
            if(ch == '.'){
                lexstate=INREAL;
                continue;
            }
            if(isalpha(ch)){
                lexstate = INID;
                continue;
            }
            return LexItem(ERR, lexeme, linenum);
        
        case INID:
            if(regex_match(lexeme + ch, regex("[a-zA-Z][a-zA-Z0-9]*"))){
                lexeme += ch;
            }
            if (in.peek() == -1 || !regex_match(lexeme + ch, regex("[a-zA-Z][a-zA-Z0-9]*"))) {
                lexstate = START;
                in.putback(ch);
                if(lexeme=="PROGRAM"){
                    currentToken = LexItem(PROGRAM, lexeme, linenum);
                }else if (lexeme == "print"){
                    currentToken = LexItem(PRINT, lexeme, linenum);
                }else if (lexeme == "end"){
                    currentToken = LexItem(END, lexeme, linenum);
                }else if (lexeme == "if"){
                    currentToken = LexItem(IF, lexeme, linenum);
                }else if (lexeme == "then"){
                    currentToken = LexItem(THEN, lexeme, linenum);
                }else if (lexeme == "float"){
                    currentToken = LexItem(FLOAT, lexeme, linenum);
                }else if (lexeme == "int"){
                    currentToken = LexItem(INT, lexeme, linenum);
                }else if (lexeme == "bool"){
                    currentToken = LexItem(BOOL, lexeme, linenum);
                }else if (lexeme == "else"){
                    currentToken = LexItem(ELSE, lexeme, linenum);
                }else if (lexeme == "true"){
                    currentToken = LexItem(TRUE, lexeme, linenum);
                }else if (lexeme == "false"){
                    currentToken = LexItem(FALSE, lexeme, linenum);
                }else {
                    currentToken = LexItem(IDENT, lexeme, linenum);
                }
                return currentToken;
            }
        break;
        case INSTRING: 
            if (ch == 10){
                return LexItem(ERR, lexeme, linenum);
            }

            if (regex_match(lexeme + ch, regex("\"[ -~]*")))
            {
                if (ch == '\\' && in.peek() == '\"')
                {
                    lexeme += ch;
                    in.get(ch);
                    lexeme += ch;
                    continue;
                }else{
                    lexeme += ch;
                }
            }
    
            if (regex_match(lexeme + ch, regex("\"[ -~]*\"")))
            {

                lexstate = START;

                currentToken = LexItem(SCONST, lexeme, linenum);

                

                return currentToken;
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
                currentToken = LexItem(ICONST, lexeme, linenum);
                return currentToken;
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

                currentToken = LexItem(RCONST, lexeme, linenum);


                return currentToken;
            }
            break;
        case INCOMMENT:
            if (ch == '\n'){
                linenum++;
            }
            if(ch == '*' && in.peek() == '/'){
                lexstate = START;
            }
            continue;
        }
    }
    return currentToken;
}