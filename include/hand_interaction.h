#ifndef HAND_INTERACTION_H
#define HAND_INTERACTION_H
#include <vector>
#include <iostream>
#include "./make_card.h"
using std::cout;
using std::endl;

class HandInteraction
{
	protected:
		float yPos;
		bool refresh = false;
		bool hidden = true;
		float windowWidth;
		std::vector <MakeCard> Cards;

	public:
		HandInteraction();
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

};

#endif // HAND_INTERACTION_H
