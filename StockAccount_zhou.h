#ifndef STOCKACCOUNT_ZHOU_H
#define STOCKACCOUNT_ZHOU_H

#include "Account_zhou.h"
#include "Node_zhou.h"
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <map>
#include <iomanip>
#include <new>

#pragma comment( lib, "libmx.lib" )
#pragma comment( lib, "libmex.lib" )
#pragma comment( lib, "libeng.lib" )

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif
#include "mex.h"
// end
#include<engine.h>
#include<cmath>




class StockAccount : public Account
{
public:
	StockAccount();
	~StockAccount();
	double getBalance() const;
	void setBalance(const double &);
	void displayPrice( std::string );
    bool checkSymbol( std::string );
    double getPrice( std:: string );
	bool isEmpty() const;
	int getSize() const; 
	int getShare( string ) const;
	void buyStock( Node *, double );
    void sellStock( Node *, double );
    void print();
    void sortStockValue();
    void swap ( Node *, Node * );
    Node * partition( Node *, Node * );
    void quickSort( Node *, Node * );
	void displayPortfolio();
	void viewHistory();
	void viewGraph(string, string);


	//friend int rGen();
private:
	Node *myHead; // first pointer
	Node *myTail; // last pointer
	int mySize; // size of doubly linked list
};



#endif