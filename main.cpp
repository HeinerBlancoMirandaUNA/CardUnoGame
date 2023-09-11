#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>
#include "./cardstorage.hpp"
#include "./gamelogic.hpp"

int main(int argc, char* argv[])
{
    // Program Initialization

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "");

	if (argc > 1 && (!strcmp(argv[1],"-fullscreen")) ){
		window.create(sf::VideoMode(sf::VideoMode::getDesktopMode()), "", sf::Style::None);
	}

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

    NewHand Player[] = { NewHand(window,false) , NewHand(window,true) };
	Player[0].show();

    NewDeck Deck(-55,50,unoCards,window);
    NewDeck Wastepile(55,50,window);

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
			switchTurn(Player);
		}

        drawOnWindow(window,background,Player,Deck,Wastepile);
    }
    return 0;
}




