#include "Queen.h"


Queen::Queen(detail::IChessPieceEnums::id player, int i, int j)
{
	m_type = QUEEN;
	if (player == WHITE)
		texture.loadFromFile("Data/Sprites/whiteCheckers/queen.png");
	else if (player == BLACK)
		texture.loadFromFile("Data/Sprites/blackCheckers/queen.png");
	m_sprite.setTexture(texture);
	m_sprite.setPosition(sf::Vector2f(j * 70, i * 70));
	m_id = player;
}


Queen::~Queen()
{
}

void Queen::draw(sf::RenderWindow *win)const
{
	win->draw(m_sprite);
}

void Queen::ChangePosition(sf::Vector2f nextPosition)
{
	m_sprite.setPosition(nextPosition);
}