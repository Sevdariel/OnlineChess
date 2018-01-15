#include "ChessPiece.h"


detail::IChessPieceEnums::type ChessPiece::GetType()
{
	return m_type;
}

detail::IChessPieceEnums::id ChessPiece::GetId()
{
	return m_id;
}

sf::Sprite& ChessPiece::GetSprite()
{
	return m_sprite;
}

void ChessPiece::SetType(detail::IChessPieceEnums::type type)
{
	m_type = type;
}

void ChessPiece::SetId(detail::IChessPieceEnums::id id)
{
	m_id = id;
}

void ChessPiece::SetPosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}

float ChessPiece::GetPositionX()
{
	return m_sprite.getPosition().x;
}

float ChessPiece::GetPositionY()
{
	return m_sprite.getPosition().y;
}

void ChessPiece::ChangePosition(sf::Vector2f nextPosition)
{
}

void ChessPiece::HighlightPossibleMove(int arr[8][8], std::vector<sf::RectangleShape> &square)
{
}
