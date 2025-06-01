#include "UserManager.h"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

UserManager::UserManager(DatabaseManager& db) : db_(db) {
    // Можно загрузить существующих пользователей из базы
}
const std::set<std::string> validRoles = { "Admin", "User", "Guest" };

bool UserManager::isValidRole(const std::string& role) {
    return validRoles.count(role) > 0;
}

bool UserManager::registerUser(const std::string& username, const std::string& password, const std::string& role) {
    if (!isValidRole(role)) return false; // Проверка роли
    if (db_.getUser(username).has_value()) return false; // Уже есть пользователь

    std::string hashed = hashPassword(password);
    if (db_.addUser(username, hashed, role)) {
        users_[username] = std::make_shared<User>(username, hashed, role);
        return true;
    }
    return false;
}

bool UserManager::authenticate(const std::string& username, const std::string& password) {
    auto userOpt = db_.getUser(username);
    if (!userOpt) return false;
    auto [id, dbUsername, passwordHash, role] = *userOpt;
    return hashPassword(password) == passwordHash;
}

std::shared_ptr<User> UserManager::getUser(const std::string& username) {
    auto it = users_.find(username);
    if (it != users_.end()) {
        return it->second;
    }
    // Можно загрузить из базы, если не найден
    auto userOpt = db_.getUser(username);
    if (userOpt) {
        auto [id, uname, passHash, role] = *userOpt;
        auto userPtr = std::make_shared<User>(uname, passHash, role);
        users_[username] = userPtr;
        return userPtr;
    }
    return nullptr;
}

std::string UserManager::hashPassword(const std::string& password) {
    // Реализуйте SHA-256
    return sha256(password);
}

std::string UserManager::sha256(const std::string& input) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    return ss.str();
}
std::string UserManager::hashPassword(const std::string& password) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password.c_str(), password.size());
    SHA256_Final(hash, &sha256);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

    return ss.str();
}