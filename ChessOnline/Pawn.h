#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
	explicit Pawn(detail::IChessPieceEnums::id player, int i, int j);
	~Pawn();

	void HighlightPossibleMove(int arr[8][8], std::vector<sf::RectangleShape> &square);
	void draw(sf::RenderWindow *win)const;
	void ChangePosition(sf::Vector2f nextPosition);
	

private:
	sf::Texture texture;
	bool moved = false;
};

