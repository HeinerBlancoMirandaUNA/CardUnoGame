#ifndef MAKE_CARD_H
#define MAKE_CARD_H
#include <cmath>
#include <SFML/Graphics.hpp>

class MakeCard
{
public:

    float xPos, yPos;
	bool enable;
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

    void initCard(int cardNumP);
    float finalX();
    void setTexture(int texturePos);
    void moveAnim();
    void opacityAnim();
    void initFlip();
    void flipAnim();

};

#endif // MAKE_CARD_H
