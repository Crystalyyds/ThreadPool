#pragma once

#include <mutex>

class Account
{
    private:
        int  id;
        int  balance;
        std::mutex mtx;
    
    public:
        Account(int id, int balance); //创建用户
        void deposit(int amount);  // 存钱
        bool withdraw(int amount); // 取钱
        int getBalance(); //  查询余额
};