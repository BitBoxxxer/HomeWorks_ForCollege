#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <memory>
#include <string>
#include "UserManager.h"

using boost::asio::ip::tcp;

class Server {
public:
    Server(boost::asio::io_context& io_context, short port, UserManager& userManager);
private:
    void do_accept();
    void handle_session(std::shared_ptr<tcp::socket> socket);
    std::string process_command(const std::string& line, std::shared_ptr<tcp::socket> socket);
    std::vector<std::string> split(const std::string& s, char delimiter);

    tcp::acceptor acceptor_;
    UserManager& userManager_;
};

#endif // SERVER_H