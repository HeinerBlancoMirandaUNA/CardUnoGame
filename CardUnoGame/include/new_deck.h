#ifndef NEW_DECK_H
#define NEW_DECK_H
#include <cstdlib>
#include <vector>
#include "./storage_interaction.h"

class NewDeck : public StorageInteraction
{
private:
    float xPos;
	float windowHeight;
    bool autoPurge; // Tells Wastepile to delete unused cards
    void createCard (int cardNum, sf::Texture &texture);
    int cardCount;

public:

    NewDeck (float xPosP, float yPosP,sf::Texture &texture,sf::RenderWindow &window);
    NewDeck (float xPosP, float yPosP,sf::RenderWindow &window) ;
    ~NewDeck();
    void rebuildCardset(sf::Texture &texture,sf::RenderWindow &window);
    void reset();
    bool hitbox (sf::Vector2f mouse) ;
    void drawOn (sf::RenderWindow &window) ;
    void refreshPos();
    void refreshPos(sf::RenderWindow &window);

    void resetCount();
    void increaseCountBy(int thisAmount);
    int getCardCount();


};

#endif // NEW_DECK_H
