#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class GameUI
{
public:

	GameUI(sf::Texture &texture);
	virtual ~GameUI();
	void drawOn(sf::RenderWindow &window);
	void hitbox(sf::Vector2f &mouse, int &click);
	int dialog;
	int event;

private:
	bool isOpen;
	float ySelection;
	int dialogX;
	int dialogY;
	int lastGameMode;
	sf::Sprite sprite;

};

#endif // MENU_H
