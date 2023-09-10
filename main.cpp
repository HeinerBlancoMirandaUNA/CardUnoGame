#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>
#include "./cardstorage.hpp"
#include "./gamelogic.hpp"

int main()
{
    // Program Initialization
    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("./resources/felt.png");
    backgroundTexture.setSmooth(true);
    sf::Sprite background;
    background.setTexture(backgroundTexture);

    sf::Texture unoCards;
    unoCards.loadFromFile("./resources/unocards.png");
    unoCards.setSmooth(true);

    srand (time(NULL));

    // Setting up objects for new Game

    NewHand Player[] = { NewHand(window,false) , NewHand(window,true) }; // { NewHand(20,window.getSize().x) , NewHand(window.getSize().y-140,window.getSize().x) };
	Player[0].show();


    NewDeck Deck(-55,50,unoCards,window);
    NewDeck Wastepile(55,50,window);

    int turn = 0;
    for (int i = 0;i < 16;i++){
        turn++;
        if (turn > 1) {turn = 0;}
        Player[turn].addCard(Deck.grabCard());

    }
    Wastepile.addCard(Deck.grabCard());

    // Game Loop

    while (window.isOpen()){

        sf::Event event;
        playerInput(event,window);

		if (turnIsOver(Player[turn],Deck,Wastepile)) {
            turn++; if (turn > 1) {turn = 0;}
            if (turn == 0) {Player[0].show();Player[1].hide();}
            if (turn == 1) {Player[0].hide();Player[1].show();}
        }

        if (action == 11){

			background.setScale(
			window.getSize().x / background.getLocalBounds().width,
			window.getSize().y / background.getLocalBounds().height
			);

			Wastepile.refreshPos(window);
			Deck.refreshPos(window);
			Player[0].refreshPos(window);
			Player[1].refreshPos(window);

        }
		window.clear();
        window.draw(background);
        Deck.drawOn(window);
        Wastepile.drawOn(window);
        Player[0].drawOn(window);
        Player[1].drawOn(window);

        window.display();
    }
    return 0;
}




