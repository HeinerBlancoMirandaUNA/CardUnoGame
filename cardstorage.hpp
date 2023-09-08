#include <iostream>
#include "./cards.hpp"
#include <cstdlib>
#include <vector>

class NewPlayer {

protected:

    float yPos;
    bool refresh = false;
    bool hidden = true;
    std::vector <MakeCard> Cards;

    void createCard (int cardNum, sf::Texture &texture){
        Cards.push_back(cardNum);
        int last = Cards.size() - 1;
        Cards[last].setTexture(texture);
    }

public:

    NewPlayer(float yPosP) {

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

    void insertCard(MakeCard toInsert) {
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

    MakeCard stealCard (int toSteal) {
        MakeCard temp = Cards[toSteal];
        eraseCard(toSteal);
        return temp;
    }

    void bringToFront (int toBring) {
        insertCard(Cards[toBring]);
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

    int hitbox (sf::Vector2f mouse){
        for (int i = Cards.size(); i > 0 ;) {
            i--;
            if (Cards[i].hitbox(mouse)){return i;}
        }
        return -1;
    }

    void drawOn (sf::RenderWindow &window){
        if (refresh){refreshPos();}
        refresh = false;
        for (int i = 0; i < Cards.size(); i++) {Cards[i].drawOn(window);}

    }

    void refreshPos() {
        float xPosP = 50;
        float width = 800;

        float toDivide = (Cards.size()-1) + 0.01;
        float add = (width - (xPosP*2)) / toDivide;

        if ( (toDivide*70) < (width - (xPosP*2)) ) {add = 70;}

        if (adjustRight) {add = add * -1; xPosP = (width - xPosP);}

        for (int i = 0; i < Cards.size(); i++) {
                Cards[i].initAnim(200,xPosP,yPos,17);
                xPosP = xPosP + add;}

    }

};

class NewDeck : public NewPlayer {

protected:
    float xPos;

public:

    // Use this constructor to create Deck object

    NewDeck (float xPosP, float yPosP,sf::Texture &texture) : NewPlayer(yPosP) {

        xPos = xPosP;

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

        //Shuffles the cards

        for (int i = 0; i < 2000; i++) {
            int moveThis=rand()%107;
            insertCard(Cards[moveThis]);
            eraseCard(moveThis);
        }


    }

    // Use this constructor to create Dumpster object

    NewDeck (float xPosP, float yPosP) : NewPlayer(yPosP) {

        xPos = xPosP;
        hidden = false;

    }

    bool hitbox (sf::Vector2f mouse){
        if (Cards.empty()) {return false;}
        return Cards[Cards.size() - 1].hitbox(mouse);
    }

    void drawOn (sf::RenderWindow &window){

        if (refresh){refreshPos();}
        refresh = false;
        int i = 0;
        if (Cards.size() > 4) {i = Cards.size() - 4;}

        for (; i < Cards.size(); i++) {
            Cards[i].drawOn(window);
        }
    }

    void refreshPos() {

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


