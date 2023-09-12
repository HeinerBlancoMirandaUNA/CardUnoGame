#include <SFML/Graphics.hpp>
int cpuTimer = 0;

struct Choice {
	int action, card;
};

bool isAllowed (MakeCard toThrow, MakeCard last){
	if (last.getColor() == 0) {return true;}
	if ((toThrow.getColor()>0)&&(toThrow.isWild())) {return true;}
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

Choice human(NewHand &Player, bool deckIsClicked) {

	int thisCard = 0;
	if (click > 0) {thisCard = Player.hitbox(mousePosition);}

	if ((click == 1)&&(thisCard > -1)){
		return {1,thisCard};
	}

	if ((click == 2)&&(thisCard > -1)){
		return {2,thisCard};
	}

	if (click == 3) {
		return {3,0};
    }

	if ((click == 1)&&deckIsClicked){
		return {4,0};
	}

    return {0,0};

}

Choice cpu() {
	std::cout<<"Cpu";
	cpuTimer++;
	if (cpuTimer < 30){

		return {0,0};
	}
	cpuTimer = 0;

	return {3,0};
}

void thisTurn(NewHand Players[], NewDeck &Deck, NewDeck &Wastepile) {

	NewHand &Player = Players[turn];
	Choice my = {0,0};

	if (Player.isHuman) {
		my = human(Player,Deck.hitbox(mousePosition));
	}
	else {
		my = cpu();
	}

	if (my.action == 1) {
		if (!isAllowed(Player.getCard(my.card), Wastepile.getCard())) {	return;	}
		Wastepile.addCard(Player.grabCard(my.card));
	}

    if (my.action == 2) {
		Player.colorWild(my.card);
		Player.bringToFront(my.card);
    }

    if (my.action == 3) { switchTurn(Players); }
    if (my.action == 4) { Player.addCard(Deck.grabCard()); }

}
