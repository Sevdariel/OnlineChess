#pragma once
#include "ChessPiece.h"

class Pawn : public ChessPiece
{
public:
	explicit Pawn(detail::IChessPieceEnums::id player, int i, int j);
	~Pawn();

	void draw(sf::RenderWindow *win)const;
	void ChangePosition(sf::Vector2f nextPosition);
	sf::Texture texture;
};

