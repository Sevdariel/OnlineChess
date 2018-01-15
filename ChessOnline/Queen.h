#pragma once
#include "ChessPiece.h"

class Queen : public ChessPiece
{
public:
	explicit Queen(detail::IChessPieceEnums::id player, int i, int j);
	~Queen();
	void HighlightPossibleMove(int arr[8][8], std::vector<sf::RectangleShape> &square);

	void draw(sf::RenderWindow *win)const;
	void ChangePosition(sf::Vector2f nextPosition);
	sf::Texture texture;
};
