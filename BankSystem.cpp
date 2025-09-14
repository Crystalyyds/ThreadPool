#include "BankSystem.h"
#include <memory>
#include <unordered_map>

void BankSystem::addAccount(int id, int balance)
{
    std::lock_guard<std::mutex> lock(mtx);
    auto acc = std::make_shared<Account>(id, balance);
    accounts[id] = acc;
}

std::shared_ptr<Account> BankSystem::getAccount(int id)
{
    std::lock_guard<std::mutex> lock(mtx);
    auto it = accounts.find(id);
    if (it != accounts.end())
    {
        return it->second;
    }
    return nullptr;
}

bool BankSystem::transfer(int fromId, int toId, int amount)
{
    std::lock_guard<std::mutex> lock(mtx);
    auto fromIt = accounts.find(fromId);
    auto toIt = accounts.find(toId);
    if (fromIt == accounts.end() || toIt == accounts.end())
    {
        return false; // 用户不存在
    }
    auto fromUser = fromIt->second;
    auto toUser = toIt->second;
    if (fromUser->withdraw(amount))
        toUser->deposit(amount);
    else
        return false;
    return true;
}