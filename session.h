#ifndef __session_h__
#define __session_h__

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem/fstream.hpp>

using boost::asio::ip::tcp;
using namespace boost::filesystem;

class Session
{
	private:
        tcp::socket socket_;
        enum { max_length = 1024 };
        char data_[max_length];
        int streamLength = 0;
        char streamPath[32];
        ofstream streamFile;
        short lengthMaxFile_ = 0 ;
  
    public:
        Session(boost::asio::io_service& io_service, short lengthMaxFile);
        tcp::socket& socket();
        void generatePath();
        void start();
        void handle_read(const boost::system::error_code& error,
            size_t bytes_transferred);
        void handle_write(const boost::system::error_code& error);

};

#endif