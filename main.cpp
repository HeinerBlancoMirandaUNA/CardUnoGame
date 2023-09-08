#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>
#include "./cardstorage.hpp"

bool lClick, rClick;

int turn = 0;

int main()
{
    // Program Initialization
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

    sf::Vector2f mousePos;

    // Setting up objects for new game

    NewPlayer Player[] = { NewPlayer(20) , NewPlayer(350) };
    Player[1].adjustRight = true;
    NewDeck Deck(350,180,unoCards);
    NewDeck Dumpster(450, 180);

    for (int i = 0;i < 16;i++){
        turn++;
        if (turn > 1) {turn = 0;}
        Player[turn].insertCard(Deck.getCard(Deck.lastCard()));
        Deck.eraseCard(Deck.lastCard());
    }
    Dumpster.insertCard(Deck.getCard(Deck.lastCard()));
    Deck.eraseCard(Deck.lastCard());

    while (window.isOpen()){

        sf::Event event;
        lClick = false;
        rClick = false;
        while (window.pollEvent(event)){

            if (event.type == sf::Event::Closed) {window.close();}

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) { lClick = true; }
                if (event.mouseButton.button == sf::Mouse::Right) { rClick = true; }
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Space){
                    std::cout<<"Switched to player ";
                    turn++; if (turn>1) {turn = 0;}
                    std::cout<<turn + 1 <<std::endl;
                }
            }

            mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        }

        if (lClick) {
            int cardSelect = Player[turn].hitbox(mousePos);
            if(cardSelect > -1){
                Dumpster.insertCard(Player[turn].getCard(cardSelect));
                Player[turn].eraseCard(cardSelect);

            }

            if (Deck.hitbox(mousePos)){
                Player[turn].insertCard(Deck.getCard(Deck.lastCard()));
                Deck.eraseCard(Deck.lastCard());
            }

        }

        window.draw(background);
        Deck.drawOn(window);
        Dumpster.drawOn(window);
        Player[0].drawOn(window);
        Player[1].drawOn(window);

        window.display();
    }
    return 0;
}




