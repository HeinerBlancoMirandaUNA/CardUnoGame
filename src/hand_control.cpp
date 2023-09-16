#include "hand_control.h"

HandControl::HandControl() : StorageInteraction() {cout<<"^^^^^^HandControl"<<endl; };

bool HandControl::isActive (NewDeck &Deck, NewDeck &Wastepile, int &click, sf::Vector2f mouse) {

	Choice current;
	if (isHuman) { current = human(Deck,Wastepile,click,mouse); }
	else { current = cpuPlayer(Deck); }

	if (current.action == 1) {

		if (!isAllowed(current.card, Wastepile.getCard())) { return true;}

		MakeCard last = getCard(current.card);

		if (!(Wastepile.getCard().getColor()==last.getColor())) {current.action = 3;}
		if (last.isWild()) {current.action = 3; }
		if (last.getType()=='D') {current.action = 3;}

		Wastepile.addCard(grabCard(current.card));
		disableAllButColor(last);
		Deck.disableAll();

		if (noMovementsLeft()) {current.action = 3;}
		if (last.getType()=='S') { current.action = 1; Deck.enableAll(); enableAll(); }

	}

    if (current.action == 2) {
		colorWild(current.card);
		bringToFront(current.card);
    }

    if (current.action == 3) {return false;}

    if (current.action == 4) { addCard(Deck.grabCard()); }

	return true;

}

bool HandControl::isAllowed (int thisCard, MakeCard last){
	MakeCard toThrow = getCard(thisCard);
	if ((last.getColor() == 0)&&(toThrow.getColor() == 0)) { return false; }
	if (last.getColor() == 0) {return true;}
	if ((toThrow.getColor() > 0)&&(toThrow.isWild())) {return true;}
	if (toThrow.getColor() == last.getColor()) {return true;}
	if (toThrow.getType() == last.getType()) {return true;}
	return false;
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
	//std::cout<<"Cpu";
	cpuTimer++;
	if (cpuTimer < 30){
		return {0,0};
	}
	cpuTimer = 0;
	return {3,0};
}


