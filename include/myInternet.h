#ifndef MYINTERNET_H
#define MYINTERNET_H

//#define _WIN32_WINNT 1281
#include <iostream>
#include <ws2tcpip.h>
#include <thread>

void shutdownApp(SOCKET);

SOCKET StartWinsockServer(const char*);

SOCKET StartWinsockClient(const char*, const char*);

#endif // MYINTERNET_H