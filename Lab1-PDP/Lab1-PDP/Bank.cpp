#include "Bank.h"
#include <iostream>

Bank::Bank()
{
	serial_counter = 0;
}

int Bank::getNextSerialNumber()
{
	return serial_counter++;
}

void Bank::transfer(Account& source, Account& destination, int amount)
{
	Account* first = &source;
	Account* second = &destination;


	if (source.id > destination.id) {
		std::swap(first, second);
	}

	std::lock(first->mtx, second->mtx);
	
	if (source.balance >= amount) {
		source.balance -= amount;
		destination.balance += amount;
		
		int serial_num = getNextSerialNumber();
		Operation operation(serial_num, amount, source.id, destination.id);

		source.addLog(operation);
		destination.addLog(operation);
	}
	else {
		throw std::runtime_error("Insufficient funds in source account.");
	}
}

bool Bank::checkConsistency(const std::vector<std::unique_ptr<Account>>& accounts) {
    for (const auto& accountPtr : accounts) {
        Account& account = *accountPtr;
        int computedBalance = account.getBalance();

        // Calculate the expected balance from account operations
        for (const Operation& operation : account.log) {
            if (operation.source == account.id) {
                computedBalance -= operation.amount;
            }
            else if (operation.destination == account.id) {
                computedBalance += operation.amount;
            }
        }

        // Verify calculated balance against actual balance
        if (computedBalance != account.getBalance()) {
            std::cerr << "Balance inconsistency in account " << account.id
                << ": expected " << computedBalance
                << ", found " << account.getBalance() << std::endl;
            return false;
        }

        // Validate each operation and confirm it exists in the counterpart account
        for (const Operation& operation : account.log) {
            if (operation.source >= accounts.size() || operation.destination >= accounts.size()) {
                std::cerr << "Invalid operation " << operation.serial_num << " in account " << account.id << std::endl;
                return false;
            }

            Account* counterAccount = (operation.source == account.id) ? accounts[operation.destination].get() : accounts[operation.source].get();

            bool matchFound = false;
            for (const Operation& counterOperation : counterAccount->log) {
                if (counterOperation.serial_num == operation.serial_num) {
                    matchFound = true;
                    break;
                }
            }
            if (!matchFound) {
                std::cerr << "Missing counterpart operation " << operation.serial_num
                    << " in account " << counterAccount->id << std::endl;
                return false;
            }
        }
    }
    std::cout << "### All accounts are consistent. ###" << std::endl;
    return true;
}
