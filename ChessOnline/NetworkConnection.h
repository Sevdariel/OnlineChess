#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

class NetworkConnection
{
public:
	NetworkConnection();
	~NetworkConnection();



	void SendMessageToServer(char sign);
	void ReceiveMessageFromServer();
	void SendChessPiecePosToServer(int array[8][8]);
	//void ReceiveChessPiecePosFromServer();
	void CloseSocket();
	char GetBufSign();
	char charArray[8][8];
	void ConvertIntArrayToChar(int arr[8][8]);
private:
	WORD WRequiredVersion;
	WSADATA WData;
	SOCKET SSocket;
	int nConnect;
	int nBytes;
	struct sockaddr_in serverAddr;
	struct hostent* lpstServerEnt;
	char cbBuf[50];
	//first sign from received message
	char bufSign;
	//char charArray[8][8];

	
	void StoreFirstSign(char buf[50]);
};

