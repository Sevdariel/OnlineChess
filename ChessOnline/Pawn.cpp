#include "Pawn.h"

//creating pawn
Pawn::Pawn(detail::IChessPieceEnums::id player, int i, int j)
{
	//setting chess piece type
	m_type = PAWN;
	//setting chess piece color
	if (player == WHITE)
		texture.loadFromFile("Data/Sprites/whiteCheckers/pawn.png");
	else if (player == BLACK)
		texture.loadFromFile("Data/Sprites/blackCheckers/pawn.png");
	//setting texture to sprite
	m_sprite.setTexture(texture);
	//setting sprite position
	m_sprite.setPosition(sf::Vector2f(j * 70, i * 70));
	m_id = player;
}


Pawn::~Pawn()
{
}
//pawn draw method
void Pawn::draw(sf::RenderWindow *win)const
{
	win->draw(m_sprite);
}
//pawn new position
void Pawn::ChangePosition(sf::Vector2f nextPosition)
{
	m_sprite.setPosition(nextPosition);
}