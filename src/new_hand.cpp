#include "new_hand.h"

NewHand::NewHand(float yPosP) : HandControl() {

	yPos = yPosP;
	adjustTop = false;

}

NewHand::NewHand(sf::RenderWindow &window, bool adjustTopP) : HandControl() {

	adjustTop = adjustTopP;
	refreshPos(window);

}

void NewHand::drawOn (sf::RenderWindow &window){ // Draws all of it's cards on the screen
	if (refresh){refreshPos();}
	refresh = false;
	for (int i = 0; i < Cards.size(); i++) {Cards[i].drawOn(window);}

}

void NewHand::refreshPos() { // Aligns the cards position on the screen
	float xPosP = 50;
	float width = windowWidth;

	float toDivide = (lastCard()) + 0.01;
	float add = (width - (xPosP*2)) / toDivide;

	if ( (toDivide*70) < (width - (xPosP*2)) ) {add = 70;}

	if (adjustTop) {add = add * -1; xPosP = (width - xPosP);}

	for (int i = 0; i < Cards.size(); i++) {
			Cards[i].initAnim(200,xPosP,yPos,17);
			xPosP = xPosP + add;
	}

}

void NewHand::refreshPos(sf::RenderWindow &window){

	windowWidth = window.getSize().x;
	yPos = window.getSize().y - 130;
	if (adjustTop) {
		yPos = 30;
	}
	refreshPos();

}

