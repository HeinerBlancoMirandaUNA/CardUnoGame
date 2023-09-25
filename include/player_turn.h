#include <SFML/Graphics.hpp>

void deal (NewHand Players[], NewDeck &Deck, NewDeck &Wastepile){
	for (int i = 0;i < 16;i++){
        turn++;
        if (turn > 1) {turn = 0;}
        Players[turn].addCard(Deck.grabCard());

    }
    Wastepile.addCard(Deck.grabCard());

}

void newGame(NewHand Players[], NewDeck &Deck, NewDeck &Wastepile, sf::RenderWindow &window, sf::Texture &texture, int mode) {

	Deck.reset();
	Deck.rebuildCardset(texture,window);
	Wastepile.reset();
	Players[0].reset();
	Players[1].reset();
	deal(Players, Deck, Wastepile);
	turn = 0;
	Players[0].show();
	Players[1].hide();
	Players[0].isHuman = true;
	Players[1].isHuman = true;
	if (mode > 1) { Players[1].isHuman = false; }
	if (mode > 2) { Players[0].isHuman = false; }

}

void switchTurn (NewHand Players[]) {

	if (Players[turn].exchangeRequested()){
		Players[1].exchangeCardsWith(Players[0]);
	}

	turn++; if (turn > 1) {turn = 0;}
	if (turn == 0) {Players[0].show();Players[1].hide();}
	if (turn == 1) {Players[0].hide();Players[1].show();}
	Players[0].enableAll(); Players[1].enableAll();

}

void thisTurn(NewHand Players[], NewDeck &Deck, NewDeck &Wastepile, GameUI &UserInterface) {

	NewHand &Player = Players[turn];

	if (UserInterface.dialog > 0) { return; }

	bool playerIsOver = !Player.isActive(Deck, Wastepile, click, mousePosition);

	if (Player.isEmpty()) {
		UserInterface.dialog = 3;
		if (Player.isHuman) { UserInterface.dialog = turn+1;}
	}

	bool unoNotPressed = false;

    if (playerIsOver) {
		unoNotPressed = !UserInterface.unoWasPressed()&&Player.isHuman&&Player.lastCard()==0;

		if (!Deck.isEmpty()&&unoNotPressed) {Player.addCard(Deck.grabCard());}
		if (!Deck.isEmpty()&&unoNotPressed) {Player.addCard(Deck.grabCard());}

		switchTurn(Players); Deck.enableAll();
		UserInterface.resetUnoButton(Players[turn].isHuman);

	}



}
