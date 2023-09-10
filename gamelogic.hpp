int action = 0;
int click = 0;
sf::Vector2f mousePosition;
sf::Vector2i resolution(800,500);
bool isFullScreen = false;

void playerInput(sf::Event &event, sf::RenderWindow &window){

	click = 0;
	action = 0;
	bool switchMode = false;

    while (window.pollEvent(event)) {
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) { click = 1;}
			if (event.mouseButton.button == sf::Mouse::Right) { click = 2; }
			if (event.mouseButton.button == sf::Mouse::Middle) { click = 3; }
		}

		if (event.type == sf::Event::KeyPressed){

			if (event.key.alt&&(event.key.code == sf::Keyboard::Return)){ switchMode = true;}
			if (event.key.code == sf::Keyboard::Escape){ window.close(); }
			if (event.key.code == sf::Keyboard::Num1){ action = 1; }
			if (event.key.code == sf::Keyboard::Num2){ action = 2; }

		}

		if (event.type == sf::Event::Resized) {
			sf::Vector2i lastPosition = window.getPosition();
			window.create(sf::VideoMode(window.getSize().x,window.getSize().y), "");
			window.setPosition(lastPosition);
			action = 11;
		}
		if (event.type == sf::Event::Closed) {window.close();}
		mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	}

	if (switchMode){
		if (isFullScreen){
			window.create(sf::VideoMode(resolution.x, resolution.y), "");
			isFullScreen = false;

		}else{
			window.create(sf::VideoMode(800,600), "",sf::Style::Fullscreen);
			isFullScreen = true;
		}

		action = 11;

	}

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
