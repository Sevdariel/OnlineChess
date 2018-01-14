#include "Board.h"

Board::Board()
{
	LoadChessBoard();
	MakeChessBoard();
	LoadChessPiecePos();
}


Board::~Board()
{
}

//loading chess board black/white fields position
void Board::LoadChessBoard()
{
	std::ifstream board("Data/TextFiles/ChessBoard.txt");
	if (board.good())
	{
		std::cout << "Board file loaded properly" << std::endl;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				board >> chessBoard[i][j];
			}
	}
	else
		std::cout << "Couldn't load board file" << std::endl;
}
//creating chess board
void Board::MakeChessBoard()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (chessBoard[i][j] == 0)
			{
				square.push_back(sf::RectangleShape(sf::Vector2f(70, 70)));
				square[k].setPosition(sf::Vector2f(j * 70, i * 70));
				square[k].setFillColor(sf::Color::White);
				k++;
			}
			else if (chessBoard[i][j] == 1)
			{
				square.push_back(sf::RectangleShape(sf::Vector2f(70, 70)));
				square[k].setPosition(sf::Vector2f(j * 70, i * 70));
				square[k].setFillColor(sf::Color(105, 105, 105));
				k++;
			}
		}
}
//drawing chess board
void Board::draw(sf::RenderWindow *win)
{
	for (auto squares : square)
		win->draw(squares);
}
//loading chess pieces position to chessPiecePos
void Board::LoadChessPiecePos()
{
	std::ifstream chessPiece("Data/TextFiles/ChessPiecePos.txt");
	if (chessPiece.good())
	{
		std::cout << "PiecePos file loaded properly" << std::endl;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				chessPiece >> chessPiecePos[i][j];
			}
	}
	else
		std::cout << "Couldn't load piecepos file" << std::endl;
}