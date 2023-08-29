#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

class MakeCards
{
public:

    float xPos, yPos; // Use these to quickly set the X/Y position of the card

    MakeCards(float cardNumP, sf::Texture &texture){ // Creates a card, the cardNumP sets the type of card

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

    void setCard (float cardNumP){ // Set to a different card (Animated)

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
        hidden = true;
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

private:

    sf::Sprite spriteCard;
    unsigned int ticks;
    unsigned int flipstate;
    bool hidden;
    bool animRunning;
    float xAnim;
    float yAnim;
    float acceleration;
    float cardNum;
    float squash;
    float textureWidth = 167.8;
    float textureHeight = 258;

    float finalX() { // Sets the actual position X of the sprite, changes origin point to the upper middle of the sprite

        return (xPos - ((textureWidth/2) * squash));

    }

    void setTexture(float cardNumP) { // Sets texture according to card number position

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
