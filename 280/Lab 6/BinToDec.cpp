#include <string>
#include <cmath>

using namespace std;

int BinToDec(string binNum){
    if(binNum.length() == 1){
        return stoi(binNum.substr(0,1));
    }
    return pow(2, binNum.length()-1) * stoi(binNum.substr(0,1)) + BinToDec(binNum.substr(1, binNum.length() -1));
}