#include <iostream>
#include <WS2tcpip.h>
#include <string>
#include <thread>
#include <sstream>

#pragma comment (lib, "ws2_32.lib")

using namespace std;
int x = 1;
void main()
{
	// Initialze winsock
	WSADATA wsData;
	WORD ver = MAKEWORD(2, 2);

	int wsOk = WSAStartup(ver, &wsData);
	if (wsOk != 0)
	{
		cerr << "Can't Initialize winsock! Quitting" << endl;
		return;
	}

	// Create a socket
	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET)
	{
		cerr << "Can't create a socket! Quitting" << endl;
		return;
	}

	// Bind the ip address and port to a socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(54000);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton .... 

	bind(listening, (sockaddr*)&hint, sizeof(hint));

	// Tell Winsock the socket is for listening 
	listen(listening, SOMAXCONN);
	cout << "Leader Truck is now Listening" << endl;
	// Create the master file descriptor set and zero it
	fd_set master;
	FD_ZERO(&master);

	// Add our first socket that we're interested in interacting with; the listening socket!
	// It's important that this socket is added for our server or else we won't 'hear' incoming
	// connections 
	FD_SET(listening, &master);

	// this will be changed by the \quit command (see below, bonus not in video!)
	bool running = true;

	while (running)
	{
		// Make a copy of the master file descriptor set, this is SUPER important because
		// the call to select() is _DESTRUCTIVE_. The copy only contains the sockets that
		// are accepting inbound connection requests OR messages. 

		// E.g. You have a server and it's master file descriptor set contains 5 items;
		// the listening socket and four clients. When you pass this set into select(), 
		// only the sockets that are interacting with the server are returned. Let's say
		// only one client is sending a message at that time. The contents of 'copy' will
		// be one socket. You will have LOST all the other sockets.

		// SO MAKE A COPY OF THE MASTER LIST TO PASS INTO select() !!!

		fd_set copy = master;

		// See who's talking to us
		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		// Loop through all the current connections / potential connect
		for (int i = 0; i < socketCount; i++)
		{
			// Makes things easy for us doing this assignment
			SOCKET sock = copy.fd_array[i];

			// Is it an inbound communication?
			if (sock == listening)
			{
				// Accept a new connection
				SOCKET client;
				wprintf(L"Waiting for a new Truck to connect...\n"); 
				client = accept(listening, NULL, NULL);
				if (client == INVALID_SOCKET) {
					wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
					closesocket(listening);
					WSACleanup();
					return;
				}
				else {

					wprintf(L"Truck number %lu connected.\n", (unsigned long)client);
				}
					
				

				// Add the new connection to the list of connected clients
				FD_SET(client, &master);

				// Send a welcome message to the connected client

				ostringstream s;
				s << "from leader > Hi Truck # " << x << " with ID # " << client << " Welcome to the platoon!\r\n";
				string strOut = s.str();

				
				send(client, strOut.c_str(), strOut.size() + 1, 0);
				x++;
			}
			else // It's an inbound message
			{
				char buf[4096];
				ZeroMemory(buf, 4096);

				// Receive message
				int bytesIn = recv(sock, buf, 4096, 0);
				
				if (bytesIn <= 0)
				{
					// Drop the client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
					std::string buf2 = buf;
					// Is the command quit? 
					if (buf2 == "quit" || buf2 == "drop")
					{
						
						
						if (buf2 == "quit")
						{
							running = false;
							break;
						}
						if (buf2 == "drop")
						{
							// Drop the client
							closesocket(sock);
							FD_CLR(sock, &master);
							cout << "Truck # " << sock << " dropped from the platoon\n\r";
						}
						/*if (buf2 == "speed")
						{

							std::thread t1([](FD_SET master, SOCKET sock) {
								for (int i = 0; i < master.fd_count; i++)
								{
									SOCKET outSock2 = master.fd_array[i];
									int f = 120;
									if (outSock2 == sock)
									{
										ostringstream m;
										m << "from leader > Hi Truck # " << sock << " my speed is " << "\r\n";
										string strOut2 = m.str();

										send(outSock2, strOut2.c_str(), strOut2.size() + 1, 0);
									}
								}
							}, master, sock);

							
						}*/


						//// Unknown command
						//continue;
					}
					


					buf2.erase(std::remove(buf2.begin(), buf2.end(), '\n'), buf2.end());
					ostringstream received;
					//buf.str();
					
					received << "truck # " << sock << " says : " << buf2 << "\r";
					string received_str = received.str();
					//received_str[strcspn(received_str, "\n")] = 0;
					//received_str.erase(std::remove(received_str.begin(), received_str.end(), '\n'), received_str.end());
					//strtok(received_str, "\n");

					cout << received_str << endl;
					// Check to see if it's a command. \quit kills the server
					

					// Send message to other clients, and definiately NOT the listening socket

					for (int i = 0; i < master.fd_count; i++)
					{
						SOCKET outSock = master.fd_array[i];
						if (outSock != listening && outSock != sock)
						{
							ostringstream ss;
							ss << "from leader > Truck #" << sock << " says: " << buf2 << "\r\n";
							string strOut = ss.str();

							send(outSock, strOut.c_str(), strOut.size() + 1, 0);
						}
					}
				}
			}
		}
	}

	// Remove the listening socket from the master file descriptor set and close it
	// to prevent anyone else trying to connect.
	FD_CLR(listening, &master);
	closesocket(listening);

	// Message to let users know what's happening.
	string msg = "Leader Truck is shutting down. Goodbye\r\n";

	while (master.fd_count > 0)
	{
		// Get the socket number
		SOCKET sock = master.fd_array[0];

		// Send the goodbye message
		send(sock, msg.c_str(), msg.size() + 1, 0);

		// Remove it from the master file list and close the socket
		FD_CLR(sock, &master);
		closesocket(sock);
	}

	// Cleanup winsock
	WSACleanup();

	system("pause");
}