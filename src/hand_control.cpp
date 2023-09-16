#include "hand_control.h"

Choice HandControl::choice (NewDeck &Deck, NewDeck &Wastepile, int &click, sf::Vector2f mouse) {

	if (isHuman) { return human(Deck,Wastepile,click,mouse); }
	else { return cpuPlayer(Deck); }

}

int HandControl::hitbox (sf::Vector2f mouse){ // Checks hitbox against all cards, returns position of the matching card
	for (int i = Cards.size(); i > 0 ;) {
		i--;
		if (Cards[i].hitbox(mouse)){return i;}
	}
	return -1;
}

Choice HandControl::human (NewDeck &Deck, NewDeck &Wastepile, int &click, sf::Vector2f mouse){
	int thisCard = 0;
	if (click > 0) {thisCard = hitbox(mouse);}

	if ((click == 1)&&(thisCard > -1)) {
		return {1,thisCard};
	}

	if ((click == 2)&&(thisCard > -1)) {
		return {2,thisCard};
	}

	if ((click == 1)&&Wastepile.hitbox(mouse)) {
		return {3,0};
	}

	if (click == 3) {
		return {3,0};
	}

	if ((click == 1)&&Deck.hitbox(mouse)) {
		return {4,0};
	}

	return {0,0};
}

Choice HandControl::cpuPlayer (NewDeck &Deck){
	std::cout<<"Cpu";
	cpuTimer++;
	if (cpuTimer < 30){
		return {0,0};
	}
	cpuTimer = 0;
	return {3,0};
}


