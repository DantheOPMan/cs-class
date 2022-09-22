#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <iomanip>
#include<algorithm>

using namespace std;

int main() {
   
   string fileName;
   ifstream file;
   string line;
   
   int lineCount = 0;
   int commentedLineCount = 0;
   int validCommandLineCount = 0;
   int invalidCommandLineCount = 0;
   int runCount = 0;
   int printCount = 0;
   int copyCount = 0;
   int deleteCount = 0;

   cout << "Enter the name of a file to read from:" << endl;
   cin >> fileName;
   cout << endl;

   file.open(fileName.c_str());
   if(file){
      while(getline(file, line)){
         lineCount++;
         line.erase(std::remove_if(line.begin(), line.end(), ::isspace), line.end());
         
         if(line == ""){

         }else{
            if(line.substr(0,1) == "%"){
               commentedLineCount++;
            }else{
               if(line.find("run") == string::npos && line.find("print") == string::npos && line.find("copy") == string::npos && line.find("delete") == string::npos){
                  invalidCommandLineCount++;
                  cout << "Error: Unrecognizable command in line " << lineCount << endl;
                  cout << endl;
               }else{
                  validCommandLineCount++;
                  if(line.substr(0,3) == "run"){
                     runCount++;
                  }
                  if(line.substr(0,5) == "print"){
                     printCount++;
                  }
                  if(line.substr(0,4) == "copy"){
                     copyCount++;
                  }
                  if(line.substr(0,6) == "delete"){
                     deleteCount++;
                  }
               }
            }
            
         }
      }

      cout << "Total lines: " << lineCount <<endl;
      cout << "Commented lines: " << commentedLineCount << endl;
      cout << "Valid Command lines: " << validCommandLineCount << endl;
      cout << "Invalid Command lines: " << invalidCommandLineCount << endl;
      cout << "Run commands: " << runCount << endl;
      cout << "Print commands: " << printCount << endl;
      cout << "Copy commands: " << copyCount << endl;
      cout << "Delete commands: " << deleteCount << endl;

      file.close();

   }else{
      cout << "File cannot be opened " << fileName<< endl;
   }

   return 0;
}