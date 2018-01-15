#pragma once
#include "ChessPiece.h"

class King : public ChessPiece
{
public:
	explicit King(detail::IChessPieceEnums::id player, int i, int j);
	~King();
	void HighlightPossibleMove(int arr[8][8], std::vector<sf::RectangleShape> &square);

	void draw(sf::RenderWindow *win)const;
	void ChangePosition(sf::Vector2f nextPosition);
	sf::Texture texture;
};
