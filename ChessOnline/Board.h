#pragma once
#include <SFML\Graphics.hpp>
#include <fstream>
#include <iostream>
//#include <Windows.h>



class IPiece;

class Board
{
public:
	Board();
	~Board();

	void draw(sf::RenderWindow *win);

	//chess piece position array
	int chessPiecePos[8][8];
	std::vector<sf::RectangleShape> square;
	//std::vector<sf::RectangleShape> GetSquare();

private:
	//chess board fields
	//std::vector<sf::RectangleShape> square;
	//sf::RenderWindow *window;
	int chessBoard[8][8];
	int k = 0;

	void LoadChessBoard();
	void MakeChessBoard();
	void LoadChessPiecePos();
};
