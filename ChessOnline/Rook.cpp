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
	xArrayPosition = i;
	yArrayPosition = j;
}


Rook::~Rook()
{
}

void Rook::HighlightPossibleMove(int arr[8][8], std::vector<sf::RectangleShape>& square)
{
	for (int i = 0; i < square.size(); i++)
	{
		if (square[i].getPosition() == m_sprite.getPosition())
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		for (int k = xArrayPosition - 1; k >= 0; k--)
		{
			if (arr[k][yArrayPosition] == 0 &&
				square[i].getPosition().y == k * 70 &&
				square[i].getPosition().x == yArrayPosition * 70)
			{
				square[i].setOutlineThickness(-6);
				square[i].setOutlineColor(sf::Color::Yellow);
			}
			else if (arr[k][yArrayPosition] != 0)
				break;
		}
		for (int k = xArrayPosition + 1; k < 8 ; k++)
		{
			if (arr[k][yArrayPosition] == 0 &&
				square[i].getPosition().y == k * 70 &&
				square[i].getPosition().x == yArrayPosition * 70)
			{
				square[i].setOutlineThickness(-6);
				square[i].setOutlineColor(sf::Color::Yellow);
			}
			else if (arr[k][yArrayPosition] != 0)
				break;
		}
		for (int k = yArrayPosition - 1; k >= 0; k--)
		{
			if (arr[xArrayPosition][k] == 0 &&
				square[i].getPosition().x == k * 70 &&
				square[i].getPosition().y == xArrayPosition * 70)
			{
				square[i].setOutlineThickness(-6);
				square[i].setOutlineColor(sf::Color::Yellow);
			}
			else if (arr[xArrayPosition][k] != 0)
				break;
		}
		for (int k = yArrayPosition + 1; k < 8; k++)
		{
			if (arr[xArrayPosition][k] == 0 &&
				square[i].getPosition().x == k * 70 &&
				square[i].getPosition().y == xArrayPosition * 70)
			{
				square[i].setOutlineThickness(-6);
				square[i].setOutlineColor(sf::Color::Yellow);
			}
			else if (arr[xArrayPosition][k] != 0)
				break;
		}
	}
}

void Rook::draw(sf::RenderWindow *win)const
{
	win->draw(m_sprite);
}

void Rook::ChangePosition(sf::Vector2f nextPosition)
{
	m_sprite.setPosition(nextPosition);
}