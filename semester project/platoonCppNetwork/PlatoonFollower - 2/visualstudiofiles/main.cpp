#include <iostream>
#include <string>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

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
	char buf[4096];
	string userInput;

	do
	{
	sending:
		// Prompt the user for some text
		cout << "> ";
		getline(cin, userInput);

		if (userInput.size() > 0)		// Make sure the user has typed in something
		{

			// Send the text

			int sendResult = send(sock, userInput.c_str(), userInput.size() + 1, 0);
			if (sendResult != SOCKET_ERROR)
			{

				if (userInput == "hi" || userInput == " ")
				{
					goto recv2;
				}
				else
				{
					goto sending;
				}
				// Wait for response
			recv2:
				ZeroMemory(buf, 4096);
				int bytesReceived = recv(sock, buf, 4096, 0);
				if (bytesReceived > 0)
				{
					// Echo response to console
					string received_msg = string(buf, 0, bytesReceived);
					cout << received_msg << endl;
					if (received_msg.rfind("from leader >", 0) == 0)
					{
						goto sending;
					}

					/*if (string(buf, 0, bytesReceived) == "backward") {
						cout << "> " << "ok leader i will go backward too" << endl;
						goto receiving;
					}
					else if (string(buf, 0, bytesReceived) == "right") {
						cout << "> " << "ok leader i will go right too" << endl;
						goto receiving;
					}
					else if (string(buf, 0, bytesReceived) == "left") {
						cout << "> " << "ok leader i will go left too" << endl;
						goto receiving;
					}*/
				}


			}
		}

	} while (userInput.size() > 0);

	// Gracefully close down everything
	closesocket(sock);
	WSACleanup();
}
