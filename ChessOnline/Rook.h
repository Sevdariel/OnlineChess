#pragma once
#include "ChessPiece.h"

class Rook : public ChessPiece
{
public:
	explicit Rook(detail::IChessPieceEnums::id player, int i, int j);
	~Rook();

	void HighlightPossibleMove(int arr[8][8], std::vector<sf::RectangleShape> &square);
	void draw(sf::RenderWindow *win)const;
	void ChangePosition(sf::Vector2f nextPosition);
	sf::Texture texture;
};
