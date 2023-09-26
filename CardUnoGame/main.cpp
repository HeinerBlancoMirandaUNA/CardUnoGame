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
#include "./include/game_ui.h"
#include "./include/user_interaction.h"
#include "./include/player_turn.h"


int main(int argc, char* argv[])
{
    // Program Initialization

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "");

	if (argc > 1 && (!strcmp(argv[1],"-fullscreen")) ){
		window.create(sf::VideoMode(sf::VideoMode::getDesktopMode()), "", sf::Style::None);
	}

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("./resources/felt.png");
    backgroundTexture.setSmooth(true);
    sf::Sprite background;
    background.setTexture(backgroundTexture);

    sf::Texture dialogTexture;
    dialogTexture.loadFromFile("./resources/ui.png");
    GameUI UserInterface(dialogTexture);

    sf::Texture unoCards;
    unoCards.loadFromFile("./resources/unocards.png");
    unoCards.setSmooth(true);

    srand (time(NULL));


	// Initializing Game Objects And Variables

	NewHand Players[2];
	Players[0].init(window,false);
	Players[1].init(window,true);

    NewDeck Deck(-125,40,unoCards,window);
    NewDeck Wastepile(125,40,window);

	newGame(Players, Deck, Wastepile, window, unoCards, 1);

	UserInterface.dialog = 4;

    // Game Loop

    while (window.isOpen()){

        sf::Event event;
        playerInput(event,window,UserInterface);

        if (UserInterface.event > 0) {
			newGame(Players, Deck, Wastepile, window, unoCards, UserInterface.event);
			UserInterface.resetUnoButton(Players[turn].isHuman);
        }

        thisTurn(Players,Deck,Wastepile,UserInterface);

        drawOn(window,background,Players,Deck,Wastepile,UserInterface);

        window.display();

    }
    return 0;
}




