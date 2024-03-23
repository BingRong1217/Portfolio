#pragma once

#include <msclr\marshal_cppstd.h>

bool tcp_connect(std::string host, int port, std::string &errmsg);
bool tcp_disconnect(std::string& errmsg);
bool tcp_send(std::string msg, std::string& errmsg);
bool tcp_recv(std::string &msg, std::string& errmsg);
bool tcp_status(void);
