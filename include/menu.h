#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class GameMenu
{
public:

	GameMenu(sf::Texture &texture);
	virtual ~GameMenu();
	void drawOn(sf::RenderWindow &window);
	void hitbox(sf::Vector2f &mouse, int &click);
	int event;

private:
	bool isOpen;
	float ySelection;
	sf::Sprite sprite;
	sf::Texture texture;

};

#endif // MENU_H
