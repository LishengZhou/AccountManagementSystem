#ifndef BANKACCOUNT_ZHOU_H
#define BANKACCOUNT_ZHOU_H

#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <iomanip>

#include "Account_zhou.h"






class BankAccount : public Account
{
public:
	BankAccount();
	~BankAccount();
	void viewBalance();
	void deposit( double );
	void withdraw( double );
	void printHistory();
    void setBalance( const double &);
    double getBalance() const;

	/*
	// History vector
	// get
	const std::vector<History>& getHisvector() const {return HisV;}
	// add
	void addHistory(History x) { HisV.push_back(x); }
private:
	std::vector<History> HisV;
	*/
};



#endif