#include "Menu.h"

GameMenu::GameMenu(sf::Texture &texture)
{
	sprite.setTexture(texture);

	isOpen = false;
}

GameMenu::~GameMenu()
{

}

void GameMenu::drawOn(sf::RenderWindow &window) {

	if (isOpen) {
		sprite.setTextureRect(sf::IntRect(0,254,239,127));
		window.draw(sprite);
		sprite.setPosition(0,(ySelection*18)+8);
		sprite.setTextureRect(sf::IntRect(0,417,239,19));
		window.draw(sprite);
		sprite.setPosition(0,0);
		sprite.setTextureRect(sf::IntRect(0,127,239,127));
		window.draw(sprite);

	}else{
		sprite.setTextureRect(sf::IntRect(0,0,239,127));
		window.draw(sprite);

	}

}

void GameMenu::hitbox(sf::Vector2f &mouse, int &click){

	event = 0;
	ySelection = floor((mouse.y-8)/18);
	if (ySelection < 2) {ySelection = 1;}
	if (ySelection > 3) {ySelection = 4;}

	bool insideMenu = isOpen&&(mouse.x < 239 && (mouse.y < 102&&mouse.y > 22));

	if (click == 1) {
		if (isOpen) {isOpen =false;click = 0;}
		else {
			if (mouse.x < 45&&mouse.y <22) {isOpen = true;click = 0;}
		}
		if (insideMenu) {
			event = ySelection;click = 0;
		}
	}

}


