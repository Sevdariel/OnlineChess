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
	xArrayPosition = i;
	yArrayPosition = j;
}


Knight::~Knight()
{
}
//highlighting possible moves
void Knight::HighlightPossibleMove(int arr[8][8], std::vector<sf::RectangleShape>& square)
{
	for (int i = 0; i < square.size(); i++)
	{
		if (square[i].getPosition() == m_sprite.getPosition())
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition - 2][yArrayPosition - 1] == 0 &&
			square[i].getPosition().x == (yArrayPosition - 1) * 70 &&
			square[i].getPosition().y == (xArrayPosition -2) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition - 2][yArrayPosition + 1] == 0 &&
			square[i].getPosition().x == (yArrayPosition + 1) * 70 &&
			square[i].getPosition().y == (xArrayPosition - 2) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition - 1][yArrayPosition + 2] == 0 &&
			square[i].getPosition().x == (yArrayPosition + 2) * 70 &&
			square[i].getPosition().y == (xArrayPosition - 1) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition + 1][yArrayPosition + 2] == 0 &&
			square[i].getPosition().x == (yArrayPosition + 2) * 70 &&
			square[i].getPosition().y == (xArrayPosition + 1) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition + 2][yArrayPosition + 1] == 0 &&
			square[i].getPosition().x == (yArrayPosition + 1) * 70 &&
			square[i].getPosition().y == (xArrayPosition + 2) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition + 2][yArrayPosition - 1] == 0 &&
			square[i].getPosition().x == (yArrayPosition - 1) * 70 &&
			square[i].getPosition().y == (xArrayPosition + 2) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition + 1][yArrayPosition - 2] == 0 &&
			square[i].getPosition().x == (yArrayPosition - 2) * 70 &&
			square[i].getPosition().y == (xArrayPosition + 1) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition - 1][yArrayPosition - 2] == 0 &&
			square[i].getPosition().x == (yArrayPosition - 2) * 70 &&
			square[i].getPosition().y == (xArrayPosition - 1) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
	}
}
//drawing sprite
void Knight::draw(sf::RenderWindow *win)const
{
	win->draw(m_sprite);
}
//changing position
void Knight::ChangePosition(sf::Vector2f nextPosition)
{
	m_sprite.setPosition(nextPosition);
}