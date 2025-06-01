#include <boost/asio.hpp>
#include "DatabaseManager.h"
#include "UserManager.h"
#include "NetworkManager.h"

int main() {
    try {
        boost::asio::io_context io_context;

        DatabaseManager db("auth.db");
        if (!db.initialize()) {
            std::cerr << "Failed to initialize database\n";
            return 1;
        }

        UserManager userManager(db);

        // Можно добавить стартовую регистрацию или загрузку пользователей

        Server server(io_context, 1234, userManager);

        std::cout << "Server started on port 1234\n";

        io_context.run();
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
}