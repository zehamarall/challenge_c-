#include "server.h"


Server::Server(boost::asio::io_service& io_service, short port, short lengthMaxFile)
    : io_service_(io_service),
    lengthMaxFile_(lengthMaxFile),
    acceptor_(io_service, tcp::endpoint(tcp::v4(), port))
{
    std::cout << "Server construct" << std::endl;
    Session* new_session = new Session(io_service_, lengthMaxFile_);
    acceptor_.async_accept(new_session->socket(),
        boost::bind(&Server::handle_accept, this, new_session,
        boost::asio::placeholders::error));
}

void Server::handle_accept(Session* new_session,
    const boost::system::error_code& error)
{
    if (!error) {
        std::cout << "New Session" << std::endl;
        new_session->start();
        new_session = new Session(io_service_, lengthMaxFile_);
        acceptor_.async_accept(new_session->socket(),
            boost::bind(&Server::handle_accept, this, new_session,
            boost::asio::placeholders::error));
    } else {
        delete new_session;
    }
}

