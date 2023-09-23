#include <SFML/Graphics.hpp>

void switchTurn (NewHand Players[]) {

	if (Players[turn].exchangeRequested()){
		Players[1].exchangeCardsWith(Players[0]);
	}

	turn++; if (turn > 1) {turn = 0;}
	if (turn == 0) {Players[0].show();Players[1].hide();}
	if (turn == 1) {Players[0].hide();Players[1].show();}
	Players[0].enableAll(); Players[1].enableAll();

}

void thisTurn(NewHand Players[], NewDeck &Deck, NewDeck &Wastepile) {

	NewHand &Player = Players[turn];

    if (!Player.isActive(Deck, Wastepile, click, mousePosition)) {
		switchTurn(Players); Deck.enableAll();
	}

}
