#include <SFML/Graphics.hpp>

void handicap(NewHand &Player, int type) {

}

void switchTurn (NewHand Players[]) {
	turn++; if (turn > 1) {turn = 0;}
	if (turn == 0) {Players[0].show();Players[1].hide();}
	if (turn == 1) {Players[0].hide();Players[1].show();}
	Players[0].enableAll(); Players[1].enableAll();

}

void thisTurn(NewHand Players[], NewDeck &Deck, NewDeck &Wastepile) {

	NewHand &Player = Players[turn];

	Choice current = Player.choice(Deck, Wastepile, click, mousePosition);

    if (current.action == 3) { switchTurn(Players); Deck.enableAll(); }

}
