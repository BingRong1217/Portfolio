#pragma once

bool server_start(int port);
bool server_stop(int port);
bool server_status(int& numCon, std::string& msg, bool& isServerStarted);