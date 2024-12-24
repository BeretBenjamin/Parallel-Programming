#include "Account.h"

Account::Account(int id, int balance)
{
	this->id = id;
	this->balance = balance;
}

void Account::addLog(const Operation& op)
{
	std::lock_guard<std::mutex> lock(mtx);
	log.push_back(op);
}

int Account::getBalance()
{
	std::lock_guard<std::mutex> lock(mtx); 
	return balance;
}
