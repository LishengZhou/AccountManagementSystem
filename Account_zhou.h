#ifndef ACCOUNT_ZHOU_H
#define ACCOUNT_ZHOU_H

#include <iostream>
#include <string>

class Account
{
	double CashBalance; // set value to be static
public:
	Account(); // if the file with balance exists, use that value; if not, 10000
	~Account();
    void setBalance( const double & );
	double getBalance() const;
	void addValue( double );
    virtual void displayPrice( std::string )
    {}
};



#endif