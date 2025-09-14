#include "Account.h"

Account::Account(int id, int balance) : id(id), balance(balance) {}

void Account::deposit(int amount)
{
    balance += amount;
}

bool Account::withdraw(int amount)
{
    balance -= amount;
}

int Account::getBalance()
{
    return balance;
}