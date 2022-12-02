#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream> 

#include "UtilityCustomer.h"
#include  "GasCustomer.h"
#include  "ElectricityCustomer.h"

using namespace std;

int main(int argc, char *argv []) 
{
	ifstream file;
    vector< UtilityCustomer * > UtilityList;
    vector< UtilityCustomer * >::iterator listitr;
	UtilityCustomer *NewCustomer;
	vector< UtilityCustomer * > RejectedList;
	GasCustomer *gasCust;
	vector <GasCustomer *> InvGasList;
	vector <ElectricityCustomer *> InvElecList;
	ElectricityCustomer *elecCust;
	string strline;
	double usage, sumGas = 0, sumElec = 0, sumGasBills = 0, sumElecBills = 0;
	int accnum, type, account, countGas=0, countElec = 0;
		
	bool result=true , newcust=false, rejcust = false, invcust = false, avedata = false;
	
	
    if( argc >= 2 ) {
		
		file.open(argv[1]);
		if( !file) 
		{
			/* error */ 
			cerr << "File cannot be opened: " << argv[1] << endl;
			exit (1);
        }
		for( int i = 2; i<argc; i++ ) {
			string arg( argv[i] );
			if( arg == "-new" )
				newcust = true;
			else if( arg == "-rej" )
				rejcust = true;
			else if( arg == "-inv" )
				invcust = true;
			else if( arg == "-ave")
				avedata = true;
			else {
				cerr << "UNRECOGNIZED FLAG " << arg << endl;
				return 0;
			}		
		}
	}
	else
	{
		cerr << "No file is found." << endl;
		exit (1);
	}
 	
 	
   	while (file >> type >> accnum >> usage)
    {
    	if(type == 1 && accnum >= 0 && accnum <= 99999)
		{
    		/*"Gas Utility"*/
    		NewCustomer = new GasCustomer(usage, accnum);
    		
		}
		else if (type == 2 && accnum >= 100000 && accnum <= 199999)
		{
			NewCustomer = new ElectricityCustomer(usage, accnum);
			
		}
		else
		{
			if(type == 2)
			{
				elecCust = new ElectricityCustomer();
				elecCust->setkWattHourUsed(usage);
				elecCust->setAccount(accnum);
				InvElecList.push_back(elecCust);
				continue;
			}	
			if(type == 1)
			{
				gasCust = new GasCustomer();
				gasCust->setUsage(usage);
				gasCust->setAccount(accnum);
				InvGasList.push_back(gasCust);
				continue;
			}				
		}	
		
		for ( int i = 0; i < UtilityList.size(); i++ )
		{
			if((*UtilityList[i]) == (NewCustomer))
			{	
				result = false;
				break;
			}
		}
		
		if(result)
		{
			UtilityList.push_back(NewCustomer);
		}
		else
		{
			RejectedList.push_back(NewCustomer);
		}
		
	}
	
	if(newcust)
	{
		cout << "List of accepted customers records:" << endl <<endl;
    	for ( int i = 0; i < UtilityList.size(); i++ ) 
    	{
    		(*UtilityList[i]).Display();
                                                           
			cout << endl;                                
		}
	}
	
	if(rejcust)
	{	
		cout << "List of rejected customers records:" << endl << endl;
    	for ( int i = 0; i < RejectedList.size(); i++ ) 
    	{
    		(*RejectedList[i]).Display();
                                                           
			cout << endl;                                
		}
	}
	
	if(invcust)
	{
		cout << "List of invalid gas customers records:" << endl << endl;
    	for ( int i = 0; i < InvGasList.size(); i++ ) 
    	{
    		(*InvGasList[i]).Display();
                                                           
			cout << endl;                                
		}
		cout << endl;
		
		cout << "List of invalid electricity customers records:" << endl << endl;
    	for ( int i = 0; i < InvElecList.size(); i++ ) 
    	{
    		(*InvElecList[i]).Display();
                                                           
			cout << endl;                                
		}
	}
	
	if(avedata)
	{
		countGas = 0;
    	countElec = 0;
		for ( int i = 0; i < UtilityList.size(); i++ ) 
    	{
    		account = (*UtilityList[i]).getAccount();
    		   	
    		if( account >= 0 && account <= 99999)
    		{
    			GasCustomer * gasPtr = (GasCustomer *) UtilityList[i];
    			sumGas += gasPtr->getUsage();
    			sumGasBills += (*UtilityList[i]).calculateBill();
    			countGas++;
			}
    		else
			{
				ElectricityCustomer * elecPtr = (ElectricityCustomer *) UtilityList[i];
				sumElec += elecPtr->getkWattHourUsed();
				sumElecBills += (*UtilityList[i]).calculateBill();
				countElec++;
			}                               
		}
		//cout << countGas << endl;
		if(countGas != 0)
		{
			cout << "Average Gas customers Usage per Cubic meter: " << (sumGas/countGas) << endl;
			cout << "Average Gas customers Bill: " << (sumGasBills /countGas) << endl;
		}	
		//cout << countElec << endl;
		if(countElec != 0)
		{
			cout << "Average Electricity customers Usage of KWattHours: " << sumElec /countElec << endl;
			cout << "Average Electricity customers Bill: " << sumElecBills /countElec << endl;
		}
	}
	return 0;
}


