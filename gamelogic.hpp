#include <SFML/Graphics.hpp>

bool isAllowed (MakeCard toThrow, MakeCard last){
	if (toThrow.getColor() == 0) {return false;}
	if (toThrow.getColor() == last.getColor()) {return true;}
	if (toThrow.getType() == last.getType()) {return true;}
	return false;

}

void switchTurn (NewHand Players[]) {
	turn++; if (turn > 1) {turn = 0;}
	if (turn == 0) {Players[0].show();Players[1].hide();}
	if (turn == 1) {Players[0].hide();Players[1].show();}
	Players[0].enableAll(); Players[1].enableAll();

}

void thisTurn(NewHand Players[], NewDeck &Deck, NewDeck &Wastepile) {

	NewHand &Player = Players[turn];
	int thisCard = 0;
	int action = 0;


	if (click > 0) {thisCard = Player.hitbox(mousePosition);}

	if (click == 1) {
		if(Deck.hitbox(mousePosition)){ Player.addCard(Deck.grabCard()); }
		if(thisCard > -1){
			if (!isAllowed(Player.getCard(thisCard), Wastepile.getCard())){ Player.disable(thisCard); return; }
			Wastepile.addCard(Player.grabCard(thisCard));
		}
	}
	if (click == 2) {
		if (thisCard > -1){ Player.colorWild(thisCard); Player.bringToFront(thisCard); }
    }

    if (click == 3) {
		switchTurn(Players);
    }




}
