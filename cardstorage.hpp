#include <iostream>
#include "./cards.hpp"
#include <cstdlib>
#include <vector>

class NewHand {

protected:

    float yPos;
    bool refresh = false;
    bool hidden = true;
    std::vector <MakeCard> Cards;

public:

    NewHand(float yPosP) {

        yPos = yPosP;
        adjustRight = false;

    }

    bool adjustRight;

    int lastCard(){
        return Cards.size()-1;
    }

    MakeCard getCard(int toGet){
        return Cards[toGet];
    }

    void addCard(MakeCard toInsert) {
        Cards.push_back(toInsert);
        if (hidden) {Cards[lastCard()].hide();}
        else {Cards[lastCard()].show();};
        refresh = true;

    }

    void eraseCard (int toErase){
        if (Cards.empty()) {return;}
        Cards.erase(Cards.begin()+(toErase));
        refresh = true;

    }

    MakeCard grabCard (int toSteal) {
        MakeCard temp = Cards[toSteal];
        eraseCard(toSteal);
        return temp;
    }

	MakeCard grabCard () { // Grabs the last card if no value is specified
        return grabCard(lastCard());
    }

    void bringToFront (int toBring) {
        addCard(Cards[toBring]);
        eraseCard(toBring);
    }

    void hide(){
        for (int i = 0; i < Cards.size(); i++) {Cards[i].hide();hidden = true;}
        hidden = true;
    }

    void show(){
        for (int i = 0; i < Cards.size(); i++) {Cards[i].show();hidden = false;}
        hidden = false;
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
        float width = 800;

        float toDivide = (lastCard()) + 0.01;
        float add = (width - (xPosP*2)) / toDivide;

        if ( (toDivide*70) < (width - (xPosP*2)) ) {add = 70;}

        if (adjustRight) {add = add * -1; xPosP = (width - xPosP);}

        for (int i = 0; i < Cards.size(); i++) {
                Cards[i].initAnim(200,xPosP,yPos,17);
                xPosP = xPosP + add;
        }

    }

};

class NewDeck : public NewHand {

protected:
    float xPos;
    bool autoPurge; // Deletes

    void createCard (int cardNum, sf::Texture &texture){
        Cards.push_back(cardNum);
        Cards[lastCard()].setTexture(texture);
    }

public:

    NewDeck (float xPosP, float yPosP,sf::Texture &texture) : NewHand(yPosP) { // Use this constructor to create Deck object

        xPos = xPosP;
        autoPurge = false;

        // Builds the entire card set

        for (int i= 0; i < 4; i++){createCard(1,texture);}
        for (int i= 0; i < 4; i++){createCard(6,texture);}
        for (int i= 0; i < 52; i++){
            createCard(i+12,texture);
            createCard(i+12,texture);
        }

        for (int i= 0; i < Cards.size(); i++){
            Cards[i].quickHide();
            if ((Cards[i].getType()) == (Cards[i+1].getType()) ){
                if ((Cards[i].getType()) == '0') {eraseCard(i+1);}
            }
        }
        refresh = true;

        // Shuffles the cards

        for (int i = 0; i < 2000; i++) { bringToFront(rand()%107); }

    }

    NewDeck (float xPosP, float yPosP) : NewHand(yPosP) { // Use this constructor to create the Wastepile object

        xPos = xPosP;
        hidden = false;
        autoPurge = true;

    }

    bool hitbox (sf::Vector2f mouse) { // Checks hitbox against last card only, returns boolean
        if (Cards.empty()) {return false;}
        return Cards[lastCard()].hitbox(mouse);
    }

    void drawOn (sf::RenderWindow &window) { // Draws only the last 4 cards

        if (refresh){refreshPos();}
        refresh = false;
        int i = 0;
        if (Cards.size() > 4) {i = Cards.size() - 4;}

        for (; i < Cards.size(); i++) {
            Cards[i].drawOn(window);
        }

        if (autoPurge && (Cards.size() > 5)) {eraseCard(Cards.size() - 5);} // Erase previously used cards

    }

    void refreshPos() { // Aligns the last 4 cards, resembles the look of a card deck...

        float xPosP = xPos;
        float yPosP = yPos;
        int i = 0;
        if (Cards.size() > 4) {i = Cards.size() - 4;}
        Cards[i].xPos = xPosP; Cards[i].yPos = yPosP;
        for (;i < Cards.size() ; i++) {
            Cards[i].initAnim(100,xPosP,yPosP,17);
            xPosP = xPosP - 5;
            yPosP = yPosP - 5;
        }
    }
};


