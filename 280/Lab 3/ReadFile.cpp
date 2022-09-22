#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <iomanip>
#include<algorithm>
#include <ctype.h>
#include <cstring>
#include<array> 
#include <vector>



using namespace std;

int main() {
    string fileName;
    ifstream file;
    string line;

    int lineCount = 0;
    int nonBlankLinesCount = 0;
    int wordCount = 0;
    int integerCount = 0;
    int nameCount = 0;

    cout << "Enter the name of a file to read from:" << endl;
    cin >> fileName;
    cout << endl;
    file.open(fileName.c_str());
    if(file){
        while(getline(file, line)){
            lineCount++;
            string noWhitespace = line;
            noWhitespace.erase(std::remove_if(noWhitespace.begin(), noWhitespace.end(), ::isspace), noWhitespace.end());
            if(noWhitespace != ""){
                nonBlankLinesCount++;
                vector<string> words;
                for(int i =0; i < line.length(); i++){
                    if(i + 1 == line.length()){
                        words.push_back(line.substr(0,i+1));
                        break;
                    }else if(line.substr(i,i+1)==" "){
                        words.push_back(line.substr(0,i+1));
                        line = line.substr(i+1, line.length());
                        i = 0;
                    }
                }   
                
                for(int i =0; i < sizeof(words);i++){
                    wordCount++;
                    char splitWord[words[i].length()];
                    strcpy(splitWord, words[i].c_str());
                    if(isalpha(splitWord[0]) || splitWord[0] == '_'){
                        for(int j =1; j < sizeof(splitWord); j++){
                            if(!isalnum(splitWord[j]) || (splitWord[j] != '_') || splitWord[j] != '@'){
                                break;
                            }else{
                                nameCount++;
                            }
                        }
                    }
                    if(isdigit(splitWord[0]) || splitWord[0] == '-' || splitWord[0] == '+'){
                        for(int j =1; j < sizeof(splitWord); j++){
                            if(!isdigit(splitWord[j])){
                                break;
                            }else{
                                integerCount++;
                            }
                        }
                    }
                }
            }
        }
        cout << "Total Number of Lines: " << lineCount <<endl;
        cout << "Number of non-blank lines: " << nonBlankLinesCount << endl;
        cout << "Number of Words: " << wordCount << endl;
        cout << "Number of Integers: " << integerCount << endl;
        cout << "Number of Names: " << nameCount << endl;

        file.close();
    }else{
      cout << "File cannot be opened " << fileName<< endl;
    }

    return 0;
}