#pragma once

#include "BankSystem.h"
#include "ThreadPool.h"

class ATM
{
private:
    BankSystem &bank;
    ThreadPool &pool;
    std::mutex mtx;
public:
    ATM(BankSystem &bank,ThreadPool &pool);
    void requestDeposit(int accountId,int amount); //存款
    void requestWithdraw(int accountId,int amount); //取款
    void requestBalance(int accountId); // 查询余额
    void requestTransfer(int fromId,int toIdk,int amount); //转账
};

