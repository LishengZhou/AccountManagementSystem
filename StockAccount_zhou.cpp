// Name: Lisheng Zhou
// Final Project: Account Management System
// Date: Dec 13, 2015

#include "StockAccount_zhou.h"

using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::endl;
using std::setw;



// StockAccount constructor
StockAccount::StockAccount()
	: myHead( NULL ),
	  myTail( NULL )
{
	mySize = 0;  // size is 0 at the beginning
    srand ( time_t (NULL) );
	
	// read from 'total_portfoio.txt' for stock and cash balance
	string FileName = "total_portfolio.txt";


	ifstream inFile(FileName, std::ios::in);

	if (!inFile) {
		//std::cerr << "File " << FileName << " could not be read to retrieve previous stock portfolio value and cash balance." << endl;
	} else {
		// from the file
		double cashvalue; // cash balance
		string stockname; // stock name
		int stockshare; // stock share
		double stockvalue; // stock value
		double totalvalue; // total value of portfolio

		// use map to store previous stock portfolio
		// define short name for map type with company name and its share
		std::map< string, int > prevStock; 

		string col1, col2, col3, col4; // there are 4 cols in the file
		
		// if file exist
		while (inFile && !inFile.eof())
		{

			inFile >> col1 >> col2 >> col3 >> col4;
			//name_price.insert(std::pair< string, double >(stockname, stockvalue));
			// if first col equals "Cash"
			if (!col1.compare("Cash")) // if same, compare equals 0
				cashvalue = std::stod(col4);
			// if 1st col = "CompanySymbol"
			if (!col1.compare("CompanySymbol")) // empty previous map data structure
				prevStock.clear();
			// if stocks!
			if (col1.compare("Cash") && col1.compare("CompanySymbol") && col1.compare("Total") && col1.compare("Date") && col1.compare("Time")){
				stockname = col1;
				stockshare = std::stoi(col2);
				stockvalue = std::stod(col4);
				prevStock.insert(std::pair< string, int >(stockname, stockshare)); // insert the stock prtfolio into map 
			}
			// if total portfolio value
			if (!col1.compare("Total"))
				totalvalue = std::stod(col4);

		}
		inFile.close();

		// set cash balance
		Account::setBalance(cashvalue);


		// if map is not empty, put prev stocks into nodes
		
		if (!prevStock.empty()) {
			for (std::map< string, int >::iterator it = prevStock.begin(); it != prevStock.end(); ++it) { 
				Node * newPtr = new Node(it->first, it->second);
				//newPtr->StockValue = newPtr->StockNum * getPrice(newPtr->StockName); // update the stock value with current stock price
				// ADD NODES
				
				if (isEmpty()) { // if list empty
					newPtr->prev = NULL;
					newPtr->next = NULL;
					myHead = newPtr;
					myTail = newPtr;
					mySize++;
				} else { // if not empty
					
					myTail->next = newPtr;
					newPtr->prev = myTail;
					myTail = newPtr;
					mySize++;
				}
			}
			sortStockValue();
		}
			
	}
	
}

// destructor
StockAccount::~StockAccount()
{
	// save all information to file "total_portfolio.txt"
	ofstream portfolioFile;
	portfolioFile.open("total_portfolio.txt", ios::out | ios::app);

	portfolioFile << "\n\nCash balance = " << getBalance();
	portfolioFile << std::left << std::setw(16) << std::setfill(' ') << "\nCompanySymbol"
		<< std::left << std::setw(10) << std::setfill(' ') << "Number"
		<< std::left << std::setw(20) << std::setfill(' ') << "PricePerShare"
		<< std::left << std::setw(10) << std::setfill(' ') << "TotalValue";
	
	// print out nodes
	double sum = getBalance();
	Node *tempPtr = myHead;
	while (tempPtr != NULL){
		double price = getPrice(tempPtr->StockName);
		sum += tempPtr->StockNum * price;
		portfolioFile << "\n";
		portfolioFile << std::left << std::setw(16) << std::setfill(' ') << tempPtr->StockName
			<< std::left << std::setw(10) << std::setfill(' ') << tempPtr->StockNum
			<< std::left << std::setw(20) << std::setfill(' ') << price
			<< std::left << std::setw(10) << std::setfill(' ') << (tempPtr->StockNum * price);
		tempPtr = tempPtr->next;
	}
	portfolioFile << "\nTotal portfolio value: " << sum;

	// time 
	time_t seconds = time(NULL);
	struct tm timeinfo;
	localtime_s(&timeinfo, &seconds);

	portfolioFile << "\nDate of record: ";

	portfolioFile << std::setw(2) << std::setfill('0') << (timeinfo.tm_mon + 1) << "/"
		<< std::setw(2) << std::setfill('0') << timeinfo.tm_mday << "/"
		<< (timeinfo.tm_year + 1900) << "\t";

	portfolioFile << "\nTime of record: ";
	portfolioFile << std::setw(2) << std::setfill('0') << timeinfo.tm_hour << ":"
		<< std::setw(2) << std::setfill('0') << timeinfo.tm_min << ":"
		<< std::setw(2) << std::setfill('0') << timeinfo.tm_sec;

	portfolioFile.close();


	// empty the linked list
	if (!isEmpty()) {
		//cout << "Destroying nodes ... \n"; // LISHENG DELETE LATER
		Node *currentPtr = myHead;
		Node *tempPtr;

		while (currentPtr != 0) { // delete remaining nodes
			tempPtr = currentPtr;
			currentPtr = currentPtr->next;
			delete tempPtr;  // delete current object of tempPtr
		}
	}
	cout << "Saving all account information...\nDone.\n"; 
	cout << "Thank you for using this program. Have a great day!" << endl;

}

void StockAccount::displayPortfolio()
{
	// display the currect portfolio
	sortStockValue();

	// cash balance
	cout << "\nCash balance = $";
	cout.imbue(std::locale(""));
	cout << std::fixed;
	cout << std::setprecision(2);
	cout << Account::getBalance() << endl;

	double sum = Account::getBalance(); // total value
	// stock portfolio
	cout << std::left << std::setw(16) << std::setfill(' ') << "Company-Symbol"
		<< std::left << std::setw(10) << std::setfill(' ') << "Number"
		<< std::left << std::setw(20) << std::setfill(' ') << "Price-per-share"
		<< std::left << std::setw(10) << std::setfill(' ') << "Total value" << endl;

	if (isEmpty())
		cout << "[Empty Portfolio]" << endl;

	Node *tempPtr = myHead;
	while (tempPtr != NULL){
		double price = getPrice(tempPtr->StockName);
		sum += tempPtr->StockNum * price;
		
		cout << std::left << std::setw(16) << std::setfill(' ') << tempPtr->StockName 
			<< std::left << std::setw(10) << std::setfill(' ') << tempPtr->StockNum << "$"
			<< std::left << std::setw(20) << std::setfill(' ') << price << "$"
			<< std::left << std::setw(10) << std::setfill(' ')  << (tempPtr->StockNum * price) << endl;
		tempPtr = tempPtr->next;
	}

	// total value
	cout << "Total portfolio value: $" << sum << endl;
}



void StockAccount::setBalance(const double &value)
{
	// set account balance
	Account::setBalance(value);
}

double StockAccount::getBalance() const{
	// get balance
	return Account::getBalance();
}

bool StockAccount::isEmpty() const{
	// check if the list is empty
	return myHead == NULL;
}

void StockAccount::displayPrice( string newstring )
{
    // check if the company symbol exists
    if ( checkSymbol( newstring )) {
        cout << "\nCompany-Symbol  Price per share" << endl;
        cout << setw(8) << newstring << setw(12) << "$" << getPrice( newstring ) << endl;
    } else
        cout << "\nThe symbol cannot be found." << endl;
    
}

int StockAccount::getSize() const
{
	return mySize;
}

int StockAccount::getShare( string name ) const 
{
	// check if the company name exists in the list
	// if exists, return number of shares
	// if not exists, return 0
	Node *tempPtr = myHead;
	int tempNum = 0;
	while ( tempPtr != NULL ) {
		if ( tempPtr->StockName == name )
			tempNum = tempPtr->StockNum; // replace with number of shares
		tempPtr = tempPtr->next;
	}
	return tempNum;
}


void StockAccount::buyStock( Node * newNode, double max ) // SET STOCK VALUE WHEN COMPARE WITH MAX-LISHENG
{
    // add stock by company name and number of shares
	
	// check if name exists
	if (checkSymbol(newNode->StockName)){
		
		// check if price is lower than max
		double newprice = getPrice(newNode->StockName);
		if (newprice <= max) { // price is within limit

			// check if user has enough money
			double newcashbalance = getBalance() - newprice*newNode->StockNum;
			if (newcashbalance >= 0) {
				// go through transaction if it meets all requirements

				// set new cash balance
				setBalance(newcashbalance);

				// display on screen
				cout.imbue(std::locale(""));
				cout << std::fixed;
				cout << std::setprecision(2);
				cout << "You have purchased " << newNode->StockNum << " shares of " << newNode->StockName
					<< " at $" << newprice << " each for a total of $" << newprice*newNode->StockNum << "." << endl;

				// append transaction to stock history
				ofstream stockHistoryFile;
				stockHistoryFile.open("stock_transaction_history.txt", ios::out | ios::app);
				// event	company name	number of shares	price per share		total value		time

				stockHistoryFile << std::fixed << std::setprecision(2);
				
				stockHistoryFile << "\nBuy\t" << newNode->StockName << "\t" << newNode->StockNum << "\t" << newprice << "\t\t" << newprice*newNode->StockNum << "\t\t";
				time_t seconds = time(NULL);
				struct tm timeinfo;
				localtime_s(&timeinfo, &seconds);

				stockHistoryFile << std::setw(2) << std::setfill('0') << timeinfo.tm_hour << ":" 
					<< std::setw(2) << std::setfill('0') << timeinfo.tm_min << ":" 
					<< std::setw(2) << std::setfill('0') << timeinfo.tm_sec;

				stockHistoryFile.close(); // close file

				// append transaction to bank history
				ofstream bankHistoryFile;
				bankHistoryFile.open("bank_transaction_history.txt", ios::out | ios::app);
				// event amount date balance

				bankHistoryFile << std::fixed << std::setprecision(2);

				bankHistoryFile << "\nWithdrawal\t" << newprice*newNode->StockNum << "\t\t";
				bankHistoryFile << std::setw(2) << std::setfill('0') << (timeinfo.tm_mon + 1) << "/"
					<< std::setw(2) << std::setfill('0') << timeinfo.tm_mday << "/" 
					<< (timeinfo.tm_year + 1900) << "\t";
				bankHistoryFile << newcashbalance;

				bankHistoryFile.close(); // close file


				// update the linked list
				Node *newPtr = new Node(newNode->StockName, newNode->StockNum);
				if (isEmpty()) { // if list empty
					newPtr->prev = NULL;
					newPtr->next = NULL;
					myHead = newPtr;
					myTail = newPtr;
					mySize++;
				}
				else { // if not empty
					Node *tempPtr = myHead;
					while ((tempPtr) && (tempPtr->StockName != newNode->StockName))
						tempPtr = tempPtr->next;
					if (tempPtr)
						tempPtr->StockNum += newNode->StockNum;
					else {
						myTail->next = newPtr;
						newPtr->prev = myTail;
						myTail = newPtr;
						mySize++;
					}

				}

				// sort the list
				sortStockValue();
			}
			else{
				cout << "\nYour stock purchase amount is more than your current cash balance in your bank account. Transfaction failed." << endl;
			}

		}
		else{
			cout << "\nThe stock price per share $" << newprice << " is higher than the amount you are willing to pay. Transaction failed. " << endl;
		}
	}
	else {
		cout << "\nThe company symbol " << newNode->StockName << " is not found. Transaction failed." << endl;
	}
}

void StockAccount::sellStock( Node * sellNode, double min ) // SET STOCK VALUE WHEN COMPARE WITH MIN-LISHENG
{
    // sell stock by company name and number of shares
    // check if it is empty
    if ( isEmpty() )
        cout << "The stock portfolio is empty. Transaction failed." << endl;
	else {
		// check if it exists in the portfolio
		if (!getShare(sellNode->StockName)) // if not exist
			cout << "The company symbol " << sellNode->StockName << " does not exist in the stock portfolio. Transaction failed." << endl;

		else { // if exist

			// check if the number of shares to sell is smaller than original number of shares
			if (sellNode->StockNum > getShare(sellNode->StockName))
				cout << "The number of shares to sell exceeds the number of shares you own. Transaction failed." << endl;

			else {
				// check if the price is higher than the minimum amount
				double newprice = getPrice(sellNode->StockName);
				if (newprice < min)
					// current price is lower than min
					cout << "The stock price per share $" << newprice << " is lower than the minimum amount you are willing to sell for. Transaction failed." << endl;


				
				else {
					// it goes through

					// update cash balance
					double newcashbalance = getBalance() + newprice*sellNode->StockNum;
					setBalance(newcashbalance);

					// display on screen
					cout.imbue(std::locale(""));
					cout << std::fixed;
					cout << std::setprecision(2);
					cout << "You have sold " << sellNode->StockNum << " shares of " << sellNode->StockName
						<< " at $" << newprice << " each for a total of $" << newprice*sellNode->StockNum << "." << endl;

					// append transaction to stock history
					ofstream stockHistoryFile;
					stockHistoryFile.open("stock_transaction_history.txt", ios::out | ios::app);
					// event	company name	number of shares	price per share		total value		time

					stockHistoryFile << std::fixed << std::setprecision(2);

					stockHistoryFile << "\nSell\t" << sellNode->StockName << "\t" << sellNode->StockNum << "\t" << newprice << "\t\t" << newprice*sellNode->StockNum << "\t\t";
					time_t seconds = time(NULL);
					struct tm timeinfo;
					localtime_s(&timeinfo, &seconds);
					
					stockHistoryFile << std::setw(2) << std::setfill('0') << timeinfo.tm_hour << ":"
						<< std::setw(2) << std::setfill('0') << timeinfo.tm_min << ":"
						<< std::setw(2) << std::setfill('0') << timeinfo.tm_sec;

					stockHistoryFile.close(); // close file

					// append transaction to bank history
					ofstream bankHistoryFile;
					bankHistoryFile.open("bank_transaction_history.txt", ios::out | ios::app);
					// event amount date balance

					bankHistoryFile << std::fixed << std::setprecision(2);

					bankHistoryFile << "\nDesposit\t" << newprice*sellNode->StockNum << "\t\t";
					bankHistoryFile << std::setw(2) << std::setfill('0') << (timeinfo.tm_mon + 1) << "/"
						<< std::setw(2) << std::setfill('0') << timeinfo.tm_mday << "/"
						<< (timeinfo.tm_year + 1900) << "\t";
					bankHistoryFile << newcashbalance;

					bankHistoryFile.close(); // close file



					// update linked list
					if (sellNode->StockNum == getShare(sellNode->StockName)) {
						// it exists and can be sold
						// sell all shares
						Node *tempPtr = myHead;

						if (mySize == 1) { // if just one node

							tempPtr = myTail;
							myTail = tempPtr->prev;
							myHead = NULL;
							cout << "Stock " << tempPtr->StockName << " has been removed from the portfolio. " << endl;
							delete tempPtr;
							mySize--;

						}
						else {
							while (tempPtr->StockName != sellNode->StockName)
								tempPtr = tempPtr->next;

							if (tempPtr == myHead) {
								//cout << "head" << endl;
								myHead = tempPtr->next;
								myHead->prev = NULL;

							}
							else if (tempPtr == myTail) {
								//cout << "end" << endl;
								myTail = tempPtr->prev;
								myTail->next = NULL;

							}
							else {
								//cout << "middle" << endl;
								(tempPtr->prev)->next = tempPtr->next;
								(tempPtr->next)->prev = tempPtr->prev;

							}
							cout << "Stock " << tempPtr->StockName << " has been removed from the portfolio. " << endl;
							delete tempPtr;
							mySize--;

						}

					} // end else if  - sell all shares
					else {
						// sell some of the shares
						Node *sellPtr = myHead;
						while (sellPtr != NULL) {
							if (sellPtr->StockName == sellNode->StockName)
								sellPtr->StockNum -= sellNode->StockNum;
							sellPtr = sellPtr->next;

						} // end while
					}

					sortStockValue();
				}
			}

		} // end else ( !getShare( sellNode->StockName ) )
	}

}


void StockAccount::print()
{
    // print portfolio
    Node *tempPtr = myHead;
    if ( isEmpty() )
        cout << "The list is empty" << endl;
    
    while ( tempPtr != NULL )
    {
        cout << "stock name: " << tempPtr->StockName << ", number of shares: " << tempPtr->StockNum << endl;
        cout << tempPtr->StockValue << endl;
        tempPtr = tempPtr->next;
    }
}

void StockAccount::sortStockValue()
{
    // sort stock value
    
    // READ FROM FILE TO GET STOCK VALUES
    Node *tempPtr = myHead;
    while ( tempPtr != NULL ) {
		//if (tempPtr->StockValue==0) // if stock values does not exists
		if ( checkSymbol( tempPtr->StockName) )
			tempPtr->StockValue = tempPtr->StockNum * getPrice( tempPtr-> StockName );
        tempPtr = tempPtr->next;
    }
    

	if (isEmpty()){
        //cout << "The stock portfolio is empty. No sorting is needed." << endl;
	}
	else if (getSize() == 1){
        //cout << "Only 1 stock in the portfolio. No sorting is needed." << endl;
	}
    else if ( getSize() == 2 ) {
        // only head and tail
        if ( myHead->StockValue < myTail->StockValue ) { // sorting is needed
            myHead->prev = myTail;
            myTail->next = myHead;
            myHead = myTail;
            myTail = myHead->next;
            myTail->next = NULL;
            myHead->prev = NULL;
        }
    } else {
        quickSort(myHead, myTail); // use quick sort to sort the rest
    }
    
    
}

void StockAccount::swap( Node *a, Node *b )
{
    // swap all of the values in a Node
    int t = a->StockNum;
    a->StockNum = b->StockNum;
    b->StockNum = t;
    
    string s = a->StockName;
    a->StockName = b->StockName;
    b->StockName = s;
    
    double tV = a->StockValue;
    a->StockValue = b->StockValue;
    b->StockValue = tV;
    
}
Node * StockAccount::partition ( Node * l, Node * h )
{
    // set pivot as h value
    // l on left, h on right
    double x = h->StockValue;
    Node *i = l->prev;
    
    for ( Node *j = l; j != h; j = j->next ) { //j starts from left
        if ( j->StockValue >= x ) { // then i, j can move right one time
            i = (i == NULL)? l : i->next; // if l is not head, i=i->next
            swap(i, j );
        }
    }
    i = (i == NULL)? l : i->next;
    swap( i, h ); // i position is the position to insert h value
    return i;
}



void StockAccount::quickSort( Node *l, Node *h )
{
    if ( h != NULL && l != h && l != h-> next) {
        Node *p = partition(l, h); // p is the pivot point
        quickSort(l, p->prev); // sort the list before p
        quickSort(p->next,h);  // sort the list after p
    }
}

bool StockAccount::checkSymbol ( string newstring )
{
    // check if user input string exists
    
    // randomly select a file
    //srand ( time (NULL) );
    int r = rand() % 2; // random number: 0 or 1
    
    string FileName;
    if (r)
        FileName = "Results_1.txt";
    else
        FileName = "Results_2.txt";
    
    ifstream inFile( FileName, std::ios::in );
    
    if ( !inFile ) {
        std::cerr << "File could not be opened to view the company symbol and its price" << endl;
        exit( 1 );
    }
    
    string stockname; // 1st column: stock name
    double stockvalue; // 2nd column: stock value
    string time; // 3rd column: time mm/dd/yyyy
    
    // use map to store
    // define short name for map type with company name and its price
    std::map< string, double > name_price;
    
    while ( inFile && !inFile.eof() )
    {
        
        inFile >> stockname >> stockvalue >> time;
        name_price.insert( std::pair< string, double >(stockname, stockvalue) );

    }
    inFile.close();
    
    
    std::map<string, double>::iterator it;
    
    it = name_price.find( newstring );
    if ( it != name_price.end() )
        return true;
    else
        return false;
}

double StockAccount::getPrice( string newstring )
{
    // with user input string, find the price
    // *** use checkSymbol() before it
    // randomly select a file
    
    int r = rand() % 2; // random number: 0 or 1
    
    string FileName;
    if (r)
        FileName = "Results_1.txt";
    else
        FileName = "Results_2.txt";
    
    ifstream inFile( FileName, std::ios::in );
    
    if ( !inFile ) {
        std::cerr << "File could not be opened to view the company symbol and its price" << endl;
        exit( 1 );
    }
    
    string stockname; // 1st column: stock name
    double stockvalue; // 2nd column: stock value
    string time; // 3rd column: time mm/dd/yyyy
    
    // use map to store
    // define short name for map type with company name and its price
    std::map< string, double > name_price;
    
    while ( inFile && !inFile.eof() )
    {
        
        inFile >> stockname >> stockvalue >> time;
        name_price.insert( std::pair< string, double >(stockname, stockvalue) );
        
        
        
        //cout << stockname << endl;
        //cout << stockvalue << endl;
        //cout << time << endl;
    }
    inFile.close();
    
    
    std::map<string, double>::iterator it;
    
    it = name_price.find( newstring );
    
    return it->second;
    //cout << name_price['GOOG'];
    
}

void StockAccount::viewHistory()
{
	// view transaction history

	string newevent, company, number, price, totalvalue, newtime;

	ifstream stockHistoryFile("stock_transaction_history.txt", std::ios::in);

	if (stockHistoryFile){

		// header
		cout << std::left << std::setw(8) << std::setfill(' ') << "Event"
			<< std::left << std::setw(12) << std::setfill(' ') << "CompSymbol"
			<< std::left << std::setw(7) << std::setfill(' ') << "Number"
			<< std::left << std::setw(15) << std::setfill(' ') << "PricePerShare"
			<< std::left << std::setw(15) << std::setfill(' ') << " TotalValue"
			<< std::left << std::setw(10) << std::setfill(' ') << "  Time" << endl;

		while (stockHistoryFile && !stockHistoryFile.eof()){
			stockHistoryFile >> newevent >> company >> number >> price >> totalvalue >> newtime;

			double doublePrice = std::stod(price);
			double doubleValue = std::stod(totalvalue);

			cout.imbue(std::locale(""));
			cout << std::fixed;
			cout << std::setprecision(2);

			cout << std::left << std::setw(8) << std::setfill(' ') << newevent
				<< std::left << std::setw(12) << std::setfill(' ') << company
				<< std::left << std::setw(7) << std::setfill(' ') << number << "$"
				<< std::left << std::setw(15) << std::setfill(' ') << doublePrice << "$"
				<< std::left << std::setw(15) << std::setfill(' ') << doubleValue
				<< std::left << std::setw(10) << std::setfill(' ') << newtime << endl;

		}
	}
	else{
		cout << "\n[Stock Transaction History is empty]" << endl;
	}
	stockHistoryFile.close();
}

void StockAccount::viewGraph(string time_start, string time_end)
{
	// use MATLAB to view graph


	// my code
	string FileName = "total_portfolio.txt";

	ifstream inFile(FileName, std::ios::in);

	if (!inFile) {
		std::cerr << "File " << FileName << " does not exist to view the plot of total value of the portfolio." << endl;
	}
	else {
		// if file exist
		
		int n = 0; // array size
		string col1, col2, col3, col4; // there are 4 cols in the file

		// read file to see how many reads exist
		bool startpoint(false); // start point

		bool endpoint(false); // end point

		while (inFile && !inFile.eof())
		{
			inFile >> col1 >> col2 >> col3 >> col4;
			if (!col1.compare("Date")){
				if (!col4.compare(time_start))
					startpoint = true;
				if (!col4.compare(time_end)) {
					startpoint = false;
					endpoint = true;
				}
			}
			if (!col1.compare("Time")) {
				if (startpoint || endpoint)
					n++;
				endpoint = false;
			}
		}
		startpoint = false;
		endpoint = false;
		cout << "Number of records is: " << n << endl;
		
		if (n == 0)
			cout << "\nYou did not enter valid dates. Plotting failed. " << endl;
		else{
			double *d = new double[n];
			for (int k = 0; k < n; k++)
				d[k] = 0;



			// from the file
			double totalvalue; // total value of portfolio
			string date; // date
			string newtime; // time
			


			int iter = 0; // iterator

			inFile.seekg(0, std::ios_base::beg); // read from file again
			while (inFile && !inFile.eof())
			{

				inFile >> col1 >> col2 >> col3 >> col4;
				
				// if first col equals "Total"
				if (!col1.compare("Total")) {
					totalvalue = std::stod(col4);
					
					//cout << d[iter] << endl;
				}
				// if 1st col = "Date"
				if (!col1.compare("Date")){
					if (!col4.compare(time_start))
						startpoint = true;
					if (!col4.compare(time_end)) {
						startpoint = false;
						endpoint = true;
					}
				}
				if (!col1.compare("Time")) {
					if ((startpoint) || (endpoint)) {
						
						d[iter] = totalvalue;
						//cout << d[iter] << endl;
						endpoint = false;
						iter++;
					}	
				}
			}


			// my code - end

			// creating a pointer to the engine
			Engine *ep;
			ep = engOpen(NULL);
			if (ep == NULL)
			{
				cout << "Error: Not Found." << endl;
				exit(1);
			}
			// end

			mxArray *A;
			A = mxCreateDoubleMatrix(1, n, mxREAL);

			memcpy((void *)mxGetPr(A), (void *)d, n*sizeof(double));

			engPutVariable(ep, "TotalValue", A);


			// plot
			engEvalString(ep, "X=TotalValue;");
			engEvalString(ep, "plot(X);");	//call plot function


			engEvalString(ep, "title('Graph for the portfolio value');");
			engEvalString(ep, "xlabel('Records');");
			engEvalString(ep, "ylabel('Dollars($)');");

			mxDestroyArray(A);

			system("pause");
		}

	}
	inFile.close();

}