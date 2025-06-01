#include <boost/asio.hpp>
#include <iostream>
#include <thread>
#include "UserManager.h"

using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_context& io_context, short port, UserManager& userManager)
        : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), userManager_(userManager) {
        do_accept();
    }

private:
    void do_accept() {
        acceptor_.async_accept(
            [this](boost::system::error_code ec, tcp::socket socket) {
                if (!ec) {
                    std::cout << "Client connected\n";
                    std::thread(&Server::handle_session, this, std::move(socket)).detach();
                }
                do_accept();
            });
    }

    void handle_session(tcp::socket socket) {
        try {
            boost::asio::streambuf buf;
            boost::system::error_code ec;

            while (true) {
                boost::asio::read_until(socket, buf, "\n", ec);
                if (ec) break;

                std::istream is(&buf);
                std::string line;
                std::getline(is, line);

                std::string response = process_command(line);
                response += "\n";

                boost::asio::write(socket, boost::asio::buffer(response), ec);
                if (ec) break;
            }
        }
        catch (std::exception& e) {
            std::cerr << "Session error: " << e.what() << "\n";
        }
    }

    std::string process_command(const std::string& cmd) {
        // Простейшая обработка команд
        // Например: LOGIN:username:password
        // Реализуйте парсинг и вызов методов UserManager
        // Возвращайте ответ: AUTH_SUCCESS, AUTH_FAILED и т.п.
        if (cmd.find("LOGIN:") == 0) {
            auto parts = split(cmd, ':');
            if (parts.size() == 3) {
                const std::string& username = parts[1];
                const std::string& password = parts[2];
                if (userManager_.authenticate(username, password))
                    return "AUTH_SUCCESS";
                else
                    return "AUTH_FAILED";
            }
        }
        // Добавьте обработку других команд
        return "UNKNOWN_COMMAND";
    }

    std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter))
            tokens.push_back(token);
        return tokens;
    }

    tcp::acceptor acceptor_;
    UserManager& userManager_;
};