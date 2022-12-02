#ifndef UTILITYCUSTOMER_H
#define UTILITYCUSTOMER_H

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <iomanip>

using namespace std;


class UtilityCustomer{
    

public:
    int accNum;
    UtilityCustomer(){
        accNum = -1;
    }
    UtilityCustomer(int num){
        accNum = num;
    }
    virtual double calculateBill() = 0;

    int getAccount(){
        return accNum;
    }
    void setAccount(int n){
        accNum = n;
    }
    virtual void Display(){
        cout << "Utility Customer Account Number: " <<  accNum << endl;
    }
    bool operator==(UtilityCustomer * UtilityObj) const{
        return UtilityObj->accNum == accNum;
    }; 
};


#endif
