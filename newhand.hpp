#include <cstdlib>
#include <vector>

class NewHand : public HandInteraction {

public:

	bool adjustTop;
	bool isHuman;

    NewHand(float yPosP) : HandInteraction() {

        yPos = yPosP;
        adjustTop = false;

    }

	NewHand(sf::RenderWindow &window, bool adjustTopP) : HandInteraction() {

		adjustTop = adjustTopP;
		refreshPos(window);

    }

    int hitbox (sf::Vector2f mouse){ // Checks hitbox against all cards, returns position of the matching card
        for (int i = Cards.size(); i > 0 ;) {
            i--;
            if (Cards[i].hitbox(mouse)){return i;}
        }
        return -1;
    }

    void drawOn (sf::RenderWindow &window){ // Draws all of it's cards on the screen
        if (refresh){refreshPos();}
        refresh = false;
        for (int i = 0; i < Cards.size(); i++) {Cards[i].drawOn(window);}

    }

    void refreshPos() { // Aligns the cards position on the screen
        float xPosP = 50;
        float width = windowWidth;

        float toDivide = (lastCard()) + 0.01;
        float add = (width - (xPosP*2)) / toDivide;

        if ( (toDivide*70) < (width - (xPosP*2)) ) {add = 70;}

        if (adjustTop) {add = add * -1; xPosP = (width - xPosP);}

        for (int i = 0; i < Cards.size(); i++) {
                Cards[i].initAnim(200,xPosP,yPos,17);
                xPosP = xPosP + add;
        }

    }

	void refreshPos(sf::RenderWindow &window){

		windowWidth = window.getSize().x;
        yPos = window.getSize().y - 130;
        if (adjustTop) {
			yPos = 30;
        }
        refreshPos();

    }

};


