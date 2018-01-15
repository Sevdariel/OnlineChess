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
	if (player == WHITE)
		m_direction = UP;
	else if (player == BLACK)
		m_direction = DOWN;
	xArrayPosition = i;
	yArrayPosition = j;
}


Pawn::~Pawn()
{
}
void Pawn::HighlightPossibleMove(int arr[8][8], std::vector<sf::RectangleShape> &square)
{
	for (int i = 0; i < square.size(); i++)
	{
			if (square[i].getPosition().x == m_sprite.getPosition().x &&
				square[i].getPosition().y == m_sprite.getPosition().y)
			{
				square[i].setOutlineThickness(-6);
				square[i].setOutlineColor(sf::Color::Yellow);
			}
			if (arr[xArrayPosition + m_direction][yArrayPosition] == 0 &&
				square[i].getPosition().x == yArrayPosition * 70 &&
				square[i].getPosition().y == (xArrayPosition + m_direction) * 70)
			{
				square[i].setOutlineThickness(-6);
				square[i].setOutlineColor(sf::Color::Yellow);
			}
			if (arr[xArrayPosition + 2*m_direction][yArrayPosition] == 0 &&
				square[i].getPosition().x == yArrayPosition * 70 &&
				square[i].getPosition().y == (xArrayPosition + 2*m_direction) * 70 &&
				!moved)
			{
				square[i].setOutlineThickness(-6);
				square[i].setOutlineColor(sf::Color::Yellow);
			}
	}
	
}
//pawn draw method
void Pawn::draw(sf::RenderWindow *win)const
{
	win->draw(m_sprite);
}
//pawn new position
void Pawn::ChangePosition(sf::Vector2f nextPosition)
{
	if (!moved)
		moved = true;
	m_sprite.setPosition(nextPosition);
}


