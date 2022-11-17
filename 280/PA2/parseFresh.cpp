/* Implementation of Recursive-Descent Parser
 * parse.cpp
 * Programming Assignment 2
 * Fall 2022
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

bool IdentList(istream& in, int& line);

//Prog ::= PROGRAM IDENT StmtList END PROGRAM
bool Prog(istream& in, int& line){
    bool status = true;
    LexItem t = Parser::GetNextToken(in, line);
    // check if begins with program and ident
    if (t.GetToken() != PROGRAM)
    {
        if (t.GetToken() == DONE)
        {
            ParseError(line, "Empty File");
            return false;
        }
        Parser::PushBackToken(t);
        ParseError(line, "Missing PROGRAM");
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

//StmtList ::= Stmt; { Stmt; }
bool StmtList(istream& in, int& line){
    bool status = Stmt(in, line);
    
    if (!status)
    {
        ParseError(line, "Invalid Statement List");
        return false;
    }
    LexItem t = Parser::GetNextToken(in, line);
    
    if(t.GetToken() == PROGRAM){
        ParseError(line, "Syntactic error in Program Body.");
        return false;
    }
    if (t.GetToken() == END)
    {
        Parser::PushBackToken(t);
        return status;
    }
    if (t.GetToken() != SEMICOL && t.GetToken() != ELSE)
    {
        if (t.GetToken() == PROGRAM)
        {
            ParseError(line, "Missing semicolon at end of Program Statement.");
            return false;
        }
        ParseError(line, "Missing a semicolon.");
        return false;
    }
    status = StmtList(in, line);
    return status;
}

//Stmt ::= DeclStmt | ControlStmt
bool Stmt(istream& in, int& line){
    bool status = true;
    LexItem t = Parser::GetNextToken(in, line);
    switch (t.GetToken())
    {
    case INT:
    case FLOAT:
    case BOOL:
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
            ParseError(line, "Incorrect control Statement");
            return status;
        }
        break;
    default:
        Parser::PushBackToken(t);
    }
    return status;
}

//DeclStmt ::= ( INT | FLOAT | BOOL ) VarList
bool DeclStmt(istream& in, int& line){
    bool status = false;
    LexItem t = Parser::GetNextToken(in, line);
    if (t == INT || t == FLOAT || t==BOOL)
    {
        status = VarList(in, line);
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
bool VarList(istream& in, int& line){
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
    defVar[t.GetLexeme()] = true;
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


//PrintStmt:= PRINT (ExpreList) 
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
		ParseError(line, "Missing THEN for If-Stmt Then-Part");
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
        if (!status)
        {
            ParseError(line, "Incorrect Statement in program");
            return false;
        }
        t = Parser::GetNextToken(in, line);
	}
	if(t.GetToken() != END){
		ParseError(line, "Missing END to end if");
        Parser::PushBackToken(t);
        return false;
	}
    t = Parser::GetNextToken(in,line);
    if(t.GetToken() != IF){
        ParseError(line, "Missing IF to end if");
        Parser::PushBackToken(t);
        return false;
    }
    return status;
}

//AssignStmt ::= Var = Expr
bool AssignStmt(istream& in, int& line){
    bool status = Var(in, line);
    if(!status){
        ParseError(line, "Missing Left-Hand Side Variable in Assignment statement");
        return false;
    }
    LexItem t = Parser::GetNextToken(in, line);
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

//Var ::= IDENT
bool Var(istream& in, int& line){
    LexItem t = Parser::GetNextToken(in, line);
    if (t.GetToken() == IDENT && defVar.find(t.GetLexeme()) != defVar.end())
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
	
	LexItem tok = Parser::GetNextToken(in, line);
	
	if (tok == COMMA) {
		status = ExprList(in, line);
        
	}
	else if(tok.GetToken() == ERR){
		ParseError(line, "Unrecognized Input Pattern");
		cout << "(" << tok.GetLexeme() << ")" << endl;
		return false;
	}
	else{
		Parser::PushBackToken(tok);
		return true;
	}
	return status;
}//End of ExprList

//Expr ::= LogORExpr ::= LogANDExpr { || LogANDRxpr }
bool Expr(istream& in, int& line){
    bool status = LogANDExpr(in, line);
    if (!status)
    {
        ParseError(line, "Expression error");
        return false;
    }
	LexItem t = Parser::GetNextToken(in, line);
	if(t.GetToken() == OR){
        
		status = LogANDExpr(in, line);
    	if (!status)
    	{
        	ParseError(line, "AND error");
        	return false;
    	}
	}else{
        Parser::PushBackToken(t);
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
        status = EqualExpr(in, line);
        if (!status)
        {
            ParseError(line, "Logic Expression error with And");
        }
        return status;
    }
    else 
    {
        Parser::PushBackToken(t);
        //ParseError(line, "invalid operator Error");
        //return false;
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
        status = RelExpr(in, line);
        if (!status)
        {
            ParseError(line, "Logic Expression error 1");
        }
        return status;
    }
    else
    {
        Parser::PushBackToken(t);
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
        status = AddExpr(in, line);
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

