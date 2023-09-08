#include <iostream>
#include "./cards.hpp"
#include <cstdlib>
#include <vector>

class NewPlayer {

public:

    bool adjustRight;

    NewPlayer(float yPosP) {

        yPos = yPosP;
        adjustRight = false;

    }

    void drawOn (sf::RenderWindow &window){
        if (refresh){refreshPos();}
        refresh = false;
        for (int i = 0; i < Cards.size(); i++) {Cards[i].drawOn(window);}

    }

    void insertCard(MakeCard toInsert) {
        Cards.push_back(toInsert);
        refresh = true;

    }

    void eraseCard (int toErase){
        if (Cards.empty()) return;
        Cards.erase(Cards.begin()+(toErase));
        refresh = true;

    }

    int hitbox (sf::Vector2f mouse){
        for (int i = Cards.size(); i > 0 ;) {
                i--;
                if (Cards[i].hitbox(mouse)){return i;}
        }
        return -1;
    }



    MakeCard getCard(int PositionNum){
        return Cards[PositionNum];
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

    int lastCard(){
        return Cards.size()-1;
    }

protected:

    float yPos;
    bool refresh = false;

    std::vector <MakeCard> Cards;

    void createCard (int cardNum, sf::Texture &texture){
        Cards.push_back(cardNum);
        int last = Cards.size() - 1;
        Cards[last].setTexture(texture);
    }

};

class NewDeck : public NewPlayer {

protected:
    float xPos;

public:

    NewDeck (float xPosP, float yPosP,sf::Texture &texture) : NewPlayer(yPosP) {

        xPos = xPosP;
        for (int i= 0; i < 4; i++){createCard(1,texture);}
        for (int i= 0; i < 4; i++){createCard(6,texture);}
        for (int i= 0; i < 52; i++){
            createCard(i+12,texture);
            createCard(i+12,texture);
        }

        for (int i= 0; i < Cards.size(); i++){
            //Cards[i].quickHide();
            if ((Cards[i].getType()) == (Cards[i+1].getType()) ){
                if ((Cards[i].getType()) == '0') {eraseCard(i+1);}
            }
        }
        refresh = true;

    }

    NewDeck (float xPosP, float yPosP) : NewPlayer(yPosP) {

        xPos = xPosP;

    }

    int refreshPos() {

        float xPosP = xPos;
        float yPosP = yPos;
        int i = 0;
        if (Cards.size() > 4) {i = Cards.size() - 4;}
        Cards[i].xPos = xPosP; Cards[i].yPos = yPosP;
        for (;i < Cards.size() ; i++) {
            Cards[i].initAnim(200,xPosP,yPosP,17);
            xPosP = xPosP - 5;
            yPosP = yPosP - 5;
        }
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

    bool hitbox (sf::Vector2f mouse){
        return Cards[Cards.size() - 1].hitbox(mouse);
    }




};


