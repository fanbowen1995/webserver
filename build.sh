#!/bin/bash

g++ main.cpp  httpconn/httpconn.cpp webserver/server.cpp httpconnhandler/httpconnhandler.cpp locker/locker.cpp -o server -lpthread -std=c++11