#ifndef STORAGE_INTERACTION_H
#define STORAGE_INTERACTION_H
#include <vector>
#include <iostream>
#include "./make_card.h"
using std::cout;
using std::endl;

class StorageInteraction // STORAGE_INTERACTION_H
{
	protected:
		float yPos;
		bool refresh = false;
		bool hidden = true;
		float windowWidth;
		std::vector <MakeCard> Cards;

	public:
		StorageInteraction();
		int lastCard();
		MakeCard getCard(int toGet);
		MakeCard getCard();
		void addCard(MakeCard toInsert);
		void eraseCard (int toErase);
		MakeCard grabCard (int toGrab);
		MakeCard grabCard (); // Grabs the last card if no value is specified
		void colorWild(int toColor);
		void disable(int toDisable) ;
		void disableAllButColor(MakeCard toDisable);
		void disableAll() ;
		void enableAll();
		bool noMovementsLeft();
		void bringToFront (int toBring) ;
		void hide();
		void show();
		bool isFull();

};

#endif // STORAGE_INTERACTION_H
