#include <iostream>
#include <string>
using namespace std;
#include "BinToDec.cpp"

int BinToDec(string binNum);

int main()
{
	string binary;
	int result;
	//int max = -1;
	cout << "Enter any positive binary number: ";
	cin >> binary;
	result = BinToDec(binary);
	
	cout << "Result of Conversion: " << result << endl;
	return 0;
}
