//
// async_tcp_echo_server.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2008 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem/fstream.hpp>
#include "server.h"

using boost::asio::ip::tcp;
using namespace boost::filesystem;



int main(int argc, char* argv[])
{
  try
  {
    if (argc != 3)
    {
      std::cerr << "Usage: Stream server <port> <Length max file save>\n";
      return 1;
    }

    boost::asio::io_service io_service;

    using namespace std; // For atoi.
    Server s(io_service, atoi(argv[1]), atoi(argv[2]));

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
  return 0;
}
