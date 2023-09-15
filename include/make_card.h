#ifndef MAKE_CARD_H
#define MAKE_CARD_H
#include <cmath>
#include <SFML/Graphics.hpp>

class MakeCard
{
public:

    float xPos, yPos; // Use these to quickly set the X/Y position of the card
	bool enable; // Enable hitbox
    MakeCard(int cardNumP, sf::Texture &texture);
    MakeCard(int cardNumP);
    void setTexture (sf::Texture &texture);
    void setCard (int cardNumP);
    void quickHide() ;
    void quickShow() ;
    void hide() ;
    void show();
    bool hitbox(sf::Vector2f mouse) ;
    void drawOn(sf::RenderWindow &window);
    void initAnim(unsigned int ticksP,float xAnimP,float yAnimP,float accelerationP) ;
    bool isMoving();
    int getColor ();
    char getType();
    void colorWild();
    bool isWild();

protected:

    sf::Sprite spriteCard;
    unsigned int ticks;
    unsigned int flipstate;
    bool hidden;
    bool animRunning;
    int cardNum;
    int opacity;
    float xAnim;
    float yAnim;
    float acceleration;
    float squash;
    float textureWidth = 167.8;
    float textureHeight = 258;

    void initCard(int cardNumP) {
        xPos = 400;
        yPos = 150;
        xAnim = 0;
        yAnim = 0;
        animRunning = false;
        enable = true;
        opacity = 0;
        flipstate = 0;
        squash = 0.4;
        cardNum = cardNumP;
        spriteCard.setScale(0.4,0.4);

    }

    float finalX() { // Sets the actual position X of the sprite, forces origin point to the upper middle of the sprite

        return (xPos - ((textureWidth/2) * squash));

    }

    void setTexture(int texturePos) { // Sets texture according to card number position

        float cardNumP = static_cast<float>(texturePos);
        float xCardNum = (fmod(cardNumP,12))*textureWidth;  // Card texture offset in X
        float yCardNum = (floor((cardNumP)/12))*textureHeight; // Card texture offset in Y
        spriteCard.setTextureRect(sf::IntRect(xCardNum,yCardNum,165,258));

    }

    void moveAnim() { // Updates movement animation

        if (animRunning) {

                xPos = xPos+((xAnim-xPos)/(ticks)*acceleration);
                yPos = yPos+((yAnim-yPos)/(ticks)*acceleration);
                ticks = ticks - 1;
                if (ticks == 0) {
                        animRunning = false;
                        xPos = xAnim;
                        yPos = yAnim;
                }
        }

    }

    void opacityAnim (){
		if (enable){
			if (opacity<244) {opacity = opacity + 10;}

		} else {
			if (opacity>50) {opacity = opacity - 10;}
		}
    }

    void initFlip() { // Initializes flip animation

        flipstate = 1;

    }

    void flipAnim() { // Updates flip animation

        if (flipstate == 0){return;}

        if (flipstate == 1){ // Squash sprite
            squash = squash - 0.08;
            if (squash < 0.001){
                flipstate = 2;
                if (hidden){setTexture(0);}
                else setTexture(cardNum);
            }
        }

        if (flipstate == 2){ // Stretch sprite
            squash = squash + 0.03;
            if (squash > 0.4){
                squash = 0.4;
                flipstate = 3;
            }
        }

        if (flipstate > 0) {spriteCard.setScale(squash ,0.4);}

        if (flipstate == 3) {flipstate = 0;}

    }

};

#endif // MAKE_CARD_H
