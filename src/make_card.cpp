#include "make_card.h"

/*
MakeCard::MakeCard()
{
	//ctor
}*/

float xPos, yPos; // Use these to quickly set the X/Y position of the card

bool enable; // Enable hitbox

MakeCard::MakeCard(int cardNumP, sf::Texture &texture){ // Creates a card, cardNumP sets the type of card and texture

	initCard(cardNumP);
	spriteCard.setTexture(texture);

}

MakeCard::MakeCard(int cardNumP){ // Creates card without texture
	initCard(cardNumP);
}

void MakeCard::setTexture (sf::Texture &texture){
	spriteCard.setTexture(texture);
	quickShow();
}

void MakeCard::setCard (int cardNumP){ // Set to a different card (Animated)

	if (!(cardNum == cardNumP)){
		hidden = false;
		cardNum = cardNumP;
		initFlip();
	}

}

void MakeCard::quickHide() { // Flip to the backside of the card
	hidden = true;
	setTexture(0);
}

void MakeCard::quickShow() { // Reveals a flipped card
	hidden = false;
	setTexture(cardNum);
}

void MakeCard::hide() {  // Flip to the backside of the card (Animated)
	if (!hidden){
		hidden = true;
		initFlip();
	}
}

void MakeCard::show(){ // Reveals a flipped card (Animated)
	if (hidden) {
		hidden = false;
		initFlip();
	}
}

bool MakeCard::hitbox(sf::Vector2f mouse) { // Mouse Hitbox

	if (!enable) {return false;}
	if ((mouse.x > finalX())and(mouse.y > yPos)){
		if ((mouse.x < finalX() + 66 )and(mouse.y < yPos + 103.2 )){return true;}
	}
	return false;

}

void MakeCard::drawOn(sf::RenderWindow &window) { // Draws sprite on the window

	moveAnim(); flipAnim(); opacityAnim();
	spriteCard.setColor(sf::Color(255,255,255,opacity));
	spriteCard.setPosition(finalX(), yPos);
	window.draw(spriteCard);

}

void MakeCard::initAnim(unsigned int ticksP,float xAnimP,float yAnimP,float accelerationP) { // Initializes movement animation with acceleration

    ticks = ticksP;                 // Animation length
    xAnim = xAnimP;                 // New X position for Sprite
    yAnim = yAnimP;                 // New Y position for Sprite
    acceleration = accelerationP;   // Acceleration (Use any float greater than 1 for normal acceleration, decimals lower than 1 to disable Slow Out, 1 for no acceleration, 0 to disable animation)
    animRunning = true;

}

bool MakeCard::isMoving() { //Use this one to check if movement animation is playing
    return animRunning;
}

int MakeCard::getColor (){

	if (cardNum < 6){return cardNum - 1;}

	if (cardNum < 11){return cardNum - 6;}

	if (cardNum > 11){
		return floor((cardNum + 1) / 13);
	}
	return 0;
}

char MakeCard::getType() {

	if (cardNum > 11){
		int position = 0;
		position = (cardNum - 11 ) % 13;

		switch (position){
			case 10:
				return '0'; // Zero Card
				break;
			case 11:
				return 'D'; // Draw two Card
				break;
			case 12:
				return 'S'; // Stop Card
				break;
			case 0:
				return 'R'; // Reverse Card
			default:
				return 48 + position; // Cards between 1 to 9;
		}

	}
	if (cardNum < 6){
		return 'W'; // Wild Card
	}

	return 'M'; // Wild Card - Draw four

}

void MakeCard::colorWild() { // Change Wild Card Color

	if (getType() == 'W') {
		if (cardNum > 4) {setCard(2);}
		else {setCard(cardNum + 1);}
	}
	if (getType() == 'M') {
		if (cardNum > 9) {setCard(7);}
		else {setCard(cardNum + 1);}
	}

}

bool MakeCard::isWild(){
	if ((getType()=='M')||(getType()=='W')) {return true;}
	return false;
}

// Private stuff



