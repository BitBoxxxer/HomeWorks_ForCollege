#include "Server.h"
#include <iostream>
#include <sstream>
#include <openssl/sha.h>
#include <fstream>
static std::ofstream logFile("server.log", std::ios::app);

Server::Server(boost::asio::io_context& io_context, short port, UserManager& userManager)
    : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)), userManager_(userManager) {
    do_accept();
}

void Server::do_accept() {
    auto socket = std::make_shared<tcp::socket>(acceptor_.get_executor().context());
    acceptor_.async_accept(*socket, [this, socket](boost::system::error_code ec) {
        if (!ec) {
            std::cout << "Client connected\n";
            std::thread(&Server::handle_session, this, socket).detach();
        }
        do_accept();
        });
}

void Server::handle_session(std::shared_ptr<tcp::socket> socket) {
    try {
        boost::asio::streambuf buf;
        boost::system::error_code ec;

        logFile << "Client connected from " << socket->remote_endpoint().address().to_string() << "\n";

        while (true) {
            boost::asio::read_until(*socket, buf, "\n", ec);
            if (ec) break;

            std::istream is(&buf);
            std::string line;
            std::getline(is, line);

            std::string response = process_command(line, socket);
            response += "\n";

            boost::asio::write(*socket, boost::asio::buffer(response), ec);
            if (ec) break;
        }
    }
    catch (std::exception& e) {
        std::cerr << "Session error: " << e.what() << "\n";
    }
}

std::string Server::process_command(const std::string& line, std::shared_ptr<tcp::socket> socket) {
    auto parts = split(line, ':');
    if (parts.empty()) return "ERROR: Invalid command";

    const std::string& cmd = parts[0];

    if (cmd == "REGISTER") {
        if (parts.size() != 5) return "REGISTER_FAILED";
        // формат: REGISTER:username:password:role
        const std::string& username = parts[1];
        const std::string& password = parts[2];
        const std::string& role = parts[3];

        if (userManager_.registerUser(username, password, role))
            return "REGISTER_SUCCESS";
        else
            return "REGISTER_FAILED";
    }
    else if (cmd == "LOGIN") {
        if (parts.size() != 3) return "AUTH_FAILED";
        const std::string& username = parts[1];
        const std::string& password = parts[2];

        if (userManager_.authenticate(username, password))
            return "AUTH_SUCCESS";
        else
            return "AUTH_FAILED";

    }
    else if (cmd == "CHECK_ACCESS") {
        if (parts.size() != 3) return "ACCESS_DENIED";
        const std::string& username = parts[1];
        const std::string& resource = parts[2];

        auto user = userManager_.getUser(username);
        if (user && user->hasAccess(resource))
            return "ACCESS_GRANTED";
        else
            return "ACCESS_DENIED";

    }
    if (cmd == "GET_RESOURCES") {
        if (parts.size() != 2) return "ERROR";
        const std::string& username = parts[1];
        auto user = userManager_.getUser(username);
        if (user) {
            return "RESOURCES:" + user->getAccessibleResources();
        }
        else {
            return "ERROR: User not found";
        }
    }
    else if (cmd == "GET_INFO") {
        if (parts.size() != 2) return "ERROR";
        const std::string& username = parts[1];
        auto user = userManager_.getUser(username);
        if (user) {
            return "USERINFO: Username=" + user->getUsername() + " Role=" + user->getRole();
        }
        else {
            return "ERROR: User not found";
        }
    }
    else {
        return "UNKNOWN_COMMAND";
    }
}

std::vector<std::string> Server::split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter))
        tokens.push_back(token);
    return tokens;
}