void playerInput(sf::Event &event, sf::RenderWindow &window, int &click,sf::Vector2f &mousePosition){

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

bool turnIsOver(NewHand &Player, NewDeck &Deck, NewDeck &Wastepile, int click, sf::Vector2f &mousePosition) {

	int thisCard;

	if (click > 0) {thisCard = Player.hitbox(mousePosition);}

	if (click == 1) {
		if(Deck.hitbox(mousePosition)){ Player.addCard(Deck.grabCard()); }
		if(thisCard > -1){ Wastepile.addCard(Player.grabCard(thisCard)); }
	}
	if (click == 2) {
		if (thisCard > -1){ Player.bringToFront(thisCard); }
    }

    if (click == 3) {
		return true;
    }

    return false;

}
