#include "King.h"


King::King(detail::IChessPieceEnums::id player, int i, int j)
{
	m_type = KING;
	if (player == WHITE)
		texture.loadFromFile("Data/Sprites/whiteCheckers/king.png");
	else if (player == BLACK)
		texture.loadFromFile("Data/Sprites/blackCheckers/king.png");
	m_sprite.setTexture(texture);
	m_sprite.setPosition(sf::Vector2f(j * 70, i * 70));
	m_id = player;
}


King::~King()
{
}

void King::draw(sf::RenderWindow *win)const
{
	win->draw(m_sprite);
}

void King::ChangePosition(sf::Vector2f nextPosition)
{
	m_sprite.setPosition(nextPosition);
}