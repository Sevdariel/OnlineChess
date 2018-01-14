#include "Bishop.h"


Bishop::Bishop(detail::IChessPieceEnums::id player, int i, int j)
{
	m_type = BISHOP;
	if (player == WHITE)
		texture.loadFromFile("Data/Sprites/whiteCheckers/bishop.png");
	else if (player == BLACK)
		texture.loadFromFile("Data/Sprites/blackCheckers/bishop.png");
	m_sprite.setTexture(texture);
	m_sprite.setPosition(sf::Vector2f(j * 70, i * 70));
	m_id = player;
}


Bishop::~Bishop()
{
}

void Bishop::draw(sf::RenderWindow *win)const
{
	win->draw(m_sprite);
}
void Bishop::ChangePosition(sf::Vector2f nextPosition)
{
	m_sprite.setPosition(nextPosition);
}