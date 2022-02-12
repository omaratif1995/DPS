/*
* Team : seniors
* Course : Distributed and parallel Systems
* Author: Omar
*/



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
// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#define DEFAULT_PORT "27015"
using namespace std::chrono;
using namespace cv;

/*****************************************************************************************************************
* Overview :this is a streaming app on the <Client> side that is divided in into two sections the first establish 
* a TCP communication with a server and the second section is responsible for grabing the frames from
* the device camera sing the openCV library and send those frames over a TCP port to the server
******************************************************************************************************************/
int main()
{
	/****************** Establishing a TCP connection ******************/
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;

    int iResult;


    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // make sure to put the IP of server machine
    iResult = getaddrinfo("172.22.152.106", DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }


    /****************** a thread to Grab the Frames and send it over a TCP port******************/



    std::thread t1([](SOCKET ConnectSocket) {
        Mat img, imgGray;
        img = Mat::zeros(480, 640, CV_8UC1);
        //make it continuous
        if (!img.isContinuous()) {
            img = img.clone();
        }
		


        VideoCapture cap(1);
        int imgSize = img.total() * img.elemSize();
        int bytes = 0;
        int key;
        make img continuos
        if (!img.isContinuous()) {
           img = img.clone();
           imgGray = img.clone();
        }
		//creat a file to store the timestamps
        std::ofstream outfile;
        outfile.open("DpsClient.txt");
		// a counter to track the frame numbers
        int i = 1;
		// start the clock
        auto t0 = std::chrono::system_clock::now();
        auto nanosec = t0.time_since_epoch();
        while (1) {

            /* get a frame from camera */
            cap >> img;

            // do video processing here 
            cvtColor(img, imgGray, COLOR_BGR2GRAY);
            flip(imgGray, imgGray, 1);
			// put the content of the mat file into a pointer
            uchar* iptr = img.data;
			// get the time stamps before sending the frame and write it inside the text file
            t0 = std::chrono::system_clock::now();
            nanosec = t0.time_since_epoch();
            outfile << "timestamp before sending of frame " << i << " = " << std::chrono::duration_cast<std::chrono::milliseconds>(nanosec).count() << std::endl;
			// send the Frame
            if ((bytes = send(ConnectSocket, (char*)iptr, imgSize, 0)) < 0) {
                std::cerr << "bytes = " << bytes << std::endl;
                break;
            }
			//increase the counter to next frame
            i++;
        }
        }, ConnectSocket);


    //-------------------------------------------------------------------------------------------------
	
	//make sure that the thread is done before continuing
    t1.join();

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}