#ifndef NODE_ZHOU_H
#define NODE_ZHOU_H

#include <iostream>
#include <string>
using namespace std;

class Node
{
	friend class StockAccount;
public:

	Node(string name, int num) // name: stock symbol; num: number of shares
		:StockName(name), StockNum(num)
	{
		this->next=NULL;
		this->prev=NULL;
        StockValue = 0;
	}
	
private:
	string StockName;
	int StockNum;
    double StockValue;
	Node *next;
	Node *prev;
 
};

#endif