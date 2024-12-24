#pragma once
#include <vector>
#include <mutex>
#include "Operation.h"
class Account {
public:
    int id;
    int balance;
    std::vector<Operation> log;
    std::mutex mtx;

    Account(int id, int balance);

    // Delete copy constructor and assignment operator
    Account(const Account&) = delete;
    Account& operator=(const Account&) = delete;

    void addLog(const Operation& op);
    int getBalance();
};

