#pragma once
#include "ChessPiece.h"

class Knight : public ChessPiece
{
public:
	explicit Knight(detail::IChessPieceEnums::id player, int i, int j);
	~Knight();
	void HighlightPossibleMove(int arr[8][8], std::vector<sf::RectangleShape> &square);

	void draw(sf::RenderWindow *win)const;
	void ChangePosition(sf::Vector2f nextPosition);
	sf::Texture texture;
};
