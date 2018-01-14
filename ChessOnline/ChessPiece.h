#pragma once
#include "detail.h"
#include "Board.h"

class Board;

class ChessPiece : public detail::IChessPieceEnums
{
public:
	virtual void draw(sf::RenderWindow *win)const = 0;
	virtual void ChangePosition(sf::Vector2f newPosition);

	sf::Sprite& GetSprite();
	void SetType(detail::IChessPieceEnums::type type);
	detail::IChessPieceEnums::type GetType();
	void SetPosition(sf::Vector2f position);
	float GetPositionX();
	float GetPositionY();
	detail::IChessPieceEnums::id GetId();
	void SetId(detail::IChessPieceEnums::id id);

protected:

	detail::IChessPieceEnums::type  m_type;
	detail::IChessPieceEnums::id  m_id;
	sf::Sprite m_sprite;
};

