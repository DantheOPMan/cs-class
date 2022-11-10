#include <iostream>
#include <fstream>
#include <stack>
#include <string>
using namespace std;
bool BalancedDelimiters(string & inputString);

int main(int argc, char *argv [])
    {
    string sentence;
    bool balancedDelimiters;
    ifstream file;
    if(argc >= 2 ) {
        file.open(argv[1]);
        if( !file) 
        {
        /* error */ 
            cerr << "File cannot be opened: " << argv[1] << endl;
            exit (1);
        }
    }
    else
    {
        cerr << "No file is found" << endl;
        exit (1);
    } 
    getline(file, sentence);
    if(sentence.length() == 0)
    {
        cout << "File is empty." << endl;
        return 0;
    }
    balancedDelimiters = BalancedDelimiters(sentence);
    if (balancedDelimiters)
        cout << "\"" << sentence << "\"" << " contains balanced delimiters." << endl;
    else
        cout << "\"" << sentence << "\"" << " does not contain balanced delimiters." << endl; 
}
