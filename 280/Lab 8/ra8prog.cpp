#include <iostream>
#include <string>
#include <vector> 
#include "val.h"
using namespace std; 


void ExecuteOp1(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " - " << val2 << " is " <<  val1 - val2 << endl;
}

void ExecuteOp2(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " - " << val2 << " is " <<  val1 * val2 << endl;
}

void ExecuteOp3(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " < " << val2 << " is " <<  (val1 < val2) << endl;
}

void ExecuteOp4(const Value& val1, const Value& val2) 
{ 
	cout << val1 << " && " << val2 << " is " <<  (val1 && val2) << endl; 
}
	
int main(int argc, char *argv[])
{
	Value ErrorVal;
	Value IntVal(7);
	float num = 4.25;
	Value FloatVal(num);
	string str1 = "CS280";
	bool flag1 = false, flag2 = true;
	Value StrVal1(str1); 
	Value BoolVal1(flag1);
	Value BoolVal2(flag2);
	string str2 = "Fall 2022";
	Value StrVal2(str2);
	vector<Value> vals( {ErrorVal, IntVal, FloatVal, StrVal1, StrVal2, BoolVal1, BoolVal2} );
	bool subflag = false, multflag = false, ltflag =false, andflag = false;
	
	if (argc == 1)
	{
		cerr << "No Specified arguments." << endl;
		return 0;
	}
	
	string arg( argv[1] );
	if( arg == "-subt" )
		subflag = true;
	else if( arg == "-mult" )
		multflag = true;
	else if( arg == "-lt" )
		ltflag = true;		
	else if( arg == "-and" )
		andflag = true;		
	else {
			cerr << "UNRECOGNIZED FLAG " << arg << endl;
			return 0;
	}
		
	
	cout << "ErrorVal=" << ErrorVal << endl; 
	cout << "IntVal=" << IntVal << endl; 
	cout << "FloatVal=" << FloatVal << endl; 
	cout << "StrVal1=" << StrVal1 << endl; 
	cout << "StrVal2=" << StrVal2 << endl;
	cout << "BoolVal1=" << BoolVal1 << endl;
	cout << "BoolVal2=" << BoolVal2 << endl;
	
	if(subflag)
	{
		for(int i = 0; i < vals.size(); i++ ) 
			for( int j = 0; j < vals.size(); j++ )
				if( i != j )
					ExecuteOp1( vals[i], vals[j] );
	}
	
	if(multflag)
	{
		for(int i = 0; i < vals.size(); i++ ) 
		for( int j = 0; j < vals.size(); j++ )
			if( i != j )
				ExecuteOp2( vals[i], vals[j] );
	}	
	
	if(ltflag)
	{				
		for(int i = 0; i < vals.size(); i++ ) 
		for( int j = 0; j < vals.size(); j++ )
			if( i != j )
				ExecuteOp3( vals[i], vals[j] );
	}
	if(andflag)
	{
		for(int i = 0; i < vals.size(); i++ ) 
		for( int j = 0; j < vals.size(); j++ )
			if( i != j )
				ExecuteOp4( vals[i], vals[j] );
	}
	return 0;
}

