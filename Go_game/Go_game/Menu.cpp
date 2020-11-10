#include "Menu.h"


/***************************************************************************************/
Menu::Menu()
	:
	board(game)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		// handle error
	}

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f( game.get_mWindow().getSize().x / 2, game.get_mWindow().getSize().y / (MAX_NUMBER_OF_ITEMS + 1) * 1 ) );

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::Black);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f( game.get_mWindow().getSize().x / 2, game.get_mWindow().getSize().y / (MAX_NUMBER_OF_ITEMS + 1 ) * 2 ) );

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::Black);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f( game.get_mWindow().getSize().x / 2, game.get_mWindow().getSize().y / (MAX_NUMBER_OF_ITEMS + 1 ) * 3 ) );

	selectedItemIndex = 0;

	game.get_mWindow().clear(sf::Color(255, 207, 97));
}


/***************************************************************************************/
Menu::~Menu()
{
}


/***************************************************************************************/
void Menu::draw()
{
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		game.get_mWindow().draw( menu[i] );
	}
}


/***************************************************************************************/
void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}


/***************************************************************************************/
void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}


/***************************************************************************************/
void Menu::switchCaseMenu()
{
	while (game.get_mWindow().isOpen())
	{
		while (game.get_mWindow().pollEvent(game.get_event()))
		{
			switch (game.get_event().type)
			{
			case sf::Event::KeyReleased:
				switch (game.get_event().key.code)
				{
				case sf::Keyboard::Up:
					MoveUp();
					Display();
					break;

				case sf::Keyboard::Down:
					MoveDown();
					Display();
					break;

				case sf::Keyboard::Return:
					switch (GetPressedItem())
					{
					case 0:
						game.Run();
						break;
					case 1:
						menu[0].setString("19x19");
						menu[1].setString("13x13");
						menu[2].setString("9x9");

						Display();
						break;
					case 2:
						game.get_mWindow().close();
						break;
					}
				}
			}
		}
	}
}


/***************************************************************************************/
void Menu::Run()
{

	draw();

	game.get_mWindow().display();

	switchCaseMenu();

}


/***************************************************************************************/
void Menu::Display()
{
	game.get_mWindow().clear(sf::Color(255, 207, 97));

	draw();

	game.get_mWindow().display();
}