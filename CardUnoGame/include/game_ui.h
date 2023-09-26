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
	void drawGui(sf::RenderWindow &window);
	void drawUnoButton(sf::RenderWindow &window);
	void hitbox(sf::Vector2f &mouse, int &click);
	int dialog;
	int event;
	bool unoWasPressed();
	void resetUnoButton(bool isHuman);

private:
	bool isOpen;
	float ySelection;
	int dialogX,dialogY,unoButtonX,unoButtonY, divider;
	bool wasPressed;
	bool humanPlayer;
	int lastGameMode;
	sf::Sprite sprite;

};

#endif // MENU_H
