#include <iostream>
#include <fstream>
#include <cstdlib> 

using namespace std;

int main() {
   int character; 
   string fileName;
   ifstream file;
   string data;
    
   cout << "Enter the name of the file to read from:" << endl;
   fileName = cin.get();
   
   file.open(fileName);
   data = file.getline(0);

   cout << data << endl;

}