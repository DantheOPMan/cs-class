#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include "lex.h"
//#include "ra5.cpp"

/*
 * CS280 - Fall 2022
*/

#include <cctype>
#include <map>
using std::map;

using namespace std;

int main(int argc, char *argv[])
{
	LexItem	tok;
	LexItem kwtok;
	ifstream  file ;
	
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
	
    map<Token,string> tokenPrint = {
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

	map <string, Token> tokString = {
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
	
	bool idsflag = false;
	bool tokflag = false;
	int linenum, strlen;
	string str1, str2;
	
	if (argc == 1)
	{
		cerr << "No Specified arguments." << endl;
		return 0;
	}
	for( int i=1; i<argc; i++ ) {
		string arg( argv[i] );
		if( arg == "-idsonly" ){
			idsflag = true;
			file.open("idsonly");
			if( file.is_open() == false ) {
				cerr << "CANNOT OPEN the File " << "idsonly.txt" << endl;
				return 0;
			}
		}
			
		else if( arg == "-alltok" ){
			tokflag = true;
			file.open("lexitems");
			if( file.is_open() == false ) {
				cerr << "CANNOT OPEN the File " << "lexitems.txt" << endl;
				return 0;
			}
		}
			
		else if( arg[0] == '-' ) {
			cerr << "UNRECOGNIZED FLAG " << arg << endl;
			return 0;
		}
		
	}
	
	if(idsflag)
    {
    	cout << "Identifiers and Keywords:" << endl;
    	file >> str1 >> linenum;
	}
	
	if(tokflag)
    {
    	cout << "All tokens:" << endl;
    	file >> str1 ;
    	//cout << str1 << " " << str2 << " " << linenum << endl;
	}
	
	
	while (!file.eof())
	{
		if(idsflag )
		{
			LexItem kwtok;
			kwtok = id_or_kw(str1, linenum);
			auto kIt = kwmap.find(kwtok.GetLexeme());
			if( kIt != kwmap.end() )
			{
			Token tt = kIt->second;
			cout << "KEYWORD: " << tokenPrint[tt] << " at Line # " << linenum;
			}
			else
			{
				cout << "IDENT: " << kwtok.GetLexeme() << " at Line # " << linenum;
			}
			cout << endl;
			file >> str1 >> linenum;	
		}
		else if (tokflag)
		{
			Token tok = tokString[str1];
			if( tok == SCONST)
			{
				file >> strlen;
				str2 = "";
				for (int i = 0; i < strlen; i++)
				{
					str2 += file.get();
				}
				file >> linenum;
			}
			else
			{
				
				file >> str2 >> linenum;
			}
			LexItem item{tok, str2, linenum};
			cout << item;
			file >> str1 ;
		}
	}
    	
    return 0;
}
