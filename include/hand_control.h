#ifndef HAND_CONTROL_H
#define HAND_CONTROL_H
#include <SFML/Graphics.hpp>
#include "./choice.h"
#include "./hand_interaction.h"
#include "../newdeck.hpp"

class HandControl : public HandInteraction
{
public:
	HandControl() : HandInteraction() {cout<<"HandControl"<<endl; };
	bool isHuman;
	Choice choice (NewDeck &Deck, NewDeck &Wastepile, int &click, sf::Vector2f mouse);
	int hitbox (sf::Vector2f mouse);

private:
	int cpuTimer = 0;
	Choice human (NewDeck &Deck, NewDeck &Wastepile, int &click, sf::Vector2f mouse);
	Choice cpuPlayer (NewDeck &Deck);
};

#endif // HAND_CONTROL_H
