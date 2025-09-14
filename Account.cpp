#include "Account.h"

Account::Account(int id, int balance) : id(id), balance(balance) {}

void Account::deposit(int amount)
{
    std::lock_guard<std::mutex> lock(mtx);
    balance += amount;
}

bool Account::withdraw(int amount)
{
    std::lock_guard<std::mutex> lock(mtx);
    if (balance >= amount)
    {
        balance -= amount;
        return true;
    }
    return false;
}

int Account::getBalance()
{
    std::lock_guard<std::mutex> lock(mtx);
    return balance;
}