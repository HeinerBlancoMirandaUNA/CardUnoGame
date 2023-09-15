#include "hand_interaction.h"


HandInteraction::HandInteraction()
{
	cout<<"Inheritance Successful"<<endl;
}

int HandInteraction::lastCard(){
	return Cards.size()-1;
}

MakeCard HandInteraction::getCard(int toGet){
	return Cards[toGet];
}

MakeCard HandInteraction::getCard(){
	return Cards[lastCard()];
}

void HandInteraction::addCard(MakeCard toInsert) {
	Cards.push_back(toInsert);
	if (hidden) {Cards[lastCard()].hide();}
	else {Cards[lastCard()].show();};
	refresh = true;
}

void HandInteraction::eraseCard (int toErase){
	if (Cards.empty()) {return;}
	Cards.erase(Cards.begin()+(toErase));
	refresh = true;
}

MakeCard HandInteraction::grabCard (int toGrab) {
	MakeCard temp = Cards[toGrab];
	eraseCard(toGrab);
	return temp;
}

MakeCard HandInteraction::grabCard () { // Grabs the last card if no value is specified
	return grabCard(lastCard());
}

void HandInteraction::colorWild(int toColor){
	Cards[toColor].colorWild();
}

void HandInteraction::disable(int toDisable) {
	Cards[toDisable].enable = false;
}

void HandInteraction::disableAllButColor(MakeCard toDisable){
	for (int i = 0; i < Cards.size(); i++) {
		Cards[i].enable = false;
		if (toDisable.getColor()==Cards[i].getColor()) { Cards[i].enable = true; }
		if (Cards[i].isWild()) { Cards[i].enable = false; }
	}
}

void HandInteraction::disableAll() {
	for (int i = 0; i < Cards.size(); i++) {Cards[i].enable = false;}
}

void HandInteraction::enableAll(){
	for (int i = 0; i < Cards.size(); i++) {Cards[i].enable = true;}
}

bool HandInteraction::noMovementsLeft(){
	for (int i = 0; i < Cards.size(); i++) {
		if (Cards[i].enable) {return false;}
	}
	return true;
}

void HandInteraction::bringToFront (int toBring) {
	addCard(Cards[toBring]);
	eraseCard(toBring);
}

void HandInteraction::hide(){
	for (int i = 0; i < Cards.size(); i++) {Cards[i].hide();hidden = true;}
	hidden = true;
}

void HandInteraction::show(){
	for (int i = 0; i < Cards.size(); i++) {Cards[i].show();hidden = false;}
	hidden = false;
}



