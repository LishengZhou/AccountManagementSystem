### Account Management System

This project is an account management system. This system has two accounts: **Stock Portfolio Account** and **Bank Account**. The Stock Portfolio Account stores all the stocks and related information the user own and can be used to trade stocks. This program mimics the price changing in a real stock transaction process by randomly select a stock price from two files: _Results_1.txt_ and _Results_2.txt_. The Bank Account stores the current cash balance and can be used to deposit or withdraw money. The initial cash balance is $10000 and it will be updated by later transactions. The cash balance and the stock portfolio will be retrieved from the following text files for later operations even if the program is previously exited.

These three text files will be generated in this program if they do not previously exist: 

1.	_total_porfolio.txt_: when the program exits, it will be updated by appending the current cash balance, stocks the user own, total portfolio value, date and time to the end of this file. It stores the history of the total portfolio value, stocks and cash balance.
2.	_stock_transaction_history.txt_: when a stock transaction is made, it will be updated by appending the “buy”/”sell” event, stock company symbol, number of shares, current price per share, stock value and time to the end of this file. It stores the history of stock transactions.
3.	_bank_transaction_history.txt_: when a bank transaction is made (including the money deposit/withdrawal from a stock transaction) , it will be updated by appending the “deposit/withdrawal” event, amount of money in the transaction, date and current cash balance to the end of this file. It stores the history of bank transactions.
	
