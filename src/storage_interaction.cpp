#include "storage_interaction.h"

StorageInteraction::StorageInteraction()
{
	cout<<"Inheritance Successful"<<endl;
}

StorageInteraction::~StorageInteraction()
{
	cout<<"StorageInteraction - Destruction Successful"<<endl;
}

void StorageInteraction::reset(){

	while (!isEmpty()) {eraseCard(0);}

}


int StorageInteraction::lastCard(){
	return Cards.size()-1;
}

MakeCard StorageInteraction::getCard(int toGet){
	return Cards[toGet];
}

MakeCard StorageInteraction::getCard(){
	return Cards[lastCard()];
}

void StorageInteraction::addCard(MakeCard toInsert) {
	Cards.push_back(toInsert);
	if (hidden) {Cards[lastCard()].hide();}
	else {Cards[lastCard()].show();};
	refresh = true;
}

void StorageInteraction::eraseCard (int toErase){
	if (Cards.empty()) {return;}
	Cards.erase(Cards.begin()+(toErase));
	refresh = true;
}

MakeCard StorageInteraction::grabCard (int toGrab) {
	MakeCard temp = Cards[toGrab];
	eraseCard(toGrab);
	return temp;
}

MakeCard StorageInteraction::grabCard () { // Grabs the last card if no value is specified
	return grabCard(lastCard());
}

void StorageInteraction::colorWild(int toColor){
	Cards[toColor].colorWild();
}

void StorageInteraction::disable(int toDisable) {
	Cards[toDisable].enable = false;
}

void StorageInteraction::disableAll() {
	for (int i = 0; i < Cards.size(); i++) {Cards[i].enable = false;}
}

void StorageInteraction::enableAll(){
	for (int i = 0; i < Cards.size(); i++) {Cards[i].enable = true;}
}

void StorageInteraction::bringToFront (int toBring) {
	addCard(Cards[toBring]);
	eraseCard(toBring);
}

void StorageInteraction::hide(){
	for (int i = 0; i < Cards.size(); i++) {Cards[i].hide();hidden = true;}
	hidden = true;
}

void StorageInteraction::show(){
	for (int i = 0; i < Cards.size(); i++) {Cards[i].show();hidden = false;}
	hidden = false;
}

bool StorageInteraction::isEmpty(){
	return Cards.empty();
}





