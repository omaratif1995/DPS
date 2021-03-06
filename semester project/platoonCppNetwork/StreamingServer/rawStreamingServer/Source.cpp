/*
* Team : seniors
* Course : Distributed and parallel Systems
* Author: Omar
*/

#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>
#include <fstream>
#include <ostream>
#include <string>
#include <thread>
// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"
using namespace std::chrono;
using namespace cv;





int __cdecl main(void)
{
	/****************** Establishing a TCP connection ******************/
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    else {
        printf("a new client is connected %d\n", WSAGetLastError());
    }

    // No longer need server socket
    closesocket(ListenSocket);


    /****************** a thread to Receive the frame from the client ******************/

    std::thread t1([](SOCKET ClientSocket) {
        Mat img;
        img = Mat::zeros(480, 640, CV_8UC1);
        int imgSize = img.total() * img.elemSize();

        uchar* iptr = img.data;
        int bytes = 0;
        int key = 0;


        //make img continuos
        if (!img.isContinuous()) {
            img = img.clone();
        }
		
		//creat a file to store the timestamps
        std::ofstream outfile;
        outfile.open("DpsServer.txt");
		
		// a counter to track the frame numbers
        int i = 1;
		
		// start the clock
        auto t0 = std::chrono::system_clock::now();
        auto nanosec = t0.time_since_epoch();
        
        while (1) {

		//Receive the fram from the Client
        if ((bytes = recv(ClientSocket, (char*)iptr, imgSize, MSG_WAITALL)) == -1) {
            printf("recv failed, received bytes = %d", bytes);
        }
		
		
		// get the time stamps after receiving the frame and write it inside the text file
        t0 = std::chrono::system_clock::now();
        nanosec = t0.time_since_epoch();
        outfile << "timestamp after receiving of frame " << i << " = " << std::chrono::duration_cast<std::chrono::milliseconds>(nanosec).count() << std::endl;

        // show the frame using the openCV imshow function
        imshow("CV Video Client", img);

        if (key = waitKey(25) >= 0) break;
		
		
		//increase the counter to next frame
		i++;
    }
    }, ClientSocket);
    
    
    //-------------------------------------------------------------------------------------------------
    
    t1.join();



    // cleanup
    closesocket(ClientSocket);
    WSACleanup();
    //outfile.close();
    return 0;
}