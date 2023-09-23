#include "new_deck.h"

void NewDeck::createCard (int cardNum, sf::Texture &texture){
	Cards.push_back(cardNum);
	Cards[lastCard()].setTexture(texture);
}

NewDeck::~NewDeck(){
	cout<<"Deck Destroyed"<<endl;
}

NewDeck::NewDeck (float xPosP, float yPosP,sf::Texture &texture,sf::RenderWindow &window) : StorageInteraction() { // Use this constructor to create Deck object

	xPos = xPosP;
	yPos = yPosP;
	autoPurge = false;
	resetCount();

	// Builds the entire card set

	for (int i= 0; i < 4; i++){createCard(1,texture);}
	for (int i= 0; i < 4; i++){createCard(6,texture);}
	for (int i= 0; i < 52; i++){
		createCard(i+12,texture);
		createCard(i+12,texture);
	}

	for (int i= 0; i < Cards.size(); i++){
		Cards[i].quickHide();
		if ((Cards[i].getType()) == (Cards[i+1].getType()) ){
			if ((Cards[i].getType()) == '0') {eraseCard(i+1);}
		}
	}

	// Shuffles the cards

	for (int i = 0; i < 2000; i++) { bringToFront(rand()%107); }

	refreshPos(window);

}

NewDeck::NewDeck (float xPosP, float yPosP,sf::RenderWindow &window) : StorageInteraction() { // Use this constructor to create the Wastepile object

	xPos = xPosP;
	yPos = yPosP;
	hidden = false;
	autoPurge = true;
	refreshPos(window);
	resetCount();

}

bool NewDeck::hitbox (sf::Vector2f mouse) { // Checks hitbox against last card only, returns boolean
	if (Cards.empty()) {return false;}
	return Cards[lastCard()].hitbox(mouse);
}

void NewDeck::drawOn (sf::RenderWindow &window) { // Draws only the last 4 cards

	if (refresh){refreshPos();}
	refresh = false;
	int i = 0;
	if (Cards.size() > 4) {i = Cards.size() - 4;}

	for (; i < Cards.size(); i++) {
		Cards[i].drawOn(window);
	}

	if (autoPurge && (Cards.size() > 5)) {eraseCard(Cards.size() - 5);} // Erase previously used cards
	cout<<cardCount<<endl;
}

void NewDeck::refreshPos() { // Aligns the last 4 cards, resembles the look of a card deck...

	if (Cards.empty()) {return;}
	float xPosP = (windowWidth/2)-xPos;
	float yPosP = (windowHeight/2)-yPos;

	int i = 0;
	if (Cards.size() > 4) {i = Cards.size() - 4;}

	for (int j; j < i; j++){
		Cards[j].xPos = xPosP; Cards[j].yPos = yPosP;
	}

	for (;i < Cards.size() ; i++) {
		xPosP = xPosP - 5;
		yPosP = yPosP - 5;
		Cards[i].initAnim(100,xPosP,yPosP,17);

	}

}

void NewDeck::refreshPos(sf::RenderWindow &window){
	windowWidth = window.getSize().x;
	windowHeight = window.getSize().y;
	refreshPos();

}

void NewDeck::resetCount(){
	cardCount = 0;
}

void NewDeck::increaseCountBy(int thisAmount){
	cardCount = cardCount + thisAmount;
}

int NewDeck::getCardCount(){
	return cardCount;
}
