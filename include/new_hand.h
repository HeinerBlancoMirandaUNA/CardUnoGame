#ifndef NEW_HAND_H
#define NEW_HAND_H
#include "./hand_control.h"

class NewHand : public HandControl {

public:

	bool adjustTop;
	NewHand();
	~NewHand();
	void init(sf::RenderWindow &window, bool adjustTopP);
    void drawOn (sf::RenderWindow &window);
    void refreshPos();
	void refreshPos(sf::RenderWindow &window);
	void exchangeCardsWith(NewHand &Player);

};

#endif // NEW_HAND_H
