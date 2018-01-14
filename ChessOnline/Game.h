#pragma once
#include <SFML\Graphics.hpp>
//#include <Windows.h>
#include <string>
#include "NetworkConnection.h"

#include "Chess.h"

using namespace sf;

class Game
{


public:
	Game();
	~Game();

	void RunGame();

	NetworkConnection networkConnection;
protected:
	enum GameState { MENU, GAME_CREATE, GAME_JOIN, GAME_OVER, END };
	GameState gameState;

private:
	sf::Font font;
	sf::RenderWindow window;
	const int width = 800;
	const int height = 560;

	void Menu();
	void MenuEvent(sf::Vector2f mouse, sf::Text text[]);
	void PlayGame();
	//char ipAddress[] = "127.0.0.1";
};

