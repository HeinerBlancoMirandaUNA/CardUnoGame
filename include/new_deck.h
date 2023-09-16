#ifndef NEW_DECK_H
#define NEW_DECK_H
#include <cstdlib>
#include <vector>
#include <./storage_interaction.h>

class NewDeck : public StorageInteraction
{
protected:
    float xPos;
	float windowHeight;
    bool autoPurge; // Tells Wastepile to delete unused cards
    void createCard (int cardNum, sf::Texture &texture);

public:

    NewDeck (float xPosP, float yPosP,sf::Texture &texture,sf::RenderWindow &window);
    NewDeck (float xPosP, float yPosP,sf::RenderWindow &window) ;
    bool hitbox (sf::Vector2f mouse) ;
    void drawOn (sf::RenderWindow &window) ;
    void refreshPos();
    void refreshPos(sf::RenderWindow &window);

};

#endif // NEW_DECK_H
