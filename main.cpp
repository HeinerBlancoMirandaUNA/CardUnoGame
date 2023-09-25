#include <iostream>
#include <string.h>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "./include/choice.h"
#include "./include/make_card.h"
#include "./include/storage_interaction.h"
#include "./include/new_deck.h"
#include "./include/hand_control.h"
#include "./include/new_hand.h"
#include "./include/menu.h"
#include "./user_interaction.hpp"
#include "./player_turn.hpp"


int main(int argc, char* argv[])
{
    // Program Initialization
    loadTextStrings();

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), info[0]);

	if (argc > 1 && (!strcmp(argv[1],"-fullscreen")) ){
		window.create(sf::VideoMode(sf::VideoMode::getDesktopMode()), "", sf::Style::None);
	}

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("./resources/felt.png");
    backgroundTexture.setSmooth(true);
    sf::Sprite background;
    background.setTexture(backgroundTexture);

    sf::Texture menuTexture;
    menuTexture.loadFromFile("./resources/menu.png");
    GameMenu Menu(menuTexture);

    sf::Texture unoCards;
    unoCards.loadFromFile("./resources/unocards.png");
    unoCards.setSmooth(true);

    srand (time(NULL));
	NewHand Players[2];

	// Initializing Game Objects

	Players[0].init(window,false);
	Players[1].init(window,true);

    NewDeck Deck(-55,50,unoCards,window);
    NewDeck Wastepile(55,50,window);

	newGame(Players, Deck, Wastepile, window, unoCards, 1);

    // Game Loop

    while (window.isOpen()){

        sf::Event event;
        playerInput(event,window,Menu);

        if (Menu.event > 0) {
			newGame(Players, Deck, Wastepile, window, unoCards, Menu.event);

        }

        thisTurn(Players,Deck,Wastepile);

        drawOn(window,background,Players,Deck,Wastepile,Menu);

        window.display();

    }
    return 0;
}




