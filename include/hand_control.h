#ifndef HAND_CONTROL_H
#define HAND_CONTROL_H
#include <SFML/Graphics.hpp>
#include "./choice.h"
#include "./storage_interaction.h"
#include "./new_deck.h"

class HandControl : public StorageInteraction
{
public:
	HandControl();
	bool isHuman;
	bool isActive (NewDeck &Deck, NewDeck &Wastepile, int &click, sf::Vector2f mouse);
	bool isAllowed (int thisCard, MakeCard last);

private:
	int cpuTimer = 0;
	int hitbox (sf::Vector2f mouse);
	Choice human (NewDeck &Deck, NewDeck &Wastepile, int &click, sf::Vector2f mouse);
	Choice cpuPlayer (NewDeck &Deck);
};

#endif // HAND_CONTROL_H
