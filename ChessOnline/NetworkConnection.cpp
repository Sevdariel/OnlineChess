#include "NetworkConnection.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
//connecting to server
NetworkConnection::NetworkConnection()
{
	WRequiredVersion = MAKEWORD(4, 0);
	if (WSAStartup(WRequiredVersion, &WData) != 0)
	{
		std::cout << "WSAStartup failed\n";
		exit(1);
	}

	lpstServerEnt = gethostbyname("127.0.0.1");
	if (!lpstServerEnt)
	{
		std::cout << "Cant get server ip address\n";
		exit(2);
	}

	SSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	memset(&serverAddr, 0, sizeof(struct sockaddr));
	serverAddr.sin_family = AF_INET;
	memcpy(&serverAddr.sin_addr.s_addr, lpstServerEnt->h_addr, lpstServerEnt->h_length);
	serverAddr.sin_port = htons(9876);

	nConnect = connect(SSocket, (struct sockaddr*)&serverAddr, sizeof(struct sockaddr));
	if (nConnect < 0)
	{
		std::cout << "Cant connect to server\n";
		exit(3);
	}
}


NetworkConnection::~NetworkConnection()
{
}
//sending message to server
void NetworkConnection::SendMessageToServer(char sign)
{
	send(SSocket, &sign, sizeof(sign), 0);
}
//receving message from server
void NetworkConnection::ReceiveMessageFromServer()
{
	nBytes = recv(SSocket, cbBuf, sizeof(cbBuf), 0);
	StoreFirstSign(cbBuf);

	cbBuf[nBytes] = '\x0';
	std::cout << cbBuf << std::endl;
}
//Sending chess piece position array to server
void NetworkConnection::SendChessPiecePosToServer(int array[8][8])
{

}
//closing socket
void NetworkConnection::CloseSocket()
{
	closesocket(SSocket);
	WSACleanup();
}
//getting buf sign
char NetworkConnection::GetBufSign()
{
	return bufSign;
}
//storing buf sign
void NetworkConnection::StoreFirstSign(char buf[50])
{
	bufSign = buf[0];
	std::cout << bufSign << std::endl;
}
