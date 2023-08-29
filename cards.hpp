#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

class MakeCards
{
public:

    float xPos, yPos; //Use these to set the X/Y position of the card
    bool animRunning; //Use this one to check if an animation is playing

    MakeCards(float cardNumP, sf::Texture &texture){

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


    void show(){
        if (hidden) {
            hidden = false;
            initFlip();
        }
    }

    void hide(){
        if (!hidden){
            hidden = true;
            initFlip();
        }
    }

    void quickHide() {
        hidden = true;
        setTexture(0);
    }

    void quickShow() {
        hidden = true;
        setTexture(cardNum);
    }

    bool hitbox (sf::Vector2f mouse){

        if ((mouse.x > finalX())and(mouse.y > yPos)){
            if ((mouse.x < finalX() + 66 )and(mouse.y < yPos + 103.2 )){return true;}
        }
        return false;

    }

    void drawOn(sf::RenderWindow &window) {

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

        //squash = squash + 0.01;

        //if (test > 0.4) {test = 0.01;}
        //test = 0.4;
        flip();

        spriteCard.setPosition(finalX(), yPos);
        window.draw(spriteCard);
    }

    void initAnim (unsigned int ticksP,float xAnimP,float yAnimP,float accelerationP){

        ticks = ticksP;                 // Animation length
        xAnim = xAnimP;                 // New X position for Sprite
        yAnim = yAnimP;                 // New Y position for Sprite
        acceleration = accelerationP;   // Acceleration (Use any float greater than 1 for normal acceleration, decimals lower than 1 to disable Slow Out, 1 for no acceleration, 0 to disable animation)
        animRunning = true;

    }
    void initFlip (){

        flipstate = 1;

    }

private:

    sf::Sprite spriteCard;
    unsigned int ticks;
    unsigned int flipstate;
    bool hidden;
    float xAnim;
    float yAnim;
    float acceleration;
    float cardNum;
    float squash;
    float textureWidth = 167.8;
    float textureHeight = 258;

    void setTexture (float cardNumP){

        float xCardNum = (fmod(cardNumP,12))*textureWidth;  // Card texture offset in X
        float yCardNum = (floor((cardNumP)/12))*textureHeight; // Card texture offset in Y
        spriteCard.setTextureRect(sf::IntRect(xCardNum,yCardNum,165,258));

    }

    float finalX (){
        return (xPos - ((textureWidth/2) * squash));
    }

    void flip(){
        if (flipstate == 0){return;}

        if (flipstate == 1){
            squash = squash - 0.08;
            if (squash < 0.001){
                flipstate = 2;
                if (hidden){setTexture(0);}
                else setTexture(cardNum);
            }
        }
        if (flipstate == 2){
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
