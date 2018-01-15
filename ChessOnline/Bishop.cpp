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
	xArrayPosition = i;
	yArrayPosition = j;
}


Bishop::~Bishop()
{
}

void Bishop::HighlightPossibleMove(int arr[8][8], std::vector<sf::RectangleShape>& square)
{
	for (int i = 0; i < square.size(); i++)
	{
		if (square[i].getPosition() == m_sprite.getPosition())
		{
			square[i].setOutlineThickness(-6);
			square[i].setOutlineColor(sf::Color::Yellow);
		}
		int count = 0;
		bool blocked = false;
		for (int k = xArrayPosition - 1 - count; k >= 0; k--)
		{
			for (int l = yArrayPosition - 1 - count; l >= 0; l--)
			{
				if (arr[k][l] == 0 &&
					square[i].getPosition().y == k * 70 &&
					square[i].getPosition().x == l * 70)
				{
					square[i].setOutlineThickness(-6);
					square[i].setOutlineColor(sf::Color::Yellow);
					break;
				}
				else if (arr[k][l] != 0)
				{
					blocked = true;
					break;
				}
				else break;
			}
			count++;
			if (blocked)
				break;
		}
		count = 0;
		blocked = false;
		for (int k = xArrayPosition - 1 - count; k >= 0; k--)
		{
			for (int l = yArrayPosition + 1 + count; l < 8; l++)
			{
				if (arr[k][l] == 0 &&
					square[i].getPosition().y == k * 70 &&
					square[i].getPosition().x == l * 70)
				{
					square[i].setOutlineThickness(-6);
					square[i].setOutlineColor(sf::Color::Yellow);
					break;
				}
				else if (arr[k][l] != 0)
				{
					blocked = true;
					break;
				}
				else break;
			}
			count++;
			if (blocked)
				break;
		}
		count = 0;
		blocked = false;
		for (int k = xArrayPosition + 1 + count; k < 8; k++)
		{
			for (int l = yArrayPosition - 1 - count; l >= 0; l--)
			{
				if (arr[k][l] == 0 &&
					square[i].getPosition().x == l * 70 &&
					square[i].getPosition().y == k * 70)
				{
					square[i].setOutlineThickness(-6);
					square[i].setOutlineColor(sf::Color::Yellow);
					break;
				}
				else if (arr[k][l] != 0)
				{
					blocked = true;
					break;
				}
				else break;
			}
			count++;
			if (blocked)
				break;
		}
		count = 0;
		blocked = false;
		for (int k = xArrayPosition + 1 + count; k < 8; k++)
		{
			for (int l = yArrayPosition + 1 + count; l < 8; l++)
			{
				if (arr[k][l] == 0 &&
					square[i].getPosition().x == l * 70 &&
					square[i].getPosition().y == k * 70)
				{
					square[i].setOutlineThickness(-6);
					square[i].setOutlineColor(sf::Color::Yellow);
					break;
				}
				else if (arr[k][l] != 0)
				{
					blocked = true;
					break;
				}
				else break;
			}
			count++;
			if (blocked)
				break;
		}
	}
}

void Bishop::draw(sf::RenderWindow *win)const
{
	win->draw(m_sprite);
}
void Bishop::ChangePosition(sf::Vector2f nextPosition)
{
	m_sprite.setPosition(nextPosition);
}