#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "User.h"
#include <unordered_map>
#include <string>
#include "DatabaseManager.h"

class UserManager {
public:
    explicit UserManager(DatabaseManager& db);
    bool registerUser(const std::string& username, const std::string& password, const std::string& role);
    bool authenticate(const std::string& username, const std::string& password);
    std::shared_ptr<User> getUser(const std::string& username);

private:
    std::unordered_map<std::string, std::shared_ptr<User>> users_;
    DatabaseManager& db_;

    std::string hashPassword(const std::string& password);
    std::string sha256(const std::string& input);
    bool isValidRole(const std::string& role);
};

#endif // USERMANAGER_H