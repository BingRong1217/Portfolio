
#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <thread>
#include <vector>
#include <windows.h>

#include <msclr\marshal_cppstd.h>

#include "serverFuncs.h"

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define MAX_CONNECTIONS 100

typedef struct {
    bool isUsed;
    HANDLE handle;          // thread ID
    SOCKET clientSocket;    // data soket ID
} Connection_Ctrl;

static bool isStarted = false;
static int numConnections = 0;

static int port;
SOCKET listenSocket;
SOCKADDR_IN serverAddr;

HANDLE hServerThread;
Connection_Ctrl connections[MAX_CONNECTIONS];

static std::string statusmsg;
static bool isNewLog = false;

// Declare and initialize a global critical section object
static CRITICAL_SECTION cs;

static Connection_Ctrl* getFreeConnection(void)
{
    if (numConnections >= MAX_CONNECTIONS)
        return NULL;

    for (int i = 0; i < MAX_CONNECTIONS; i++)
        if (connections[i].isUsed == false) {
            connections[i].isUsed = true;
            return &connections[i];
        }

    return NULL;
}

static void deleteAllConnections(void)
{
    for (int i = 0; i < MAX_CONNECTIONS; i++)
        if (connections[i].isUsed == true) {
            connections[i].isUsed = false;

            shutdown(connections[i].clientSocket, SD_BOTH); // Notify the client that the socket is closed
            closesocket(connections[i].clientSocket);
            TerminateThread(connections[i].handle, 0);
        }

    numConnections = 0;
}

static void deleteConnection(SOCKET sock)
{
    for (int i = 0; i < MAX_CONNECTIONS; i++) {

        if (connections[i].isUsed == true && connections[i].clientSocket == sock) {
            connections[i].isUsed = false;
            shutdown(connections[i].clientSocket, SD_BOTH); // Notify the client that the socket is closed
            closesocket(connections[i].clientSocket);
            numConnections--;

            TerminateThread(connections[i].handle, 0);

            return;
        }
    }
}

static void do_log(std::string log)    // store server status message waiting for UI timer to retrieve and show
{
    // Enter the critical section
    EnterCriticalSection(&cs);

    statusmsg += ">> ";
    statusmsg += log;
    isNewLog = true;

    // Leave the critical section
    LeaveCriticalSection(&cs);
}

static bool get_log(std::string &msg)    // retrieve stored server status message
{
    if (isNewLog)
    {
        // Enter the critical section
        EnterCriticalSection(&cs);

        msg = statusmsg;
        statusmsg = "";
        isNewLog = false;
        // Leave the critical section
        LeaveCriticalSection(&cs);

        return true;
    }
    else
        return false;
}

DWORD WINAPI connectionProc(LPVOID lpParam) {       // thread for a new connection
    SOCKET clientSocket = (SOCKET)lpParam;
    char rcv_buffer[1024], snd_buffer[1024];
    int n;
    char logmsg[1024];

    numConnections++;
    while ((n = recv(clientSocket, rcv_buffer, sizeof(rcv_buffer), 0)) > 0) {   // run until connection close or server stop
        rcv_buffer[n] = 0;
        sprintf(logmsg, "Message received (socket id=%llu): %s\n", clientSocket, rcv_buffer);
        do_log(logmsg);
        sprintf(snd_buffer, "Server echo>> %s", rcv_buffer);
        send(clientSocket, snd_buffer, strlen(snd_buffer), 0);
    }

    sprintf(logmsg, "Connection closed, socket id=%llu\n", clientSocket);
    do_log(logmsg);

    deleteConnection(clientSocket); // close socket and delete this thread

    return 0;
}


DWORD WINAPI serverProc(LPVOID lpParameter) {
    // init winsock
    WSADATA wsa = { 0 };
    WORD wVer = MAKEWORD(2, 2);
    WSAStartup(wVer, &wsa);
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != NO_ERROR) {
        do_log("Error: init winsock\n");
        WSACleanup();
        return 1;
    }

    // Create a TCP socket
    listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenSocket == INVALID_SOCKET) {
        do_log("Socket creation error\n");
        WSACleanup();
        return 1;
    }

    // Bind the socket to a local address and port
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(port);
    if (bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        do_log("Binding error\n");
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    char my_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &serverAddr.sin_addr, my_ip, sizeof(my_ip));
    char tmp[128];
    sprintf(tmp, "Server start at: %s:%d\n", my_ip, port);
    do_log(tmp);

    // Listen for incoming connections
    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
        do_log("Listening error\n");
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }
    do_log("Wait for connection...\n");

    isStarted = true;

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t addrlen = sizeof(client_addr);

        SOCKET clientSocket = accept(listenSocket, (struct sockaddr*)&client_addr, &addrlen);
        if (clientSocket == INVALID_SOCKET) {
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        char client_ip[INET_ADDRSTRLEN];
        char tmp[128];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
        sprintf(tmp, "Connected by %s:%d, socket id=%llu\n", client_ip, ntohs(client_addr.sin_port), clientSocket);
        do_log(tmp);

        Connection_Ctrl*con = getFreeConnection();
        con->clientSocket = clientSocket;
        con->handle = CreateThread(NULL, 0, connectionProc, (LPVOID)clientSocket, 0, NULL);
    }

    return 0;
}


bool server_status(int &numCon, std::string& msg, bool &isServerStarted)
{
    isServerStarted = isStarted;
    numCon = numConnections;
    return get_log(msg);
}

bool server_start(int tcpport)
{
    port = tcpport;

    if (isStarted)  // already started
        return false;

    // Initialize the critical section object
    InitializeCriticalSection(&cs);

    for ( int i=0 ; i < MAX_CONNECTIONS ;  i++ )
        connections[i].isUsed = false;

    // Create a new thread
    hServerThread = CreateThread(NULL, 0, serverProc, NULL, 0, NULL);

    return true;
}

bool server_stop(int tcpport)
{
    port = tcpport;

    if (!isStarted)  // not started
        return false;

    // Close the thread handle
    TerminateThread(hServerThread, 0);
    isStarted = false;

    deleteAllConnections();

    // Close the server socket
    closesocket(listenSocket);
    WSACleanup();

    do_log("Server stopped\n");
    numConnections = 0;

    return true;
}
