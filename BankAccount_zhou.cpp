// Name: Lisheng Zhou
// Final Project: Account Management System
// Date: Dec 13, 2015


#include "BankAccount_zhou.h"
using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::setw;

// constructor
BankAccount::BankAccount()
: Account()
{
}

BankAccount::~BankAccount()
{
}

void BankAccount::viewBalance()
{
	// view account balance
	// round to 2 decimal places
    cout.precision(2);
	cout << "You have $" << std::fixed << getBalance() << " in your bank account." << endl;
}

void BankAccount::deposit(double value)
{
	// deposit
	double newbalance = getBalance() + value;
	setBalance(newbalance);

	// add event to history
	// time
	time_t seconds = time(NULL);
	struct tm timeinfo;
	localtime_s(&timeinfo, &seconds);

	// append transaction to bank history
	ofstream bankHistoryFile;
	bankHistoryFile.open("bank_transaction_history.txt", std::ios::out | std::ios::app);
	// event amount date balance

	bankHistoryFile << std::fixed << std::setprecision(2);

	bankHistoryFile << "\nDesposit\t" << value << "\t\t";
	bankHistoryFile << std::setw(2) << std::setfill('0') << (timeinfo.tm_mon + 1) << "/"
		<< std::setw(2) << std::setfill('0') << timeinfo.tm_mday << "/"
		<< (timeinfo.tm_year + 1900) << "\t";
	bankHistoryFile << newbalance;

	bankHistoryFile.close(); // close file

}

void BankAccount::withdraw(double value)
{
	// withdraw
	double newbalance = getBalance() - value;
	if (newbalance >= 0){
		setBalance(newbalance);

		// add event to history
		// time
		time_t seconds = time(NULL);
		struct tm timeinfo;
		localtime_s(&timeinfo, &seconds);

		// append transaction to bank history
		ofstream bankHistoryFile;
		bankHistoryFile.open("bank_transaction_history.txt", std::ios::out | std::ios::app);
		// event amount date balance

		bankHistoryFile << std::fixed << std::setprecision(2);

		bankHistoryFile << "\nWithdrawal\t" << value << "\t\t";
		bankHistoryFile << std::setw(2) << std::setfill('0') << (timeinfo.tm_mon + 1) << "/"
			<< std::setw(2) << std::setfill('0') << timeinfo.tm_mday << "/"
			<< (timeinfo.tm_year + 1900) << "\t";
		bankHistoryFile << newbalance;

		bankHistoryFile.close(); // close file
	}
	else
		cout << "You don't have sufficient amount of cash balance in your bank account. Transaction failed." << endl;
}

void BankAccount::printHistory()
{
	// print history
	string newevent, amount, date, balance;

	ifstream bankHistoryFile("bank_transaction_history.txt", std::ios::in);

	if (bankHistoryFile){

		// header
		cout << std::left << std::setw(16) << std::setfill(' ') << "Event"
			<< std::left << std::setw(15) << std::setfill(' ') << "Amount"
			<< std::left << std::setw(20) << std::setfill(' ') << " Date"
			<< std::left << std::setw(10) << std::setfill(' ') << " Balance" << endl;

		while (bankHistoryFile && !bankHistoryFile.eof()){
			bankHistoryFile >> newevent >> amount >> date >> balance;
			
			double doubleAmount = std::stod(amount);
			double doubleBalance = std::stod(balance);
			
			cout.imbue(std::locale(""));
			cout << std::fixed;
			cout << std::setprecision(2);

			cout << std::left << std::setw(16) << std::setfill(' ') << newevent << "$"
				<< std::left << std::setw(15) << std::setfill(' ') << doubleAmount
				<< std::left << std::setw(20) << std::setfill(' ') << date << "$"
				<< std::left << std::setw(10) << std::setfill(' ') << doubleBalance << endl;

		}
	}
	else{
		cout << "\n[Bank Transaction History is empty]" << endl;
	}
	bankHistoryFile.close();
}


void BankAccount::setBalance( const double &value )
{
    // set account balance
    Account::setBalance( value );
}

double BankAccount::getBalance() const{
	// get balance
    return Account::getBalance();
}
/*
void BankAccount::printHistory()
{
	// print history entries
	// iterator
	std::vector< History >::const_iterator it;
	cout << std::left<< std::setw(20) << std::setfill(' ') << "Event";
	cout << std::left<< std::setw(20) << std::setfill(' ') << "Amount";
	cout << std::left<< std::setw(20) << std::setfill(' ') << "Date";
	cout << std::left<< std::setw(20) << std::setfill(' ') << "Balance";
	//cout << endl;
	for ( it = HisV.begin(); it != HisV.end(); it++ ) {
		cout << std::left<< std::setw(20) << std::setfill(' ') << (*it).getEvent();


		cout << std::left<< std::setw(20) << std::setfill(' ') << (*it).getValue();

		cout << std::left<< std::setw(20) << std::setfill(' ') << (*it).getDate();
		cout.imbue( std::locale("") );
		cout << std::left<< std::setw(20) << std::setfill(' ') << (*it).getBalance();
		//cout << endl;
	}
	
}*/
