// Name: Lisheng Zhou
// Final Project: Account Management System
// Date: Dec 13, 2015

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <time.h>
#include <iomanip>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;

#include "Account_zhou.h"
#include "BankAccount_zhou.h"
#include "StockAccount_zhou.h"
#include "Node_zhou.h"

void instructionTop()
{
    // instruction for main menu
    cout << "\n\nPlease select an account to access:" << endl;
    cout << "1. Stock Portfolio Account" << endl;
    cout << "2. Bank Account" << endl;
    cout << "3. Exit" << endl;
    cout << "Option: ";
}

void stockInstruction()
{
    // instruction for stock menu
    cout << "\nPlease select an option:" << endl;
    cout << "1. Display the price for a stock symbol" << endl;
    cout << "2. Display the current portfolio" << endl;
    cout << "3. Buy shares" << endl;
    cout << "4. Sell shares" << endl;
    cout << "5. View a graph for the portfolio value" << endl;
    cout << "6. View transaction history" << endl;
    cout << "7. Return to previous menu" << endl;
    cout << "Option: ";
}

void bankInstruction()
{
    // instruction for bank menu
    cout << "\nPlease select an option:" << endl;
    cout << "1. View account balance" << endl;
    cout << "2. Deposit money" << endl;
    cout << "3. Withdraw money" << endl;
    cout << "4. Print out history" << endl;
    cout << "5. Return to previous menu" << endl;
    cout << "Option: ";
}

void mainMenu()
{
    int mainChoice; // choice for top menu
    
	// stockaccount object
	StockAccount stockObj;
	// bankaccount object
	BankAccount bankObj;

	// link two balance
	bankObj.setBalance(stockObj.getBalance());

    do {
        instructionTop();
        cin >> mainChoice;
		while (cin.fail()){
			cout << "\nPlease enter an integer value: ";
			cin.clear();
			cin.ignore();
			cin >> mainChoice;
		}

        switch ( mainChoice ) {
            case 1:
            {
                // stock menu
                cout << "\nStock Portfolio Account" << endl;

				// update balance
				stockObj.setBalance(bankObj.getBalance());

                int stockChoice; // choice for stock menu
                
                string stockSymbol; // stock symbol
                int numberShare; // number of shares
                double maxPrice; // max price to buy shares
                double minPrice; // min Price to sell shares
				string time_start, time_end; // time period to view graph
                
                do {
                    stockInstruction();
                    cin >> stockChoice;

					while (cin.fail()){
						cout << "\nPlease enter an integer value: ";
						cin.clear();
						cin.ignore();
						cin >> stockChoice;
					}

                    //StockAccount *stockPtr = &account;
                    
                    switch ( stockChoice ) {
                        case 1:
                            // display price for stock
                            cout << "\nPlease enter the stock symbol: ";
                            cin >> stockSymbol;
                            stockObj.displayPrice( stockSymbol ); // WORKING ON IT
                            break;
                        case 2:
                            // display current portfolio
                            //cout << "display current portfolio" << endl;
							stockObj.displayPortfolio();
                            break;
                        case 3:
                            // buy shares
                            cout << "Please enter the stock symbol you wish to purchase: ";
                            cin >> stockSymbol;
							
                            cout << "Please enter the number of shares: ";
                            cin >> numberShare;
							while (cin.fail()){
								cout << "\nPlease enter an integer value: ";
								cin.clear();
								cin.ignore();
								cin >> numberShare;
							}

                            cout << "Please enter the maximum amount you are willing to pay per share: $";
                            cin >> maxPrice;
							while (cin.fail()){
								cout << "\nPlease enter a double value: $";
								cin.clear();
								cin.ignore();
								cin >> maxPrice;
							}

							stockObj.buyStock(&Node(stockSymbol, numberShare), maxPrice);
                            
                            break;
                        case 4:
                            // sell shares
                            cout << "Please enter the stock symbol you wish to sell: ";
                            cin >> stockSymbol;
                            cout << "Please enter the number of shares: ";
                            cin >> numberShare;

							while (cin.fail()){
								cout << "\nPlease enter an integer value: ";
								cin.clear();
								cin.ignore();
								cin >> numberShare;
							}

                            cout << "Please enter the minimum amount you are willing to sell per share: $";
                            cin >> minPrice;
							while (cin.fail()){
								cout << "\nPlease enter a double value: $";
								cin.clear();
								cin.ignore();
								cin >> minPrice;
							}

							stockObj.sellStock(&Node(stockSymbol, numberShare), minPrice);
                            
                            break;
                        case 5:
                            // view matlab graph
							cout << "\nPlease select the time period in the graph: " << endl;
							cout << "Start Date (mm/dd/yyyy): ";
							cin >> time_start;
							cout << "\nEnd Date (mm/dd/yyyy): ";
							cin >> time_end;
							stockObj.viewGraph(time_start, time_end);
                            
                            break;
                        case 6:
                            // view transaction history
							stockObj.viewHistory();
                            
                            break;
                        
                    } // end stock switch
                } while ( stockChoice != 7 );
                
                break;
            } // end case 1
            case 2:
            {
                // bank menu
                cout << "\nBank Account" << endl;

				// update balance
				bankObj.setBalance(stockObj.getBalance());

                int bankChoice; // choice for bank menu
                
                double amount; // amount of money to deposit or withdraw
                
                do {
                    bankInstruction();
                    cin >> bankChoice;
                    
					while (cin.fail()){
						cout << "\nPlease enter an integer value: ";
						cin.clear();
						cin.ignore();
						cin >> bankChoice;
					}

                    switch ( bankChoice ) {
                        case 1:
                            // view account balance
                            
							bankObj.viewBalance();
                            break;
                        case 2:
                            // deposit
							
                            cout << "Please select the amount you wish to deposit: $";
                            cin >> amount;
							
							while (cin.fail()){
								cout << "\nPlease enter a double value: $";
								cin.clear();
								cin.ignore();
								cin >> amount;
							}
							
							bankObj.deposit(amount);
                            break;
                        case 3:
                            // withdraw
                            cout << "Please select the amount you wish to withdraw: $";
                            cin >> amount;
                            
							while (cin.fail()){
								cout << "\nPlease enter a double value: $";
								cin.clear();
								cin.ignore();
								cin >> amount;
							}
							bankObj.withdraw(amount);

                            break;
                        case 4:
                            // print history
							bankObj.printHistory();
                            
                            break;
                    } // end bank switch
                } while ( bankChoice != 5 );
                
                break;
            } // end case 2
        } // end main switch
    } while ( mainChoice != 3 );

}


int main()
{
	// main function
	mainMenu();
    
	return 0;
}