int action = 0;
int turn = 0;
int click = 0;
bool windowResized = true;
sf::Vector2f mousePosition;
sf::Vector2i resolution(800,480);

void playerInput(sf::Event &event, sf::RenderWindow &window){

	click = 0;
	action = 0;
	//windowResized = false;

    while (window.pollEvent(event)) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) { click = 1;}
			if (event.mouseButton.button == sf::Mouse::Right) { click = 2; }
			if (event.mouseButton.button == sf::Mouse::Middle) { click = 3; }
		}

		if (event.type == sf::Event::KeyPressed){

			if (event.key.code == sf::Keyboard::Escape){ window.close(); }
			if (event.key.code == sf::Keyboard::Num1){ action = 1; }
			if (event.key.code == sf::Keyboard::Num2){ action = 2; }

		}

		if (event.type == sf::Event::Resized) {
			sf::Vector2i lastPosition = window.getPosition();
			window.create(sf::VideoMode(window.getSize().x,window.getSize().y), "");
			window.setPosition(lastPosition);
			action = 11;
			windowResized = true;
		}
		if (event.type == sf::Event::Closed) {window.close();}
		mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	}

}

void drawOnWindow(sf::RenderWindow &window, sf::Sprite &background, NewHand Player[], NewDeck &Deck, NewDeck &Wastepile){

	if (windowResized) {
		background.setScale(
		window.getSize().x / background.getLocalBounds().width,
		window.getSize().y / background.getLocalBounds().height
		);

		Wastepile.refreshPos(window);
		Deck.refreshPos(window);
		Player[0].refreshPos(window);
		Player[1].refreshPos(window);
		windowResized = false;

	}

	window.clear();
	window.draw(background);
	Deck.drawOn(window);
	Wastepile.drawOn(window);
	Player[0].drawOn(window);
	Player[1].drawOn(window);

	window.display();

}

void switchTurn (NewHand Player[]) {
	turn++; if (turn > 1) {turn = 0;}
	if (turn == 0) {Player[0].show();Player[1].hide();}
	if (turn == 1) {Player[0].hide();Player[1].show();}

}


bool turnIsOver(NewHand &Player, NewDeck &Deck, NewDeck &Wastepile) {

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
