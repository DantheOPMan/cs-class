#include <iostream>
#include <regex>
#include <map>
#include "lex.h"
using namespace std;

static map<Token, string> tokenPrint{

    {PRINT, "PRINT"}, {IF, "IF"},
    {BEGIN, "BEGIN"},
    {END, "END"},

    {THEN, "THEN"},
    {IDENT, "IDENT"},

    {ICONST, "ICONST"},
    {SCONST, "SCONST"},

    {RCONST, "RCONST"},
    {PLUS, "PLUS"},

    {MINUS, "MINUS"},
    {MULT, "MULT"},

    {DIV, "DIV"},
    {EQ, "EQ"},

    {LPAREN, "LPAREN"},
    {RPAREN, "RPAREN"},

    {SCOMA, "SCOMA"},
    {COMA, "COMA"},

    {ERR, "ERR"},
    {DONE, "DONE"}

};

ostream &operator<<(ostream &out, const LexItem &tok)
{

    string *token = &tokenPrint[tok.GetToken()];
    cout << *token;
    bool eval = (tok.GetToken() == SCONST) || (tok.GetToken() == RCONST) || (tok.GetToken() == ICONST) || (tok.GetToken() == IDENT) || (tok.GetToken() == ERR);
    if (eval)

        cout << " (" << tok.GetLexeme() << ")";

    return out;
}

LexItem currentToken;

LexItem previousToken;


LexItem getNextToken(istream &in, int &linenum)
{
    enum TokenState
    {
        START,
        INID,
        INSTRING,
        ININT,
        INREAL,
        INCOMMENT,
        SIGN
    } lexstate = START;

    string lexeme;

    char character;

    char nextCharacter;

    // Search until a token is found or eof is reached.

    while (in.get(character))
    {

        switch (lexstate)
        {

            // Basic state of searching for a token

        case START:

            if (character == '\n')

                linenum++;

            // If eof is found finish searching

            if (in.peek() == -1)
            {

                if (previousToken.GetToken() != END)

                    return LexItem(ERR, "No END Token", previousToken.GetLinenum());

                return LexItem(DONE, lexeme, linenum);
            }

            // Spaces are meaningless for token analysis and are skipped

            if (isspace(character))

                continue;

            lexeme = character;

            // Check for comment with //

            if (character == '/' && char(in.peek()) == '/')
            {

                lexstate = INCOMMENT;

                continue;
            }

            // Check for signs

            if (character == '+' || character == '-' || character == '*' ||

                character == '/' || character == '(' || character == ')' ||

                character == '=' || character == ',' || character == ';')
            {

                lexstate = SIGN;

                continue;
            }

            // Check for string

            if (character == '\"')
            {

                lexstate = INSTRING;

                continue;
            }

            // Check for ints

            if (isdigit(character))
            {

                lexstate = ININT;

                continue;
            }

            // Check for reals

            if (character == '.')
            {

                lexstate = INREAL;

                continue;
            }

            // Check for identifiers

            if (isalpha(character))
            {

                lexstate = INID;

                continue;
            }

            // If a character cannot be classified into a state it must be an error

            return LexItem(ERR, lexeme, linenum);

        case INID:

            // Regex is used to match strings to proper formatting

            if (regex_match(lexeme + character, regex("[a-zA-Z][a-zA-Z0-9]*")))

                lexeme += character;

            if (in.peek() == -1 || !regex_match(lexeme + character, regex("[a-zA-Z][a-zA-Z0-9]*"))) {

                lexstate = START;

                in.putback(character);

                // Check for reserved keywords as identifiers

                if (lexeme == "begin") {

                    if (previousToken.GetToken() != ERR)

                        return LexItem(ERR, lexeme, linenum);

                    currentToken = LexItem(BEGIN, lexeme, linenum);

                }

                else if (lexeme == "print")

                    currentToken = LexItem(PRINT, lexeme, linenum);

                else if (lexeme == "end") {

                    if (previousToken.GetToken() != SCOMA)

                        return LexItem(ERR, previousToken.GetLexeme(), linenum);

                    currentToken = LexItem(END, lexeme, linenum);

                }

                else if (lexeme == "if")

                    currentToken = LexItem(IF, lexeme, linenum);

                else if (lexeme == "then")

                    currentToken = LexItem(THEN, lexeme, linenum);

                else {

                    if (previousToken.GetToken() == IDENT)

                        return LexItem(ERR, lexeme, linenum);

                    currentToken = LexItem(IDENT, lexeme, linenum);

                }

                // Check for no begin token

                if (currentToken != BEGIN && previousToken == ERR)

                    return LexItem(ERR, "No BEGIN Token", currentToken.GetLinenum());

                previousToken = currentToken;

                return currentToken;

            }

        break;

            case INSTRING:

            // Check for no begin token

            if (previousToken == ERR)

                return LexItem(ERR, "No Begin Token", linenum);

            // String cannot contain multiple lines, must be an error

            if (character == 10)

                return LexItem(ERR, lexeme, linenum);

            // Check lexeme for unfished string

            if (regex_match(lexeme + character, regex("\"[ -~]*")))
            {

                if (character == '\\' && in.peek() == '\"')
                {

                    lexeme += character;

                    in.get(character);

                    lexeme += character;

                    continue;
                }

                else

                    lexeme += character;
            }

            // Check lexeme for finished string

            if (regex_match(lexeme + character, regex("\"[ -~]*\"")))
            {

                lexstate = START;

                currentToken = LexItem(SCONST, lexeme, linenum);

                previousToken = currentToken;

                return currentToken;
            }

            break;

        case ININT:

            // Check for no begin token

            if (previousToken == ERR)

                return LexItem(ERR, "No Begin Token", linenum);

            // Checks if an alpha character is next to an integer number

            if (isalpha(character))

                return LexItem(ERR, lexeme + character, linenum);

            if (regex_match(lexeme + character, regex("[0-9]+")))
            {

                lexeme += character;
            }

            // If a period is found then the int is actual a real number

            else if (character == '.')
            {

                lexstate = INREAL;

                in.putback(character);

                continue;
            }

            else
            {

                lexstate = START;

                in.putback(character);

                currentToken = LexItem(ICONST, lexeme, linenum);

                previousToken = currentToken;

                return currentToken;
            }

            break;

        case INREAL:

            // Check for no begin token

            if (previousToken == ERR)

                return LexItem(ERR, "No Begin Token", linenum);

            // Checks if an alpha character is next to a real number

            if (isalpha(character))

                return LexItem(ERR, lexeme + character, linenum);

            if (regex_match(lexeme + character, regex("[0-9]*\\.[0-9]+")))
            {

                lexeme += character;
            }

            else if (regex_match(lexeme + character, regex("[0-9]*\\.[0-9]*")))
            {

                lexeme += character;
            }

            else
            {

                if (lexeme[lexeme.length() - 1] == '.')

                    return LexItem(ERR, lexeme, linenum);

                lexstate = START;

                in.putback(character);

                currentToken = LexItem(RCONST, lexeme, linenum);

                previousToken = currentToken;

                return currentToken;
            }

            break;

        case INCOMMENT:

            // Because comment is not a token it can be ignored

            if (character == '\n')
            {

                linenum++;

                lexstate = START;
            }

            continue;

        case SIGN:

            // Check for no begin token

            if (previousToken == ERR)

                return LexItem(ERR, "No Begin Token", linenum);

            /**



            * Signs are a little more complex and have to be handled individually

            * for the most part. Each sign can have a differnet type of token

            * in front of it requiring differnt checks.

            */

            if (lexeme == "+" || lexeme == "*" || lexeme == "/")
            {

                Token token = previousToken.GetToken();

                if (token == IDENT || token == ICONST || token == RCONST)
                {

                    lexstate = START;

                    in.putback(character);

                    if (lexeme == "+")
                        
                        currentToken = LexItem(PLUS, lexeme, linenum);

                    else if (lexeme == "*")

                        currentToken = LexItem(MULT, lexeme, linenum);

                    else

                        currentToken = LexItem(DIV, lexeme, linenum);

                    previousToken = currentToken;

                    return currentToken;
                }

                else

                    return LexItem(ERR, lexeme + character, linenum);
            }

            if (lexeme == "-")
            {

                Token token = previousToken.GetToken();

                if (token == IDENT || token == ICONST || token == RCONST || token == EQ)
                {

                    lexstate = START;

                    in.putback(character);

                    currentToken = LexItem(MINUS, lexeme, linenum);

                    previousToken = currentToken;

                    return currentToken;
                }

                else

                    return LexItem(ERR, lexeme + character, linenum);
            }

            if (lexeme == "(")
            {

                Token token = previousToken.GetToken();

                if (token == IF || token == EQ || token == PLUS || token == MINUS ||

                    token == MULT || token == DIV)
                {

                    lexstate = START;

                    in.putback(character);

                    currentToken = LexItem(LPAREN, lexeme, linenum);

                    previousToken = currentToken;

                    return currentToken;
                }

                else

                    return LexItem(ERR, lexeme + character, linenum);
            }

            if (lexeme == ")")
            {

                Token token = previousToken.GetToken();

                if (token == ICONST || token == RCONST || token == IDENT)
                {

                    lexstate = START;

                    in.putback(character);

                    currentToken = LexItem(RPAREN, lexeme, linenum);

                    previousToken = currentToken;

                    return currentToken;
                }

                else

                    return LexItem(ERR, lexeme + character, linenum);
            }

            if (lexeme == "=")
            {

                Token token = previousToken.GetToken();

                if (token == IDENT)
                {

                    lexstate = START;

                    in.putback(character);

                    currentToken = LexItem(EQ, lexeme, linenum);

                    previousToken = currentToken;

                    return currentToken;
                }

                else

                    return LexItem(ERR, lexeme + character, linenum);
            }

            if (lexeme == ",")
            {

                Token token = previousToken.GetToken();

                if (token == SCONST)
                {

                    lexstate = START;

                    in.putback(character);

                    currentToken = LexItem(COMA, lexeme, linenum);

                    previousToken = currentToken;

                    return currentToken;
                }

                else

                    return LexItem(ERR, lexeme + character, linenum);
            }

            if (lexeme == ";")
            {

                Token token = previousToken.GetToken();

                if (token == SCONST || token == ICONST || token == RCONST || token == IDENT)
                {

                    lexstate = START;

                    in.putback(character);

                    currentToken = LexItem(SCOMA, lexeme, linenum);

                    previousToken = currentToken;

                    return currentToken;
                }

                else

                    return LexItem(ERR, lexeme + character, linenum);
            }

            break;
        }
    }

    return LexItem(DONE, "", linenum);
}
