#ifndef HAND_CONTROL_H
#define HAND_CONTROL_H
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "./choice.h"
#include "./storage_interaction.h"
#include "./new_deck.h"

class HandControl : public StorageInteraction
{
public:
	HandControl();
	virtual ~HandControl();
	void reset();
	bool isHuman;
	bool exchangeRequested();
	bool isActive (NewDeck &Deck, NewDeck &Wastepile, int &click, sf::Vector2f mouse);

private:
	int cpuTimer = 0;
	int hitbox (sf::Vector2f mouse);
	bool lastCardWasZero;
	bool isReady;
	void eatCards (NewDeck &Deck, NewDeck &Wastepile);
	Choice human (NewDeck &Deck, NewDeck &Wastepile, int &click, sf::Vector2f mouse);
	Choice cpuPlayer (NewDeck &Deck,NewDeck &Wastepile);
	void disableAllButColor(MakeCard toDisable);
	void disableAllButDraw(MakeCard last);
	void disableAllDrawTwo();
	int mostCommonColor();
	bool noMovementsLeft();
	bool isAllowed (int thisCard, MakeCard last);
	bool isFull();

};

#endif // HAND_CONTROL_H
