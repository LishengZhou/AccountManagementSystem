// Name: Lisheng Zhou
// Final Project: Account Management System
// Date: Dec 13, 2015

#include "Account_zhou.h"

// constructor
Account::Account()
{
	CashBalance = 10000;
}
// destructor
Account::~Account()
{
}

void Account::setBalance( const double &value )
{
    // set balance
    CashBalance = value;
}



double Account::getBalance() const
{
	// return cash balance
	return CashBalance;
}

void Account::addValue( double value )
{
	CashBalance+=value;
}