#ifndef ELECTRICITYCUSTOMER_H
#define ELECTRICITYCUSTOMER_H

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <iomanip>

using namespace std;


class ElectricityCustomer : public UtilityCustomer{


public:
    double const kWattPrice = 0.25;
    double  kWattHourUsed;
    ElectricityCustomer(){
        kWattHourUsed = 0.0;
    }
    ElectricityCustomer(double kWattInput, int num) : UtilityCustomer(num){
        kWattHourUsed = kWattInput;
    }
    double calculateBill(){
        return kWattHourUsed * kWattPrice;
    }
    double getkWattHourUsed(){
        return kWattHourUsed;
    }
    void setkWattHourUsed(double n){
        kWattHourUsed = n;
    }
    void Display(){
        cout << "Electric Utility Customer" << endl;
        cout << "Utility Customer Account Number: " <<  accNum << endl;
        cout << "Electricity Used (in kWattHour): " << kWattHourUsed << endl;
        cout << "total Charge: " << calculateBill() << endl;
    }
};


#endif
