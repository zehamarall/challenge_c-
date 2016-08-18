#include "session.h"

Session::Session(boost::asio::io_service& io_service, short lengthMaxFile)
    : socket_(io_service), lengthMaxFile_(lengthMaxFile), streamLength(0), streamPath()
    {
        generatePath();
    }

tcp::socket& Session::socket()
{
    return socket_;
}

void Session::generatePath()
{
    std::time_t now = std::time(NULL);
    std::strftime(streamPath, 32, "%d_%m_%Y-%H:%M:%S", std::localtime(&now));
}

void Session::start()
{
    socket_.async_read_some(boost::asio::buffer(data_, max_length),
        boost::bind(&Session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));
}

void Session::handle_read(const boost::system::error_code& error,
    size_t bytes_transferred)
{
    if (!error) {
        streamLength += bytes_transferred;

        if (streamLength > lengthMaxFile_) {
            generatePath();
            streamLength = 0;
        }

        streamFile.open(streamPath, std::ios::app | std::ios::binary);
        streamFile << data_;
        streamFile.close();     

        boost::asio::async_write(socket_,
            boost::asio::buffer("OK", bytes_transferred),
            boost::bind(&Session::handle_write, this,
            boost::asio::placeholders::error));
    } else {
        delete this;
    }
}

void Session::handle_write(const boost::system::error_code& error)
{
    if (!error) {
            socket_.async_read_some(boost::asio::buffer(data_, max_length),
            boost::bind(&Session::handle_read, this,
            boost::asio::placeholders::error,
            boost::asio::placeholders::bytes_transferred));            
    } else {
        delete this;
    }
}