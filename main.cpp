#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>
#include "./cardstorage.hpp"
#include "./gamelogic.hpp"

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

    sf::Vector2f mousePosition;
    int click = 0;

    srand (time(NULL));

    // Setting up objects for new turnIsOver

    NewHand Player[] = { NewHand(20) , NewHand(350) };
    Player[0].adjustRight = false; Player[0].show();
    Player[1].adjustRight = true;

    NewDeck Deck(350,180,unoCards);
    NewDeck Wastepile(450, 180);

    int turn = 0;
    for (int i = 0;i < 16;i++){
        turn++;
        if (turn > 1) {turn = 0;}
        Player[turn].addCard(Deck.grabCard());

    }
    Wastepile.addCard(Deck.grabCard());

    // turnIsOver Loop

    while (window.isOpen()){

        sf::Event event;
        playerInput(event,window,click,mousePosition);

		if (turnIsOver(Player[turn],Deck,Wastepile,click,mousePosition)) {
            turn++; if (turn > 1) {turn = 0;}
            if (turn == 0) {Player[0].show();Player[1].hide();}
            if (turn == 1) {Player[0].hide();Player[1].show();}
        }

        window.draw(background);
        Deck.drawOn(window);
        Wastepile.drawOn(window);
        Player[0].drawOn(window);
        Player[1].drawOn(window);

        window.display();
    }
    return 0;
}




