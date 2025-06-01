#define USER_H

#include <string>
#include <unordered_set>

class User {
public:
    User(std::string username, std::string passwordHash, std::string role)
        : username_(std::move(username)), passwordHash_(std::move(passwordHash)), role_(std::move(role)) {
    }

    const std::string& getUsername() const { return username_; }
    const std::string& getPasswordHash() const { return passwordHash_; }
    const std::string& getRole() const { return role_; }

    bool hasAccess(const std::string& resource) const {
        if (role_ == "Admin") return true;

        if (role_ == "User") {
            static std::unordered_set<std::string> user_resources = { "resource1", "resource2" };
            return user_resources.count(resource) > 0;
        }

        if (role_ == "Guest") {
            return resource == "public";
        }

        return false;
    }

    std::string getAccessibleResources() const {
        if (role_ == "Admin") return "all";
        if (role_ == "User") return "resource1, resource2";
        if (role_ == "Guest") return "public";
        return "";
    }

private:
    std::string username_;
    std::string passwordHash_;
    std::string role_;
};
