#include "ATM.h"
#include "BankSystem.h"
#include "ThreadPool.h"
#include <iostream>
#include <thread>
#include <chrono>

int main()
{
    // 创建线程池（4个线程）
    ThreadPool pool(4);

    // 创建银行系统
    BankSystem bank;
    bank.addAccount(1, 1000); // 账户1 初始余额 1000
    bank.addAccount(2, 500);  // 账户2 初始余额 500
    bank.addAccount(3, 200);  // 账户3 初始余额 200

    // 创建ATM（绑定银行系统和线程池）
    ATM atm(bank, pool);

    // 模拟多线程操作
    atm.requestDeposit(1, 200);     // 账户1 存款 200
    atm.requestWithdraw(2, 100);    // 账户2 取款 100
    atm.requestBalance(1);          // 查询账户1余额
    atm.requestBalance(2);          // 查询账户2余额
    atm.requestTransfer(1, 3, 300); // 账户1 转账 300 到 账户3
    atm.requestTransfer(2, 1, 1000);// 账户2 尝试转账 1000 到 账户1（失败）

    // 为了让线程池里的任务有时间完成，main线程需要等待
    std::this_thread::sleep_for(std::chrono::seconds(2));

    std::cout << "Final Balances:" << std::endl;
    atm.requestBalance(1);
    atm.requestBalance(2);
    atm.requestBalance(3);

    // 再等一等，保证打印完成
    std::this_thread::sleep_for(std::chrono::seconds(2));

    return 0;
}
