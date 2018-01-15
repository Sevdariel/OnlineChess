#include "Game.h"

Game::Game(char argv[])
{
	window.create(sf::VideoMode(width, height), "OnlineChess");

	networkConnection.SetIpAddress(argv);
	gameState = END;

	if (!font.loadFromFile("Data/Fonts/arial.ttf"))
	{
		//MessageBox(NULL, "Font not found", "ERROR", NULL);
		return;
	}

	gameState = MENU;
}


Game::~Game()
{
}
//menu main loop
void Game::RunGame()
{
	while (gameState != END)
	{
		switch (gameState)
		{
		case MENU:
			Menu();
			break;
		case GAME_CREATE:
			//creating new room at server
			//receiving result as char // c - room created
			networkConnection.SendMessageToServer('c');
			networkConnection.ReceiveMessageFromServer();
			if (networkConnection.GetBufSign() == 'c')
			{
				networkConnection.ReceiveMessageFromServer();
				PlayGame();
			}
			gameState = MENU;
			break;
		case GAME_JOIN:
			//joining to existing room at the server
			//receiving result as char // j - joined room 
			networkConnection.SendMessageToServer('j');
			networkConnection.ReceiveMessageFromServer();
			if (networkConnection.GetBufSign() == 'j')
			{
				networkConnection.ReceiveMessageFromServer();
				PlayGame();
			}
			gameState = MENU;
			break;
		case GAME_OVER:
			PlayGame();		//TODO Switch yo GameOver method
			break;
		}
	}
}
// menu strings
void Game::Menu()
{
	Text title("Chess Online", font, 80);
	title.setStyle(Text::Bold);

	title.setPosition(width / 2 - title.getGlobalBounds().width / 2, 20);

	const int ile = 3;

	Text text[ile];

	std::string str[] = { "Create Lobby","Join Lobby", "Exit" };
	for (int i = 0; i<ile; i++)
	{
		text[i].setFont(font);
		text[i].setCharacterSize(55);

		text[i].setString(str[i]);
		text[i].setPosition(width / 2 - text[i].getGlobalBounds().width / 2, 250 + i * 100);
	}

	while (gameState == MENU)
	{
		Vector2f mouse(Mouse::getPosition(window));
		Event event;
		MenuEvent(mouse, text);

		for (int i = 0; i<ile; i++)
			if (text[i].getGlobalBounds().contains(mouse))
				text[i].setFillColor(Color::Cyan);
			else text[i].setFillColor(Color::White);

			window.clear();

			window.draw(title);
			for (int i = 0; i<ile; i++)
				window.draw(text[i]);

			window.display();
	}
}
//menu mouse event
void Game::MenuEvent(sf::Vector2f mouse, sf::Text text[])
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			gameState = END;
		else if (text[0].getGlobalBounds().contains(mouse) &&
			event.type == sf::Event::MouseButtonReleased &&
			event.key.code == sf::Mouse::Left)
			gameState = GAME_CREATE;
		else if (text[1].getGlobalBounds().contains(mouse) &&
			event.type == sf::Event::MouseButtonReleased &&
			event.key.code == sf::Mouse::Left)
			gameState = GAME_JOIN;
		else if (text[2].getGlobalBounds().contains(mouse) &&
			event.type == sf::Event::MouseButtonReleased &&
			event.key.code == sf::Mouse::Left)
			gameState = END;
	}
}
//launching game loop
void Game::PlayGame()
{
	Chess chess(window, networkConnection);

	if (!chess.Run())
		gameState = GAME_OVER;
}