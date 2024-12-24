#include "Account.h"
#include "Bank.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <thread>
#include <tuple>
#include <vector>
#include "main.h"

Bank bank;
std::mutex global_mtx;
bool running = true; 

void readAccountsFromFile(const std::string& filepath, std::vector<std::unique_ptr<Account>>& accountList) {
    try {
        std::ifstream inputFile(filepath);
        if (!inputFile) throw std::runtime_error("Failed to open the specified file");

        std::string record;
        while (std::getline(inputFile, record)) {
            if (record.empty() || record.front() == '#') continue;

            std::istringstream recordStream(record);
            int accountId, accountBalance;
            recordStream >> accountId >> accountBalance;
            accountList.push_back(std::make_unique<Account>(accountId, accountBalance));
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "An error occurred while reading accounts: " << ex.what() << std::endl;
    }
    catch (...) {
        std::cerr << "An unspecified error occurred during account loading." << std::endl;
    }
}


void readTransfersFromFile(const std::string& filepath, std::vector<std::tuple<int, int, int>>& transferList) {
    std::ifstream inputFile(filepath);
    if (!inputFile) throw std::runtime_error("Could not open the specified file");

    std::string record;
    while (std::getline(inputFile, record)) {
        if (record.empty() || record[0] == '#') continue;

        std::istringstream recordStream(record);
        int fromAccount, toAccount, transferAmount;
        recordStream >> fromAccount >> toAccount >> transferAmount;
        transferList.emplace_back(fromAccount, toAccount, transferAmount);
    }
}



void transferMoney(Account* source, Account* destination, int amount) {
    std::unique_lock<std::mutex> lock1(source->mtx, std::defer_lock);
    std::unique_lock<std::mutex> lock2(destination->mtx, std::defer_lock);

    std::lock(lock1, lock2); 

    
    if (source->balance >= amount) {
        source->balance -= amount;
        destination->balance += amount;
    }
    else {
        std::cerr << "error: Transfer failed. Insufficient funds" << source->id << std::endl;
    }
}


void periodicCheck(std::vector<std::unique_ptr<Account>>& accounts) {
    while (running) { 
        std::this_thread::sleep_for(std::chrono::seconds(1));
        {
            std::lock_guard<std::mutex> lock(global_mtx);
            bank.checkConsistency(accounts); 
        }
    }
}

int main() {
    std::vector<std::unique_ptr<Account>> accounts;
    std::vector<std::tuple<int, int, int>> transfers;

    try {
        readAccountsFromFile("Accounts.txt", accounts);
        readTransfersFromFile("Transfers.txt", transfers);
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading files: " << e.what() << std::endl;
        return 1; 
    }

    std::vector<std::thread> transferThreads;
    std::thread checkerThread(periodicCheck, std::ref(accounts)); 

    
    for (const auto& transfer : transfers) {
        int source_id, dest_id, amount;
        std::tie(source_id, dest_id, amount) = transfer;

       
        if (source_id >= accounts.size() || dest_id >= accounts.size()) {
            std::cerr << "Invalid account index in transfer: " << source_id << ", " << dest_id << std::endl;
            continue;  
        }

        
        transferThreads.emplace_back(transferMoney, accounts[source_id].get(), accounts[dest_id].get(), amount);
    }

    
    for (auto& thread : transferThreads) {
        thread.join();
    }

    
    {
        std::lock_guard<std::mutex> lock(global_mtx);
        bank.checkConsistency(accounts);
    }

    
    running = false; 
    checkerThread.join(); 

    std::cout << "+++ Transfers completed successfully. +++" << std::endl;
    std::cout << "+++ Balances After Transfers: +++" << std::endl;
    for (const auto& accountPtr : accounts) {
        Account& account = *accountPtr; 
        std::cout << "+++ ID: " << account.id << ", Balance =  " << account.getBalance() << "$ +++"<<std::endl;
    }
    return 0;
}
