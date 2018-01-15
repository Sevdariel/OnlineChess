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
	xArrayPosition = i;
	yArrayPosition = j;
}


King::~King()
{
}

void King::HighlightPossibleMove(int arr[8][8], std::vector<sf::RectangleShape>& square)
{
	for (int i = 0; i < square.size(); i++)
	{
		if (square[i].getPosition().x == m_sprite.getPosition().x &&
			square[i].getPosition().y == m_sprite.getPosition().y)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition - 1][yArrayPosition - 1] == 0 &&
			square[i].getPosition().x == (yArrayPosition - 1)* 70 &&
			square[i].getPosition().y == (xArrayPosition - 1) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition - 1][yArrayPosition] == 0 &&
			square[i].getPosition().x == (yArrayPosition) * 70 &&
			square[i].getPosition().y == (xArrayPosition - 1) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition - 1][yArrayPosition + 1] == 0 &&
			square[i].getPosition().x == (yArrayPosition + 1) * 70 &&
			square[i].getPosition().y == (xArrayPosition - 1) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition][yArrayPosition + 1] == 0 &&
			square[i].getPosition().x == (yArrayPosition + 1) * 70 &&
			square[i].getPosition().y == (xArrayPosition) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition + 1][yArrayPosition + 1] == 0 &&
			square[i].getPosition().x == (yArrayPosition + 1) * 70 &&
			square[i].getPosition().y == (xArrayPosition + 1) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition + 1][yArrayPosition] == 0 &&
			square[i].getPosition().x == (yArrayPosition) * 70 &&
			square[i].getPosition().y == (xArrayPosition + 1) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition + 1][yArrayPosition - 1] == 0 &&
			square[i].getPosition().x == (yArrayPosition - 1) * 70 &&
			square[i].getPosition().y == (xArrayPosition + 1) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		if (arr[xArrayPosition][yArrayPosition - 1] == 0 &&
			square[i].getPosition().x == (yArrayPosition - 1) * 70 &&
			square[i].getPosition().y == (xArrayPosition) * 70)
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
	}
}

void King::draw(sf::RenderWindow *win)const
{
	win->draw(m_sprite);
}

void King::ChangePosition(sf::Vector2f nextPosition)
{
	m_sprite.setPosition(nextPosition);
}