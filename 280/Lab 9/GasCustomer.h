#ifndef GASCUSTOMER_H
#define GASCUSTOMER_H

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <iomanip>

using namespace std;


class GasCustomer : public UtilityCustomer{

public:
    
    double const gasPrice = 3.75;
    double usage;
    GasCustomer() {
        usage = 0.0;
    }
    GasCustomer( double usageInput, int num) : UtilityCustomer(num){
        usage = usageInput;
    }
    double calculateBill(){
        return gasPrice * usage;
    }
    double getUsage(){
        return usage;
    }
    void setUsage(double n){
        usage = n;
    }
    void Display(){
        cout << "Gas Utility Customer" << endl;
        cout << "Utility Customer Account Number: " <<  accNum << endl;
        cout << "Gas Used (in cubic meters): " << usage << endl;
        cout << "total Charge: " << calculateBill() << endl;
    }
};


#endif
