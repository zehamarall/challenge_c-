#ifndef __server_h__
#define __server_h__

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem/fstream.hpp>
#include "session.h"

using boost::asio::ip::tcp;
using namespace boost::filesystem;

class Server
{
    public:
        Server(boost::asio::io_service& io_service, short port, short lengthMaxFile);
        void handle_accept(Session* new_session, const boost::system::error_code& error);

    private:
        boost::asio::io_service& io_service_;
        tcp::acceptor acceptor_;
        short lengthMaxFile_;
};

#endif
