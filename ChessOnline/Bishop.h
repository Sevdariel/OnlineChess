#pragma once
#include "ChessPiece.h"

class Bishop : public ChessPiece
{
public:
	explicit Bishop(detail::IChessPieceEnums::id player, int i, int j);
	~Bishop();

	void draw(sf::RenderWindow *win)const;
	void ChangePosition(sf::Vector2f nextPosition);
	sf::Texture texture;
};
