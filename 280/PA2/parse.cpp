/* Implementation of Recursive-Descent Parser
 * parse.cpp
 * Programming Assignment 2
 * Spring 2022
*/

#include "parse.h"

map<string, bool> defVar;

namespace Parser {
	bool pushed_back = false;
	LexItem	pushed_token;

	static LexItem GetNextToken(istream& in, int& line) {
		if( pushed_back ) {
			pushed_back = false;
			return pushed_token;
		}
		return getNextToken(in, line);
	}

	static void PushBackToken(LexItem & t) {
		if( pushed_back ) {
			abort();
		}
		pushed_back = true;
		pushed_token = t;	
	}

}

static int error_count = 0;

int ErrCount()
{
    return error_count;
}

void ParseError(int line, string msg)
{
	++error_count;
	cout << line << ": " << msg << endl;
}


//Prog ::= PROGRAM IDENT StmtList END PROGRAM
bool Prog(istream& in, int& line){
	bool status = true;
    LexItem t = Parser::GetNextToken(in, line);
    // check if begins with program and ident
    if (t.GetToken() != PROGRAM)
    {
        // Parser::PushBackToken(t);
        if (t.GetToken() == DONE)
        {
            ParseError(line, "Empty File");
            return false;
        }
        Parser::PushBackToken(t);
        ParseError(line, "Missing PROGRAM.");
        return false;
    }
    t = Parser::GetNextToken(in, line);
    if (t.GetToken() != IDENT)
    {
        Parser::PushBackToken(t);
        ParseError(line, "Missing Program Name.");
        return false;
    }
    status = StmtList(in, line);
    if (!status)
    {
        ParseError(line, "Incorrect Program Body.");
        return false;
    }
    t = Parser::GetNextToken(in, line);
    if (t.GetToken() != END)
    {
        Parser::PushBackToken(t);
        ParseError(line, "Missing END at end of program.");
        return false;
    }
    t = Parser::GetNextToken(in, line);
    if (t.GetToken() != PROGRAM)
    {
        Parser::PushBackToken(t);
        ParseError(line, "Missing PROGRAM at the End");
        return false;
    }
    return status;
}

// StmtList ::= Stmt; {Stmt;}
bool StmtList(istream& in, int& line){
	bool status = Stmt(in, line);
    if (!status)
    {
        ParseError(line, "Invalid Statement List");
        return false;
    }
    LexItem t = Parser::GetNextToken(in, line);
    if (t.GetToken() == END)
    {
        Parser::PushBackToken(t);
        return status;
    }
    if (t.GetToken() != SEMICOL)
    {
        if (t.GetToken() == PROGRAM)
        {
            ParseError(line, "Missing semicolon at end of Statement.");
            return false;
        }
        ParseError(line, "Missing a semicolon.");
        return false;
    }
    status = StmtList(in, line);
    return status;
}

//DeclStmt ::= ( INT | FLOAT | BOOL ) VarList
bool DeclStmt(istream& in, int& line){
	bool status = false;
    // cout << "in Decl" << endl;
    LexItem t = Parser::GetNextToken(in, line);
    if (t == INT || t == FLOAT || t==BOOL)
    {
        status = VarList(in, line);
        // cout<< "returning from IdentList" << " " << (status? 1: 0) << endl;
        if (!status)
        {
            ParseError(line, "Incorrect variable in Declaration Statement.");
            return status;
        }
    }
    else
    {
        Parser::PushBackToken(t);
        ParseError(line, "Incorrect Type.");
        return false;
    }
    return true;
}

//VarList ::= Var { ,Var } 
bool VarList(istream &in, int &line)
{
    bool status = true;
    LexItem t = Parser::GetNextToken(in, line);
    if (t.GetToken() != IDENT)
    {
        ParseError(line, "Invalid Identifier List");
        return false;
    }
    if (defVar.find(t.GetLexeme()) != defVar.end())
    {// if variable already in map
        ParseError(line, "Variable Redefinition");
        return false;
    }
    defVar[t.GetLexeme()] = true; // add to map
    t = Parser::GetNextToken(in, line);
    if (t.GetToken() == COMMA)
    {
        status = VarList(in, line);
    }
    else
    {
        Parser::PushBackToken(t);
    }
    return status;
}

//ControlStmt ::= AssigStmt | IfStmt | PrintStmt 
bool ControlStmt(istream& in, int& line) {
	bool status;
	
	LexItem t = Parser::GetNextToken(in, line);
	
	switch( t.GetToken() ) {

	case PRINT:
		status = PrintStmt(in, line);
		break;

	case IF:
		status = IfStmt(in, line);
		break;

	case IDENT:
		Parser::PushBackToken(t);
        status = AssignStmt(in, line);
		break;
		
	default:
		Parser::PushBackToken(t);
		return false;
	}

	return status;
}//End of ControlStmt

// Stmt ::= DeclStmt | ControlStmt
bool Stmt(istream& in, int& line){
	bool status = true;
    // cout << "in Stmt" << endl;
    LexItem t = Parser::GetNextToken(in, line);
    switch (t.GetToken())
    {
    case INT:
    case FLOAT:
        Parser::PushBackToken(t);
        status = DeclStmt(in, line);
        if (!status)
            {
                ParseError(line, "Incorrect Declaration Statement.");
                return status;
            }
        break;
    case IF:
    case PRINT:
    case IDENT:
        Parser::PushBackToken(t);
        status = ControlStmt(in, line);
        if (!status)
        {
            ParseError(line, "Incorrect control Statement.");
            return status;
        }
        break;
    default:
        Parser::PushBackToken(t);
    }
    return status;
}

//PrintStmt:= PRINT (ExprList) 
bool PrintStmt(istream& in, int& line) {
	LexItem t;
	
	t = Parser::GetNextToken(in, line);
	if( t != LPAREN ) {
		
		ParseError(line, "Missing Left Parenthesis");
		return false;
	}
	
	bool ex = ExprList(in, line);
	
	if( !ex ) {
		ParseError(line, "Missing expression list after Print");
		return false;
	}
	
	t = Parser::GetNextToken(in, line);
	if(t != RPAREN ) {
		
		ParseError(line, "Missing Right Parenthesis");
		return false;
	}
	return ex;
}//End of PrintStmt

//IfStmt ::= IF (Expr) THEN StmtList [ ELSE StmtList ] END IF 
bool IfStmt(istream& in, int& line){
	LexItem t = Parser::GetNextToken(in, line);
    bool status = false;
    if (t.GetToken() != IF)
    {
        ParseError(line, "missing IF");
        return false;
    }
    t = Parser::GetNextToken(in, line);
    if (t.GetToken() != LPAREN)
    {
        ParseError(line, "Missing left paren in IF");
        return false;
    }
    status = Expr(in, line);
    if (!status)
    {
        ParseError(line, "Missing Expression in If-Stmt Then-Part");
        return false;
    }
    t = Parser::GetNextToken(in, line);
    if (t.GetToken() != RPAREN)
    {
        ParseError(line, "Missing Right Parenthesis");
        return false;
    }
    t = Parser::GetNextToken(in, line);
	if(t.GetToken() != THEN){
		ParseError(line, "Missing Statement for If-Stmt Then-Part");
        return false;	
	}
    status = StmtList(in, line);
    if (!status)
    {
        ParseError(line, "Incorrect Statement in program");
        return false;
    }
	t = Parser::GetNextToken(in, line);
	if(t.GetToken() == ELSE){
		status = StmtList(in, line);
	}else{
		Parser::PushBackToken(t);
	}
	t = Parser::GetNextToken(in, line);
	if(t.GetToken() != END && (t = Parser::GetNextToken(in,line)).GetToken() != IF){
		ParseError(line, "Missing statement to end if");
        return false;
	}
    return status;
}
// AssignStmt ::= Var = Expr
bool AssignStmt(istream& in, int& line){
	bool status = Var(in, line);
    LexItem t = Parser::GetNextToken(in, line);
    // t = Parser::GetNextToken(in, line);
    if (t.GetToken() != ASSOP)
    {
        Parser::PushBackToken(t);
        ParseError(line, "Missing assignment op");
        return false;
    }
    status = Expr(in, line);
    if (!status)
    {
        Parser::PushBackToken(t);
        ParseError(line, "Invalid assignment var");
        return false;
    }
    return true;
}
// Var ::= IDENT
bool Var(istream& in, int& line){
	LexItem t = Parser::GetNextToken(in, line);
    if (t.GetToken() == IDENT)
    {
        return true;
    }
    else
    {
    	ParseError(line, "Incorrect Identifier Statement");
        return false;
    }
}

//ExprList:= Expr {,Expr}
bool ExprList(istream& in, int& line) {
	bool status = false;
	status = Expr(in, line);
	if(!status){
		ParseError(line, "Missing Expression");
		return false;
	}
	
	LexItem t = Parser::GetNextToken(in, line);
	
	if (t == COMMA) {
		status = ExprList(in, line);
	}
	else if(t.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << t.GetLexeme() << ")" << endl;
		return false;
	}
	else{
		Parser::PushBackToken(t);
		return true;
	}
	return status;
}//End of ExprList

//Expr ::= LogORExpr ::= LogANDExpr { || LogANDRxpr } 
bool Expr(istream &in, int &line)
{
	bool status;
	LexItem t = Parser::GetNextToken(in, line);
	if(t.GetToken() == OR){
		status = LogANDExpr(in, line);
	}else{
		status = LogANDExpr(in, line);
    	if (!status)
    	{
        	ParseError(line, "AND error");
        	return false;
    	}
    	LexItem t = Parser::GetNextToken(in, line);
    	if (t.GetToken() == OR)
    	{
       		status = LogANDExpr(in, line);
    	}
    	else
    	{
        	Parser::PushBackToken(t);
    	}
    
	}
    return status;
}

//LogANDExpr ::= EqualExpr { && EqualExpr } 
bool LogANDExpr(istream& in, int& line){
	bool status = EqualExpr(in, line);
    if (!status)
    {
        ParseError(line, "Logic expression error");
        return false;
    }
    LexItem t = Parser::GetNextToken(in, line);
    if (t.GetToken() == AND)
    {
        status = EqualExpr(in, line); //might have to put logandexpr
        if (!status)
        {
            ParseError(line, "Logic Expression error 1");
        }
        return status;
    }
    else
    {
        ParseError(line, "invalid operator Error");
        return false;
    }
    return status;
}

//EqualExpr ::= RelExpr  [== RelExpr ] 
bool EqualExpr(istream& in, int& line){
	bool status = RelExpr(in, line);
    if (!status)
    {
        ParseError(line, "Logic expression error");
        return false;
    }
    LexItem t = Parser::GetNextToken(in, line);
    if (t.GetToken() == EQUAL)
    {
        status = RelExpr(in, line); //might have to put equalexpr
        if (!status)
        {
            ParseError(line, "Logic Expression error 1");
        }
        return status;
    }
    else
    {
        ParseError(line, "invalid operator Error");
        return false;
    }
    return status;
}

//RelExpr ::= AddExpr  [ ( < | > ) AddExpr ] 
bool RelExpr(istream& in, int& line){
	bool status = AddExpr(in, line);
    if (!status)
    {
        ParseError(line, "Term Error 1");
        return false;
    }
    LexItem t = Parser::GetNextToken(in, line);
    if (t.GetToken() == GTHAN || t.GetToken() == LTHAN )
    {
        status = AddExpr(in, line); //might need to change to relexpr
    }
    else
    {
        Parser::PushBackToken(t);
    }
    return status;
}

//AddExpr :: MultExpr { ( + | - ) MultExpr }
bool AddExpr(istream& in, int& line){
	bool status = MultExpr(in, line);
    if (!status)
    {
        ParseError(line, "Expression error");
        return false;
    }
    LexItem t = Parser::GetNextToken(in, line);
    if (t.GetToken() == PLUS || t.GetToken() == MINUS)
    {
        status = MultExpr(in, line);
    }
    else
    {
        Parser::PushBackToken(t);
    }
    return status;
}

//MultExpr ::= UnaryExpr { ( * | / ) UnaryExpr } 
bool MultExpr(istream& in, int& line){
	bool status = UnaryExpr(in, line);
    if (!status)
    {
        ParseError(line, "Missing operand after operator");
        return false;
    }
    LexItem t = Parser::GetNextToken(in, line);
    if (t.GetToken() == MULT || t.GetToken() == DIV )
    {
        status = MultExpr(in, line); //might need to change to unaryexpr
    }
    else
    {
        Parser::PushBackToken(t);
    }
    return status;
}

//UnaryExpr ::= ( - | + | ! ) PrimaryExpr | PrimaryExpr
bool UnaryExpr(istream& in, int& line){
	LexItem t = Parser::GetNextToken(in, line);
    bool status = true;
    if (t.GetToken() == PLUS || t.GetToken() == MINUS || t.GetToken() == NOT)
    {
        status = PrimaryExpr(in, line, 1);
        if (!status)
        {
            ParseError(line, "Missing operand after operator");
            return false;
        }
    }
    else
    {
        Parser::PushBackToken(t);
        status = PrimaryExpr(in, line, 1);
        if (!status)
        {
            ParseError(line, "Missing operand after operator");
            return false;
        }
    }
    return status;
}

//PrimaryExpr ::= IDENT | ICONST | RCONST | SCONST | BCONST | ( Expr )
bool PrimaryExpr(istream& in, int& line, int sign){
    LexItem t = Parser::GetNextToken(in, line);
    bool status = true;
    if (t.GetToken() == IDENT)
    {
        if (defVar.count(t.GetLexeme()) == 0)
        {
            ParseError(line, "Undeclared variable");
        }
        return status;
    }
    else if (t.GetToken() == ICONST)
    {
        return status;
    }
    else if (t.GetToken() == RCONST)
    {
        return status;
    }
    else if (t.GetToken() == SCONST)
    {
        return status;
    }else if(t.GetToken() == BCONST)
    {
        return status;
    }
    if (t.GetToken() != LPAREN)
    {
        ParseError(line, "No left parenthesis");
        return false;
    }
    status = Expr(in, line);
    if (!status)
    {
        ParseError(line, "Factor error");
        return false;
    }
    t = Parser::GetNextToken(in, line);
    if (t.GetToken() != RPAREN)
    {
        ParseError(line, "No right parenthesis");
        return false;
    }
    return status;
}