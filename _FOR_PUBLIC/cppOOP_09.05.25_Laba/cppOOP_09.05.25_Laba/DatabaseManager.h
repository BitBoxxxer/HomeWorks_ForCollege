#define DATABASEMANAGER_H

#include <sqlite3.h>
#include <string>
#include <optional>
#include <tuple>

class DatabaseManager {
public:
    explicit DatabaseManager(const std::string& dbPath);
    ~DatabaseManager();

    bool initialize();
    bool addUser(const std::string& username, const std::string& passwordHash, const std::string& role);
    std::optional<std::tuple<int, std::string, std::string, std::string>> getUser(const std::string& username);

private:
    sqlite3* db_;
    std::string dbPath_;
};
