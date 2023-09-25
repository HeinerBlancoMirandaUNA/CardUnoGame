#include "game_ui.h"

GameUI::GameUI(sf::Texture &texture)
{
	sprite.setTexture(texture);
	isOpen = false;
	dialog = 0;
	dialogX = 0;
	dialogY = 0;
	divider = 0;
	lastGameMode = 0;
	humanPlayer = true;
	wasPressed = false;

}

GameUI::~GameUI()
{

}

void GameUI::drawUnoButton(sf::RenderWindow &window){

	unoButtonX =(window.getSize().x/2)-78;
	unoButtonY =(window.getSize().y/2)-40;
	sprite.setTextureRect(sf::IntRect(0,957,135,149));

	sprite.setPosition(unoButtonX,unoButtonY);
	sprite.move( (145 / divider) -10, 20 / divider);
	sprite.setColor(sf::Color(10,10,10,(9*divider)+35));
	window.draw(sprite);

	sprite.setPosition(unoButtonX,unoButtonY);
	sprite.move( -25 / divider, -25 / divider);
	sprite.setColor(sf::Color(255,255,255,255));

	window.draw(sprite);
	std::cout<<wasPressed<<std::endl;

}

void GameUI::drawGui(sf::RenderWindow &window) {

	sprite.setPosition(0,0);
	sprite.setOrigin(0,0);
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

	dialogX = (window.getSize().x /2) - 119;

	if (dialog>0&&dialog<4){


		dialogY = 50;
		if (dialog == 1) { dialogY = window.getSize().y - 150;}
		sprite.setPosition(dialogX,dialogY);
		sprite.setTextureRect(sf::IntRect(0,442,239,101));
		window.draw(sprite);
		sprite.move(0,35);
		sprite.setTextureRect(sf::IntRect(0,544 + ((dialog-1) * 17),239,17));
		window.draw(sprite);

	}

	if (dialog == 4) {
		dialogY = (window.getSize().y/2) -180;
		sprite.setPosition(dialogX,dialogY);
		dialogY = dialogY + 261;
		sprite.setTextureRect(sf::IntRect(0,595,239,363));
		window.draw(sprite);

	}

}

void GameUI::hitbox(sf::Vector2f &mouse, int &click){

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
			event = static_cast<int>(ySelection);
			lastGameMode = event;
			dialog = 0;
			click = 0;

		}
	}

	bool closeDialog= click == 1&&
	(mouse.x > dialogX +76) && ( mouse.x < dialogX + 150)&&
	(mouse.y > dialogY +63) && ( mouse.y < dialogY + 85);

	if (dialog > 0) {
		if (closeDialog) {dialog = 0; event = lastGameMode; }

		click = 0;
	}

	if (!humanPlayer) {divider = 10;}

	bool isTouchingButton =
	(mouse.x > unoButtonX+15) && ( mouse.y > unoButtonY)&&
	(mouse.x < unoButtonX+115) && ( mouse.y < unoButtonY+85);

	if (isTouchingButton) {

		if (click == 1) {
			divider = 10;
			wasPressed = true;
			return;
		}

		if (divider > 4) {divider--;}


	} else {

		if (divider < 10) {divider++;}

	}

}

bool GameUI::unoWasPressed(){
	return wasPressed;
}

void GameUI::resetUnoButton(bool isHuman){
	wasPressed = false;
	humanPlayer = isHuman;

}


