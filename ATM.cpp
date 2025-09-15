#include "ATM.h"
#include <mutex>
#include <iostream>

ATM::ATM(BankSystem &bank, ThreadPool &pool) : bank(bank), pool(pool)
{
}

void ATM::requestDeposit(int accountId, int amount)
{
    auto user = bank.getAccount(accountId);
    pool.enqueue([user, amount]()
                 { user->deposit(amount); });
}

void ATM::requestWithdraw(int accountId, int amount)
{
    auto user = bank.getAccount(accountId);
    pool.enqueue([user, amount]()
                 {
    bool ok = user->withdraw(amount);
    if (!ok) std::cout << "Withdraw failed: insufficient funds\n"; });
}

void ATM::requestBalance(int accountId)
{
    auto user = bank.getAccount(accountId);
    pool.enqueue([user]()
                 { std::cout << "Balance: " << user->getBalance() << "\n"; });
}

void ATM::requestTransfer(int fromId, int toId, int amount)
{
    auto fromUser = bank.getAccount(fromId);
    auto toUser = bank.getAccount(toId);
    pool.enqueue([this, fromId, toId, amount]()
                 {
    bool ok = this->bank.transfer(fromId, toId, amount);
    if (ok) {
        std::cout << "Transfer success: " << amount 
                  << " from " << fromId << " to " << toId << "\n";
    } else {
        std::cout << "Transfer failed\n";
    } });
}