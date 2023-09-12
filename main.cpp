#include <iostream>
#include <string.h>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "./cardstorage.hpp"
#include "./userinteraction.hpp"
#include "./gamelogic.hpp"

int main(int argc, char* argv[])
{
    // Program Initialization
    loadTextStrings();

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), info[0]);

	if (argc > 1 && (!strcmp(argv[1],"-fullscreen")) ){
		window.create(sf::VideoMode(sf::VideoMode::getDesktopMode()), "", sf::Style::None);
	}

	tellUser(0);

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

    NewHand Players[] = { NewHand(window,false) , NewHand(window,true) };
	Players[0].show();

    NewDeck Deck(-55,50,unoCards,window);
    NewDeck Wastepile(55,50,window);

    for (int i = 0;i < 16;i++){
        turn++;
        if (turn > 1) {turn = 0;}
        Players[turn].addCard(Deck.grabCard());

    }
    Wastepile.addCard(Deck.grabCard());

    Players[0].isHuman = true;
    Players[1].isHuman = false;

    // Game Loop

    while (window.isOpen()){

        sf::Event event;
        playerInput(event,window);

        thisTurn(Players,Deck,Wastepile);


        drawOn(window,background,Players,Deck,Wastepile);

    }
    return 0;
}




