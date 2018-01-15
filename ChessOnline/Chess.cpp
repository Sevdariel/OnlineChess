#include "Chess.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"

Chess::Chess(sf::RenderWindow &win, NetworkConnection &netCon)
{
	networkConnection = &netCon;
	window = &win;
	CreatePieces();
}


Chess::~Chess()
{
}
//Running play loop
bool Chess::Run()
{
	exit = false;
	while (!exit)
	{
		sf::Vector2f mouse(sf::Mouse::getPosition(*window));
		Draw();
		MouseEvent(mouse);

		picked = false;
	}
	return true;
}
//Handle mouse event
void Chess::MouseEvent(sf::Vector2f mouse)
{
	sf::Event event;
	while (window->pollEvent(event))
		if (event.type == sf::Event::Closed)
		{
			window->close();
			exit = true;
		}
	//player 1 move
	if (networkConnection->GetBufSign() == 'a')
	{
		playerTurn = 1;
		if (event.type == sf::Event::MouseButtonReleased &&
			event.mouseButton.button == sf::Mouse::Left)
		{
			//checking if moues button pressed contains piece
			for (auto pieces : whitePieces)
			{
				if (mouse.x >= pieces->GetPositionX() &&
					mouse.x < pieces->GetPositionX() + 70 &&
					mouse.y >= pieces->GetPositionY() &&
					mouse.y < pieces->GetPositionY() + 70)
				{	//picking chess piece
					if (!picked)
					{
						CalculateArrayPosition(mouse);
						tempPiece = chessBoard.chessPiecePos[arrayPosY][arrayPosX];
						selectedPiece = pieces;
						selectedPiece->HighlightPossibleMove(chessBoard.chessPiecePos, chessBoard.square);
						break;
					}
				}
				//putting chess picked chess piece
				else if (event.type == sf::Event::MouseButtonReleased &&
					event.mouseButton.button == sf::Mouse::Left &&
					selectedPiece != 0)
				{
					prevArrayPosX = arrayPosX;
					prevArrayPosY = arrayPosY;
					CalculateArrayPosition(mouse);
					if (chessBoard.chessPiecePos[arrayPosY][arrayPosX] == 0) //&&
					{
						if (CheckHighlightPossibleMoves(mouse))
						{
							selectedPiece->ChangePosition(CalculateProperPosition(mouse));
							picked = true;
							for (int i = 0; i < chessBoard.square.size(); i++)
								chessBoard.square[i].setOutlineThickness(0);
							chessBoard.chessPiecePos[arrayPosY][arrayPosX] = tempPiece;
							chessBoard.chessPiecePos[prevArrayPosY][prevArrayPosX] = 0;
							selectedPiece->ChangeArrayPosition(arrayPosY - prevArrayPosY, arrayPosX - prevArrayPosX);
							networkConnection->SendMessageToServer('e');
							networkConnection->ReceiveMessageFromServer();
							//networkConnection->SendChessPiecePosToServer(chessBoard.chessPiecePos);
							selectedPiece = 0;
						}
					}
				}
			}
		}
	}
	//same as above but for player 2
	else if (networkConnection->GetBufSign() == 'b')
	{
		playerTurn = 2;
		if (event.type == sf::Event::MouseButtonReleased &&
			event.mouseButton.button == sf::Mouse::Left)
			for (auto pieces : blackPieces)
				if (mouse.x >= pieces->GetPositionX() &&
					mouse.x < pieces->GetPositionX() + 70 &&
					mouse.y >= pieces->GetPositionY() &&
					mouse.y < pieces->GetPositionY() + 70)
				{
					if (!picked)
					{
						CalculateArrayPosition(mouse);
						tempPiece = chessBoard.chessPiecePos[arrayPosY][arrayPosX];
						selectedPiece = pieces;
						selectedPiece->HighlightPossibleMove(chessBoard.chessPiecePos, chessBoard.square);
						break;
					}
				}
				else if (event.type == sf::Event::MouseButtonReleased &&
					event.mouseButton.button == sf::Mouse::Left &&
					selectedPiece != 0)
				{
					prevArrayPosX = arrayPosX;
					prevArrayPosY = arrayPosY;
					CalculateArrayPosition(mouse);
					if (chessBoard.chessPiecePos[arrayPosY][arrayPosX] == 0) //&&
					{
						if (CheckHighlightPossibleMoves(mouse))
						{
							selectedPiece->ChangePosition(CalculateProperPosition(mouse));
							picked = true;
							for (int i = 0; i < chessBoard.square.size(); i++)
								chessBoard.square[i].setOutlineThickness(0);
							chessBoard.chessPiecePos[arrayPosY][arrayPosX] = tempPiece;
							chessBoard.chessPiecePos[prevArrayPosY][prevArrayPosX] = 0;
							selectedPiece->ChangeArrayPosition(arrayPosY - prevArrayPosY, arrayPosX - prevArrayPosX);
							networkConnection->SendMessageToServer('e');
							networkConnection->ReceiveMessageFromServer();
							//networkConnection->SendChessPiecePosToServer(chessBoard.chessPiecePos);
							selectedPiece = 0;
						}
					}
				}
	}
	else if (networkConnection->GetBufSign() == 'c')
		networkConnection->ReceiveMessageFromServer();
}
//drawing method
void Chess::Draw()
{
	window->clear();
	chessBoard.draw(window);
	DrawChessPieces();
	window->display();
}
//piece drawing method
void Chess::DrawChessPieces()
{
	for (auto pieces : whitePieces)
		pieces->draw(window);
	for (auto pieces : blackPieces)
		pieces->draw(window);
}
//creating pieces from chessboard.chessPiecePos
void Chess::CreatePieces()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
		{
			if (chessBoard.chessPiecePos[i][j] == 1)
				whitePieces.push_back(new Pawn(detail::IChessPieceEnums::WHITE, i, j));
			else if (chessBoard.chessPiecePos[i][j] == 2)
				whitePieces.push_back(new Rook(detail::IChessPieceEnums::WHITE, i, j));
			else if (chessBoard.chessPiecePos[i][j] == 3)
				whitePieces.push_back(new Knight(detail::IChessPieceEnums::WHITE, i, j));
			else if (chessBoard.chessPiecePos[i][j] == 4)
				whitePieces.push_back(new Bishop(detail::IChessPieceEnums::WHITE, i, j));
			else if (chessBoard.chessPiecePos[i][j] == 5)
				whitePieces.push_back(new Queen(detail::IChessPieceEnums::WHITE, i, j));
			else if (chessBoard.chessPiecePos[i][j] == 6)
				whitePieces.push_back(new King(detail::IChessPieceEnums::WHITE, i, j));
			else if (chessBoard.chessPiecePos[i][j] == 11)
				blackPieces.push_back(new Pawn(detail::IChessPieceEnums::BLACK, i, j));
			else if (chessBoard.chessPiecePos[i][j] == 12)
				blackPieces.push_back(new Rook(detail::IChessPieceEnums::BLACK, i, j));
			else if (chessBoard.chessPiecePos[i][j] == 13)
				blackPieces.push_back(new Knight(detail::IChessPieceEnums::BLACK, i, j));
			else if (chessBoard.chessPiecePos[i][j] == 14)
				blackPieces.push_back(new Bishop(detail::IChessPieceEnums::BLACK, i, j));
			else if (chessBoard.chessPiecePos[i][j] == 15)
				blackPieces.push_back(new Queen(detail::IChessPieceEnums::BLACK, i, j));
			else if (chessBoard.chessPiecePos[i][j] == 16)
				blackPieces.push_back(new King(detail::IChessPieceEnums::BLACK, i, j));

		}
}
//calculating proper position for chess pieces
sf::Vector2f Chess::CalculateProperPosition(sf::Vector2f mouse)
{
	int countX, countY;
	float properPosX = mouse.x / 70;
	float properPosY = mouse.y / 70;
	countX = properPosX;
	countY = properPosY;
	sf::Vector2f properPos(countX * 70, countY * 70);
	return properPos;
}
//calculating chess position in chessboard.chessPiecePos
void Chess::CalculateArrayPosition(sf::Vector2f mouse)
{
	arrayPosX = mouse.x / 70;
	arrayPosY = mouse.y / 70;
}

bool Chess::CheckHighlightPossibleMoves(sf::Vector2f mouse)
{
	sf::Vector2f possiblePosition = CalculateProperPosition(mouse);
	for (int i = 0; i < chessBoard.square.size(); i++)
		if (possiblePosition == chessBoard.square[i].getPosition() && 
			chessBoard.square[i].getOutlineThickness() == -6)
			return true;
	return false;
}

