#include "Knight.h"


Knight::Knight(detail::IChessPieceEnums::id player, int i, int j)
{
	m_type = KNIGHT;
	if (player == WHITE)
		texture.loadFromFile("Data/Sprites/whiteCheckers/knight.png");
	else if (player == BLACK)
		texture.loadFromFile("Data/Sprites/blackCheckers/knight.png");
	m_sprite.setTexture(texture);
	m_sprite.setPosition(sf::Vector2f(j * 70, i * 70));
	m_id = player;
}


Knight::~Knight()
{
}

void Knight::draw(sf::RenderWindow *win)const
{
	win->draw(m_sprite);
}

void Knight::ChangePosition(sf::Vector2f nextPosition)
{
	m_sprite.setPosition(nextPosition);
}