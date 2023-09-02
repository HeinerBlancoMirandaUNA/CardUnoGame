#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <SFML/Graphics.hpp>
#include "./cards.hpp"

bool lClick, rClick;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 480), "Test");
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("./resources/felt.png");
    backgroundTexture.setSmooth(true);
    sf::Sprite background;
    background.setTexture(backgroundTexture);
    background.move(-2,-2); background.setScale(1.01,1);

    sf::Texture unoCards;
    unoCards.loadFromFile("./resources/unocards.png");
    unoCards.setSmooth(true);

    std::vector<MakeCards> Cards;
    for (int i= 0; i < 63; i++){
            Cards.push_back({i,unoCards});
            Cards[i].xPos = (i * 11) + 60 ;
            Cards[i].yPos = 20 ;
            Cards[i].quickHide();
    }

    sf::Vector2f mousePos;

    while (window.isOpen()){

        sf::Event event;
        lClick = false;
        rClick = false;
        while (window.pollEvent(event)){

            if (event.type == sf::Event::Closed) {window.close();}

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left)
                    {
                    lClick = true;

                }
                if (event.mouseButton.button == sf::Mouse::Right)
                    {
                    rClick = true;

                }
            }

            mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        }

        if ((rClick)or(lClick)) {
            for (unsigned int i = Cards.size(); i > 0 ; ) {
                i--;
                if (Cards[i].hitbox(mousePos)){

                    if (lClick){
                    Cards[i].show();
                    std::cout<<"Card type = "<<Cards[i].getType()<<" Color = "<<Cards[i].getColor()<<std::endl;

                    Cards[i].initAnim(100,400+rand()%15,170 + rand()%13,17);
                    }
                    else{
                        Cards[i].colorWild();

                    }

                    Cards.push_back(Cards[i]);
                    Cards.erase(Cards.begin()+i);
                    break;

                }
            }
        }

        window.draw(background);

        for (unsigned int i=0 ; i < Cards.size() ; i++){
            Cards[i].drawOn(window);
        }

        window.display();
    }
    return 0;
}




