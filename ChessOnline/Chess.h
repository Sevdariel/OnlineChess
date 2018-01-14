#pragma once
#include <SFML\Graphics.hpp>
//#include <Windows.h>

#include "Board.h"
#include "ChessPiece.h"
#include "NetworkConnection.h"

class Chess
{
public:
	Chess(sf::RenderWindow &win, NetworkConnection &netCon);
	~Chess();

	bool Run();

private:
	NetworkConnection *networkConnection;
	sf::RenderWindow *window;
	bool exit;
	bool picked;
	int playerTurn = 1;
	int arrayPosX, arrayPosY, prevArrayPosX, prevArrayPosY;
	int tempPiece;
	Board chessBoard;
	ChessPiece* selectedPiece = 0;
	//white chess pieces
	std::vector<ChessPiece*> whitePieces;
	//black chess pieces
	std::vector<ChessPiece*> blackPieces;

	void MouseEvent(sf::Vector2f mouse);
	void Draw();
	void DrawChessPieces();
	void CreatePieces();
	sf::Vector2f CalculateProperPosition(sf::Vector2f mouse);
	void CalculateArrayPosition(sf::Vector2f mouse);
};

