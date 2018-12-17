#ifndef MYINTERNET_H
#define MYINTERNET_H

#define _WIN32_WINNT 1281
#include <ws2tcpip.h>
#include <iostream>
#include "myInternet.h"

void shutdownApp(SOCKET DataSocket)
{
	std::cout << "\n---------------------------\n";
	std::cout << "END OF PROGRAM.\n\n";
	system("pause");
	shutdown(DataSocket, SD_BOTH);
	WSACleanup();
	exit(0);
}

SOCKET StartWinsockServer(const char* port)
{
    // Initialize WINSOCK
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2,2), &wsaData);

    // Create the listening socket
        SOCKET ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
    
    // Initialize the sample struct and get another filled struct of the same type and old values
        addrinfo hints, *result(0); ZeroMemory(&hints, sizeof(hints));
        hints.ai_family   = AF_INET;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_protocol = IPPROTO_TCP;
        hints.ai_flags    = AI_PASSIVE;

        getaddrinfo(0, port, &hints, &result);

    // Bind the socket to the ip and port provided by the getaddrinfo and set the listen socket's type to listen
        bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
        listen(ListenSocket, SOMAXCONN); // Only sets the type to listen ( doesn't actually listen )

    // Free unused memory
        freeaddrinfo(result);

    // Return the data socket
        return ListenSocket;
}

SOCKET StartWinsockClient(const char* ip, const char* port)
{
	// Initialize WINSOCK
		WSAData wsaData;
		WSAStartup(MAKEWORD(2,2), &wsaData) != 0;

	// Create the data socket
    	SOCKET DataSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		
	// Initialize the sample struct and get another filled struct of the same type and old values
		addrinfo hints, *result(0); ZeroMemory(&hints, sizeof(hints));
		hints.ai_family   = AF_INET;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_TCP;

		getaddrinfo(ip, port, &hints, &result);

	// Try to connect to the server ( Will forever wait until a valid connection is made )
		std::cout << "Attempting to connect to " << ip << " on port " << port << " ...";

		while(connect(DataSocket, result->ai_addr, (int)result->ai_addrlen) != 0) Sleep(1000);
		system("cls"); std::cout << "Connected!" << std::endl;
	
	// Free unused memory
		freeaddrinfo(result);

	// Return the data socket
		return DataSocket;
}

#endif