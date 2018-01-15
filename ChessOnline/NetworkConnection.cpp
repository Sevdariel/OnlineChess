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
	//std::cout << "checkfirst" << std::endl;
	ConvertIntArrayToChar(array);
	//std::cout << "checksecond" << std::endl;
	for (int i = 0; i < 8; i++)
	{
		//std::cout << "check" << i << std::endl;
		send(SSocket, charArray[i], 8, 0);
	}
	//send(SSocket, *charArray, sizeof(array[8][8]), 0);
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
void NetworkConnection::ConvertIntArrayToChar(int arr[8][8])
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (arr[i][j] == 0)
				charArray[i][j] = '0';
			else if (arr[i][j] == 1)
				charArray[i][j] = '1';
			else if (arr[i][j] == 2)
				charArray[i][j] = '2';
			else if (arr[i][j] == 3)
				charArray[i][j] = '3';
			else if (arr[i][j] == 4)
				charArray[i][j] = '4';
			else if (arr[i][j] == 5)
				charArray[i][j] = '5';
			else if (arr[i][j] == 6)
				charArray[i][j] = '6';
			else if (arr[i][j] == 11)
				charArray[i][j] = 'z';
			else if (arr[i][j] == 12)
				charArray[i][j] = 'y';
			else if (arr[i][j] == 13)
				charArray[i][j] = 'w';
			else if (arr[i][j] == 14)
				charArray[i][j] = 'x';
			else if (arr[i][j] == 15)
				charArray[i][j] = 't';
			else if (arr[i][j] == 16)
				charArray[i][j] = 'v';
		}
	std::cout << &charArray[0] << std::endl;
}
//storing buf sign
void NetworkConnection::StoreFirstSign(char buf[50])
{
	bufSign = buf[0];
	std::cout << bufSign << std::endl;
}
