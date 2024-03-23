
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <msclr\marshal_cppstd.h>

#include "clientFuncs.h"

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")


using namespace std;

static bool isConnected = false;
static SOCKET sock;
static struct sockaddr_in serv_name;
static int status;
static char indata[1024] = { 0 }, outdata[1024] = { 0 };

bool tcp_status(void)
{
    return isConnected;
}

bool tcp_recv(std::string& msg, std::string& errmsg)    // receive message
{
    if (!isConnected)
    {
        errmsg = "";
        return false;
    }

#if 0
    // Wait for the connection to complete
    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(sock, &readSet);

    struct timeval t;
    t.tv_sec = 1;   // 1 second
    t.tv_usec = 0;  // 0 usec
    if (select(0, NULL, &readSet, NULL, &t) == 0)
    {
        errmsg = "Connection error: time exceed 1 seconds";
        return false;
    }
#endif

    int nbytes = recv(sock, indata, sizeof(indata), 0);     // receive how many bytes

    if (nbytes == -1) {
        errno_t err;
        _get_errno(&err);

        switch (err)
        {
            case EAGAIN:
            case EWOULDBLOCK:   // no data
                return false;

            case 0:
                return false;
            default:
                return false;
        }
        
    }

    if (nbytes == 0) {

        errmsg = "Connection closed by server";

        // Set the socket back to blocking mode
        u_long iMode = 0;
        ioctlsocket(sock, FIONBIO, &iMode);

        // Close the socket
        closesocket(sock);

        WSACleanup();
        isConnected = false;

        return false;
    }
    
    indata[nbytes] = 0; // string end
    msg = indata;
    return true;

}

bool tcp_send(std::string msg, std::string& errmsg)
{
    if (!isConnected)
    {
        errmsg = "Connection did not exist";
        return false;
    }
    send(sock, msg.c_str(), msg.size(), 0);
    errmsg = "Message sent OK";

    return true;
}

bool tcp_disconnect(std::string& errmsg)
{
    if (!isConnected)
    {
        errmsg = "Connection did not exist";
        return false; 
    }

    // Set the socket back to blocking mode
    u_long iMode = 0;
    ioctlsocket(sock, FIONBIO, &iMode);

    // Close the socket
    closesocket(sock);


    WSACleanup();
    isConnected = false;
    errmsg = "Connection closed";
    return true;
}

bool tcp_connect(std::string host, int port, std::string &errmsg)
{

    if (isConnected)
    {
        errmsg = "Connection already exist";
        return true;
    }


    // init winsock
    WSADATA wsa = { 0 };
    WORD wVer = MAKEWORD(2, 2);
    WSAStartup(wVer, &wsa);
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != NO_ERROR) {
        errmsg = "Error: init winsock";
        return false;
    }

    // create a socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        errmsg = "Socket creation error";
        return false;
    }

    // server address
    serv_name.sin_family = AF_INET;
    inet_pton(AF_INET, host.c_str(), &serv_name.sin_addr);
    serv_name.sin_port = htons(port);

    // Set the socket to non-blocking mode
    u_long iMode = 1;
    ioctlsocket(sock, FIONBIO, &iMode);

    connect(sock, (struct sockaddr*)&serv_name, sizeof(serv_name));

    // Wait for the connection to complete
    fd_set writeSet;
    FD_ZERO(&writeSet);
    FD_SET(sock, &writeSet);

    struct timeval t;
    t.tv_sec = 2;   // 2 second
    t.tv_usec = 0;  // 0 usec
    if (select(0, NULL, &writeSet, NULL, &t) == 0)
    {
        errmsg = "Connection error: time exceed 2 seconds";
        return false;
    }

    isConnected = true;
    errmsg = "Connected OK";
    return true;

}