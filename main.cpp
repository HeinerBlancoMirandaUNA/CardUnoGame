#include <iostream>
#include <cmath>
#include <vector>
#include <SFML/Graphics.hpp>
#include "./cardstorage.hpp"

bool space;

int turn = 0;

void playerInput(sf::Event &event, sf::RenderWindow &window, int &click,sf::Vector2f &mousePosition){

	space = false;
	click = 0;

    while (window.pollEvent(event)) {
		if (event.type == sf::Event::MouseButtonPressed) {

			if (event.mouseButton.button == sf::Mouse::Left) { click = 1;}
			if (event.mouseButton.button == sf::Mouse::Right) { click = 2; }
			if (event.mouseButton.button == sf::Mouse::Middle) { click = 3; }
		}
	if (event.type == sf::Event::Closed) {window.close();}
	mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	}

}

void game(NewHand &Player, NewDeck &Deck, NewDeck &Wastepile, int click, sf::Vector2f &mousePosition) {

	int thisCard;

	if (click > 0) {thisCard = Player.hitbox(mousePosition);}

	if (click == 1) {
			if(Deck.hitbox(mousePosition)){ Player.addCard(Deck.grabCard()); return; }
            if(thisCard > -1){ Wastepile.addCard(Player.grabCard(thisCard)); return; }
	}
	if (click == 2) {
		if (thisCard > -1){ Player.bringToFront(thisCard); }
    }
}



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

    // Setting up objects for new game

    NewHand Player[] = { NewHand(20) , NewHand(350) };
    Player[0].adjustRight = false; Player[0].show();
    Player[1].adjustRight = true;

    NewDeck Deck(350,180,unoCards);
    NewDeck Wastepile(450, 180);

    for (int i = 0;i < 16;i++){
        turn++;
        if (turn > 1) {turn = 0;}
        Player[turn].addCard(Deck.grabCard());

    }
    Wastepile.addCard(Deck.grabCard());

    // Game Loop

    while (window.isOpen()){

        sf::Event event;
        playerInput(event,window,click,mousePosition);
        game(Player[turn],Deck,Wastepile,click,mousePosition);

		if (click == 3) {
            turn++; if (turn > 1) {turn = 0;}
            std::cout<<"Switched to player ";
            std::cout<<turn<<std::endl;
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




