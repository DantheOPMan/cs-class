#include <iostream>
#include <fstream>
#include <cstdlib> 
#include <iomanip>


using namespace std;

int main() {
   
   int character; 
   string fileName;
   ifstream file;
   string line;
    
   cout << "Enter the name of the file to read from:" << endl;
   cin >> fileName;

   file.open(fileName.c_str());
   if(file){
      while(getline(file, line)){
         cout << line << endl;
          
      }

      file.close();
   }else{
      cout << "File cannot be found"<< endl;
   }

   return 0;
   

}