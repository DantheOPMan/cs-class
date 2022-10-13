#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include "lex.cpp"

using namespace std;

int main(int argc, char **argv)
{

    LexItem token;

    ifstream file;

    file.open(argv[0]);

    vector<LexItem> tokens;

    int lineNumber = 0;

    int tokenCount = 0;

    if (file.is_open()){
        
    }
}