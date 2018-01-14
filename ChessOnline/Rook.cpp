#include "Rook.h"


Rook::Rook(detail::IChessPieceEnums::id player, int i, int j)
{
	m_type = ROOK;
	if (player == WHITE)
		texture.loadFromFile("Data/Sprites/whiteCheckers/rook.png");
	else if (player == BLACK)
		texture.loadFromFile("Data/Sprites/blackCheckers/rook.png");
	m_sprite.setTexture(texture);
	m_sprite.setPosition(sf::Vector2f(j * 70, i * 70));
	m_id = player;
}


Rook::~Rook()
{
}

void Rook::draw(sf::RenderWindow *win)const
{
	win->draw(m_sprite);
}

void Rook::ChangePosition(sf::Vector2f nextPosition)
{
	m_sprite.setPosition(nextPosition);
}