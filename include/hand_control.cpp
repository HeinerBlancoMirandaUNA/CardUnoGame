#include "hand_control.h"

HandControl::HandControl() : StorageInteraction()
{

};

HandControl::~HandControl()
{

};

void HandControl::reset(){
	StorageInteraction::reset();
	isReady = true;
	lastCardWasZero = false;
	cpuTimer = 1;

};

bool HandControl::isActive (NewDeck &Deck, NewDeck &Wastepile, int &click, sf::Vector2f mouse) {

	Choice current;
	lastCardWasZero = false;
	bool endTurn = false;

	if (isReady) { // Executed only when players switch turn
		if (Wastepile.getCardCount() > 1) { disableAllDrawTwo(); } // Rule C
		Wastepile.resetCount();
		if (Deck.getCardCount() > 0) {
			disableAllButDraw(Wastepile.getCard());
			bool canIeat =(isFull()&&noMovementsLeft())||Deck.isEmpty();
			if (canIeat) { enableAll(); Deck.resetCount(); }
		}
		isReady = false;
	}

	if (isFull()) {Deck.disableAll();}

	if (isHuman) { current = human(Deck,Wastepile,click,mouse); }
	else { current = cpuPlayer(Deck,Wastepile); }

	if (current.action == 1) {

		if (!isAllowed(current.card, Wastepile.getCard())) { return true;}
		if (!isFull()) {Deck.enableAll();}

		MakeCard last = getCard(current.card);

		if (!(Wastepile.getCard().getColor()==last.getColor())) {endTurn = true;}

		if (last.getType()=='M') { Deck.increaseCountBy(4); Wastepile.resetCount(); }
		if (last.isWild()) {endTurn = true; }
		if (last.getType()=='D') { Deck.increaseCountBy(2); Wastepile.resetCount(); endTurn = true;}

		Wastepile.addCard(grabCard(current.card));
		disableAllButColor(last);
		Deck.disableAll();

		if (noMovementsLeft()) {endTurn = true;}
		if (last.getType()=='0') { lastCardWasZero = true; ; endTurn = true;} // This will handle the card swithching beetween players
		if (last.getType()=='S') { current.action = 1;endTurn = false; Deck.enableAll(); enableAll(); }

	}

    if (current.action == 2) {

		if (Cards[current.card].getColor() > 0 ) {colorWild(current.card);}
		else {Cards[current.card].colorWild(mostCommonColor());}
		bringToFront(current.card);
    }

	if (current.action == 4) {

		eatCards(Deck,Wastepile);
		if (Deck.getCardCount() > 0) {endTurn = true;}
		Deck.resetCount();

	}

    if (current.action == 3&&Deck.getCardCount() == 0) {
		endTurn = true;
	}

	if (endTurn) {
		isReady = true;
		return false;
	}

	return true;

}

bool HandControl::isFull(){
	if (lastCard() > 22){
		return true;
	}
	return false;
}

bool HandControl::exchangeRequested(){
	return lastCardWasZero;
}

bool HandControl::noMovementsLeft(){
	for (int i = 0; i < Cards.size(); i++) {
		if (Cards[i].enable) {return false;}
	}
	return true;
}

void HandControl::eatCards(NewDeck &Deck, NewDeck &Wastepile){

	if (Deck.getCardCount() == 0){

		if (isFull()) { return; }
		if (!Deck.getCard().enable) { return; }
		addCard(Deck.grabCard());
		Wastepile.increaseCountBy(1);

	} else {

		for (int i=0; i < Deck.getCardCount() ; i++){
			if (isFull()) { return; }
			addCard(Deck.grabCard()); }

	}

}

void HandControl::disableAllButColor(MakeCard toDisable){
	for (int i = 0; i < Cards.size(); i++) {
		Cards[i].enable = false;
		if (toDisable.getColor()==Cards[i].getColor()) { Cards[i].enable = true; }
		if (Cards[i].isWild()) { Cards[i].enable = false; }
	}
}

void HandControl::disableAllButDraw(MakeCard last) {
	for (int i = 0; i < Cards.size(); i++) {
		bool disableThis = true;
		if (last.getType()=='D'){
			if (Cards[i].getType()=='D') { disableThis = false; }
		}

		if (last.getType()=='M'){
			if (Cards[i].getColor()==last.getColor()&&Cards[i].getType()=='D') { disableThis = false; }
		}

		if (Cards[i].getType()=='M') { disableThis = false; }
		if (disableThis) {
			Cards[i].enable = false;
		}
	}
}

void HandControl::disableAllDrawTwo(){
	for (int i = 0; i < Cards.size(); i++) {
		if (Cards[i].getType() == 'D') { Cards[i].enable = false; }
	}
}


bool HandControl::isAllowed (int thisCard, MakeCard last){
	MakeCard toThrow = getCard(thisCard);
	if (toThrow.getColor() == 0) { return false; }
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

	if (click == 1&&thisCard > -1) {
		return {1,thisCard};
	}

	if (click == 2&&thisCard > -1) {
		return {2,thisCard};
	}

	if (click == 1&&Wastepile.hitbox(mouse)) {
		return {3,0};
	}

	if (click == 3) {
		return {3,0};
	}

	if (click == 1&&Deck.hitbox(mouse)) {
		return {4,0};
	}

	return {0,0};
}

Choice HandControl::cpuPlayer (NewDeck &Deck, NewDeck &Wastepile){

	cpuTimer++;
	int delay = 60;
	if (cpuTimer < delay){
		return {0,0};
	}
	cpuTimer = 0;

	int colorToSwitch = mostCommonColor();
	MakeCard last = Wastepile.getCard();

	MakeCard myCard = getCard();

	if (myCard.isWild()&&myCard.getColor()>0) { return {1,lastCard()};}

	for (int i = 0;i < lastCard()+1; i++) {

		myCard = getCard(i);

		bool itsAPlusFourCard = myCard.enable && myCard.getType() == 'M';

		if (itsAPlusFourCard) {
			if (myCard.getColor() == 0) {return {2, i};}
			return {1, i};
		}

	}

	for (int i = 0;i < lastCard()+1; i++) {

		myCard = getCard(i);
		bool itsTheSameCardColor = myCard.enable && (myCard.getColor() == last.getColor());
		if (itsTheSameCardColor) {return {1, i};}

	}

	for (int i = 0;i < lastCard()+1; i++) {

		bool istAColorWildCard =
		getCard(i).enable && (
		getCard(i).getType() == 'W'
		);

		if (istAColorWildCard) {
			if (getCard(i).getColor() > 0) {return {1, i};}
			if (last.getColor() != getCard().getColor()) {return {2, i};}
		}

	}



	for (int i = 0;i < lastCard()+1; i++) {

		bool itsTheSameCardType =
		getCard(i).enable && (
		(getCard(i).getType() == last.getType())||
		last.getColor() == 0); // Throws card anyway if it doesn't have a color assigned

		if (itsTheSameCardType) {return { 1, i };}

	}


	if (!Deck.isEmpty()&&!isFull()) {

		cpuTimer = cpuTimer + (delay/3);
		return {4,0};

	}

	return {3,0};
}

int HandControl::mostCommonColor(){

	int color[5];
	for (int i = 0; i < 5; i++){color[i] = 0;}

	for (int i = 0; i < lastCard()+1; i++) {
		for (int j = 0; j < 5; j++){
			if (getCard(i).getColor() == j&&!getCard(i).isWild()) {color[j]++;}
		}

	}

	int largest = color[0];
	for (int i = 0; i < 5; i++){
		if (color[i] > color[largest]){ largest = i; }
	}

	if (largest == 0) { largest= 1 + rand()%4;}

	return largest;

}


