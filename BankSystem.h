#pragma once

#include "Account.h"

#include <mutex>
#include <memory>
#include <unordered_map>

class BankSystem
{
private:
    std::unordered_map<int, std::shared_ptr<Account>> accounts;
    std::mutex mtx;

public:
    void addAccount(int id,int balance); //添加账户
    std::shared_ptr<Account> getAccount(int id); // 获取用户指针
    bool transfer(int fromId,int toid,int amount); // 转账
};
