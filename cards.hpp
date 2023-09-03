#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

class MakeCards
{
public:

    float xPos, yPos; // Use these to quickly set the X/Y position of the card

    MakeCards(int cardNumP, sf::Texture &texture){ // Creates a card, the cardNumP sets the type of card

        xPos = 0;
        yPos = 0;
        xAnim = 0;
        yAnim = 0;
        animRunning = false;
        flipstate = 0;
        squash = 0.4;
        cardNum = cardNumP;

        spriteCard.setTexture(texture);
        spriteCard.setScale(0.4,0.4);

        quickShow();

    }

    void setCard (int cardNumP){ // Set to a different card (Animated)

        if (!(cardNum == cardNumP)){
            hidden = false;
            cardNum = cardNumP;
            initFlip();
        }

    }

    void quickHide() { // Flip to the backside of the card
        hidden = true;
        setTexture(0);
    }

    void quickShow() { // Reveals a flipped card
        hidden = false;
        setTexture(cardNum);
    }

    void hide() {  // Flip to the backside of the card (Animated)
        if (!hidden){
            hidden = true;
            initFlip();
        }
    }

    void show(){ // Reveals a flipped card (Animated)
        if (hidden) {
            hidden = false;
            initFlip();
        }
    }

    bool hitbox(sf::Vector2f mouse) { // Mouse Hitbox

        if ((mouse.x > finalX())and(mouse.y > yPos)){
            if ((mouse.x < finalX() + 66 )and(mouse.y < yPos + 103.2 )){return true;}
        }
        return false;

    }

    void drawOn(sf::RenderWindow &window) { // Draws sprite on the window

        moveAnim(); flipAnim();
        spriteCard.setPosition(finalX(), yPos);
        window.draw(spriteCard);

    }

    void initAnim(unsigned int ticksP,float xAnimP,float yAnimP,float accelerationP) { // Initializes movement animation with acceleration

        ticks = ticksP;                 // Animation length
        xAnim = xAnimP;                 // New X position for Sprite
        yAnim = yAnimP;                 // New Y position for Sprite
        acceleration = accelerationP;   // Acceleration (Use any float greater than 1 for normal acceleration, decimals lower than 1 to disable Slow Out, 1 for no acceleration, 0 to disable animation)
        animRunning = true;

    }

    bool isMoving() { //Use this one to check if movement animation is playing
        return animRunning;
    }

    int getColor (){

        if (cardNum < 6){return cardNum - 1;}

        if (cardNum < 11){return cardNum - 6;}

        if (cardNum > 11){
            return floor((cardNum + 1) / 13);
        }
        return 0;
    }

    char getType() {

        if (cardNum > 11){
            int position = 0;
            position = (cardNum - 11 ) % 13;

            switch (position){
                case 10:
                    return '0'; // Zero Card
                    break;
                case 11:
                    return 'D'; // Draw two Card
                    break;
                case 12:
                    return 'S'; // Stop Card
                    break;
                case 0:
                    return 'R'; // Reverse Card
                default:
                    return 48 + position; // Cards between 1 to 9;
            }

        }
        if (cardNum < 6){
            return 'W'; // Wild Card
        }

        return 'M'; // Wild Card - Draw four

    }

    void colorWild() { // Change color to Wild Card

        if (getType() == 'W') {
            if (cardNum > 4) {setCard(2);}
            else {setCard(cardNum + 1);}
        }
        if (getType() == 'M') {
            if (cardNum > 9) {setCard(7);}
            else {setCard(cardNum + 1);}
        }

    }


private:

    sf::Sprite spriteCard;
    unsigned int ticks;
    unsigned int flipstate;
    bool hidden;
    bool animRunning;
    int cardNum;
    float xAnim;
    float yAnim;
    float acceleration;
    float squash;
    float textureWidth = 167.8;
    float textureHeight = 258;

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
