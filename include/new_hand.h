#ifndef NEW_HAND_H
#define NEW_HAND_H
#include "./hand_control.h"

class NewHand : public HandControl {

public:

	bool adjustTop;
    NewHand(float yPosP);
	NewHand(sf::RenderWindow &window, bool adjustTopP);
    void drawOn (sf::RenderWindow &window);
    void refreshPos();
	void refreshPos(sf::RenderWindow &window);

};

#endif // NEW_HAND_H
