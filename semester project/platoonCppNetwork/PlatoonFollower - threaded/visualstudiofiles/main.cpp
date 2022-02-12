/*
* Team : seniors
* Course : Distributed and parallel Systems
* Author: Omar
*/
#include <iostream>
#include <string>
#include <WS2tcpip.h>
#include <thread>

#pragma comment(lib, "ws2_32.lib")

using namespace std;
char buf[4096];
/**
*Overview : a threaded client application that can send and receive messages at the same time
* without having the issue of blocking the main thread with the send and receive functions
* we can make as much instances of this application and each application will represent a Truck
**/
void receive(SOCKET sock)
{
	ZeroMemory(buf, 4096);
	int bytesReceived = recv(sock, buf, 4096, 0);
	if (bytesReceived > 0)
	{
		// Echo response to console
		string received_msg = string(buf, 0, bytesReceived);
		cout << received_msg << endl;



	}
}


void main()
{
	string ipAddress = "129.217.103.125";			// IP Address of the server
	int port = 54000;						// Listening port # on the server

	// Initialize WinSock
	WSAData data;
	WORD ver = MAKEWORD(2, 2);
	int wsResult = WSAStartup(ver, &data);
	if (wsResult != 0)
	{
		cerr << "Can't start Winsock, Err #" << wsResult << endl;
		return;
	}

	// Create socket
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET)
	{
		cerr << "Can't create socket, Err #" << WSAGetLastError() << endl;
		WSACleanup();
		return;
	}

	// Fill in a hint structure
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

	// Connect to server
	int connResult = connect(sock, (sockaddr*)&hint, sizeof(hint));
	if (connResult == SOCKET_ERROR)
	{
		cerr << "Can't connect to server, Err #" << WSAGetLastError() << endl;
		closesocket(sock);
		WSACleanup();
		return;
	}
	//------------------------------------------------------------------------------------------------------
	// Do-while loop to send and receive data

	string userInput;
	std::thread t1([](string userInput, SOCKET sock) { while (true) {
		//cout << "> ";
		getline(cin, userInput);

		if (userInput.size() > 0)		// Make sure the user has typed in something
		{

			// Send the text

			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
		}
	}}, userInput, sock),
		t2([](SOCKET sock) { while (true) {
		ZeroMemory(buf, 4096);
		int bytesReceived = recv(sock, buf, 4096, 0);
		if (bytesReceived > 0)
		{
			// Echo response to console
			string received_msg = string(buf, 0, bytesReceived);
			cout << received_msg;



		}
	}}, sock);

	t1.join();
	t2.join(); // only necessary if t1 is not really an infinite loop
	//do
	//{
	//	//begininng:
	//	
	//	thread th1(receive, sock);
	//	begininng:
	//	// Prompt the user for some text
	//	
	//	cout << "> ";
	//	getline(cin, userInput);

	//	if (userInput.size() > 0)		// Make sure the user has typed in something
	//	{

	//		// Send the text
	//		
	//		int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
	//		if (sendResult != SOCKET_ERROR)
	//		{
	//		

	//				goto begininng;
	//			//continue;


	//		}
	//	}
	//	//th1.join();
	//} while (userInput.size() > 0);
	//----------------------------------------------------------------------------------------------------------
	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}
