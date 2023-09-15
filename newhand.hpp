#include <cstdlib>
#include <vector>

class NewHand {

protected:

    float yPos;
    bool refresh = false;
    bool hidden = true;
    float windowWidth;

    std::vector <MakeCard> Cards;


public:

	bool adjustTop;
	bool isHuman;

    NewHand(float yPosP) {

        yPos = yPosP;
        adjustTop = false;

    }

	NewHand(sf::RenderWindow &window, bool adjustTopP) {

		adjustTop = adjustTopP;
		refreshPos(window);

    }

    int lastCard(){
        return Cards.size()-1;
    }

    MakeCard getCard(int toGet){
        return Cards[toGet];
    }

	MakeCard getCard(){
        return Cards[lastCard()];
    }

    void addCard(MakeCard toInsert) {
        Cards.push_back(toInsert);
        if (hidden) {Cards[lastCard()].hide();}
        else {Cards[lastCard()].show();};
        refresh = true;

    }

    void eraseCard (int toErase){
        if (Cards.empty()) {return;}
        Cards.erase(Cards.begin()+(toErase));
        refresh = true;

    }

    MakeCard grabCard (int toGrab) {
        MakeCard temp = Cards[toGrab];
        eraseCard(toGrab);
        return temp;
    }

	MakeCard grabCard () { // Grabs the last card if no value is specified
        return grabCard(lastCard());
    }

    void colorWild(int toColor){
    	Cards[toColor].colorWild();
    }

    void disable(int toDisable) {
    	Cards[toDisable].enable = false;
    }

    void disableAllButColor(MakeCard toDisable){
    	for (int i = 0; i < Cards.size(); i++) {
			Cards[i].enable = false;
			if (toDisable.getColor()==Cards[i].getColor()) { Cards[i].enable = true; }
			if (Cards[i].isWild()) { Cards[i].enable = false; }
		}
    }

	void disableAll() {
    	for (int i = 0; i < Cards.size(); i++) {Cards[i].enable = false;}
    }

    void enableAll(){
    	for (int i = 0; i < Cards.size(); i++) {Cards[i].enable = true;}
    }

    bool noMovementsLeft(){
		for (int i = 0; i < Cards.size(); i++) {
			if (Cards[i].enable) {return false;}
		}
		return true;
    }

    void bringToFront (int toBring) {
        addCard(Cards[toBring]);
        eraseCard(toBring);
    }

    void hide(){
        for (int i = 0; i < Cards.size(); i++) {Cards[i].hide();hidden = true;}
        hidden = true;
    }

    void show(){
        for (int i = 0; i < Cards.size(); i++) {Cards[i].show();hidden = false;}
        hidden = false;
    }

    int hitbox (sf::Vector2f mouse){ // Checks hitbox against all cards, returns position of the matching card
        for (int i = Cards.size(); i > 0 ;) {
            i--;
            if (Cards[i].hitbox(mouse)){return i;}
        }
        return -1;
    }

    void drawOn (sf::RenderWindow &window){ // Draws all of it's cards on the screen
        if (refresh){refreshPos();}
        refresh = false;
        for (int i = 0; i < Cards.size(); i++) {Cards[i].drawOn(window);}

    }

    void refreshPos() { // Aligns the cards position on the screen
        float xPosP = 50;
        float width = windowWidth;

        float toDivide = (lastCard()) + 0.01;
        float add = (width - (xPosP*2)) / toDivide;

        if ( (toDivide*70) < (width - (xPosP*2)) ) {add = 70;}

        if (adjustTop) {add = add * -1; xPosP = (width - xPosP);}

        for (int i = 0; i < Cards.size(); i++) {
                Cards[i].initAnim(200,xPosP,yPos,17);
                xPosP = xPosP + add;
        }

    }

	void refreshPos(sf::RenderWindow &window){

		windowWidth = window.getSize().x;
        yPos = window.getSize().y - 130;
        if (adjustTop) {
			yPos = 30;
        }
        refreshPos();

    }

};


