#include "sidebar.h"
#include "constants.h"
#include <cstring>


sidebar::sidebar() {
//    std::cout << "sidebar CTOR: top" << std::endl

    //LOAD FONT
//    std::cout<<"sidebar CTOR: loading font"<<std::endl;
    if(!font.loadFromFile("../res/Bangers.ttf")) {
        std::cout<<"sidebar CTOR: can't load font"<<std::endl;
        cin.get();  //why tho?
        exit(-1);
    }
//    std::cout << "sidebar CTOR: font loaded" << endl;

    //INIT TEXT
    sb_text.setFont(font);
    sb_text.setCharacterSize(24);
    sb_text.setColor(sf::Color::White);
//    std::cout<<"text object initialized"<<std::endl;
}

void sidebar::draw(sf::RenderWindow &window) {
/*    const double VERTICAL_LINE_SPACING = 5.0;
    const double LEFT_MARGIN = 10.0;

    window.draw(rect);
    float height = 10;

    for (vector<string>::iterator it = items.begin();
                                it!= items.end(); it++){
        bool blank = false;
        if (strlen(it->c_str()) == 0){
            //empty rows must be taken into account (getLocalBounds())
            //    but not drawn
            blank = true;
            sb_text.setString("BLANK");
        }
        else{
            sb_text.setString(it->c_str());
        }
        sb_text.setPosition(sf::Vector2f(_left+LEFT_MARGIN, height));
        height += sb_text.getLocalBounds().height+VERTICAL_LINE_SPACING;
        if (!blank)
            window.draw(sb_text);
    }
    */
    //DRAW MAIN FUNCTION BUTTONS

    if(_buttonState == B_PAUSED)
        drawText(sf::Color::White, "Resume", 550, 30, window);
    else
        drawText(sf::Color::White, "Pause", 550, 30, window);
    drawText(sf::Color::White, "Random", 550, 78, window);
    drawText(sf::Color::White, "Clear", 550, 126, window);
//    drawText(sf::Color::White, "Exit", 550, 174, window);
    if(_buttonState == B_SELECTING)
        drawText(sf::Color::White, "Exit Select", 550, 174, window);
    else
        drawText(sf::Color::White, "Select", 550, 174, window);
    if(_buttonState == B_LOADING_PATTERN)
        drawText(sf::Color::White, "Exit Load Pattern", 550, 222, window);
    else
        drawText(sf::Color::White, "Load Pattern", 550, 222, window);
    drawText(sf::Color::White, "Exit", 550, 270, window);

    //DRAW COLOR SELECTION BUTTONS
    drawText(sf::Color::White, "Colors:", 750, 30, window);
    drawText(sf::Color(15, 91, 255), "Blue", 750, 70, window);
    drawText(sf::Color(16, 237, 141), "Mint", 750, 110, window);
    drawText(sf::Color(154, 54, 255), "Purple", 750, 150, window);
    drawText(sf::Color(255, 20, 86), "Magenta", 750, 190, window);

    {
        drawText(sf::Color(231, 0, 0), "P", 750, 230, window);
        drawText(sf::Color(255, 140, 0), "r", 760, 230, window);
        drawText(sf::Color(255, 239, 0), "i", 772, 230, window);
        drawText(sf::Color(0, 129, 31), "d", 777, 230, window);
        drawText(sf::Color(0, 68, 255), "e", 788, 230, window);

    }
    drawText(sf::Color(170, 170, 170), "Random", 750, 270, window);


    //DRAW SAVE/LOAD & NUMBER BOXES
    if(_buttonState == B_SELECTING)
        drawText(sf::Color::White, "Pattern Save:", 550, 340, window);
    else
        drawText(sf::Color::White, "Save:", 550, 340, window);
    if(_buttonState == B_LOADING_PATTERN)
        drawText(sf::Color::White, "Pattern Load:", 750, 340, window);
    else
        drawText(sf::Color::White, "Load:", 750, 340, window);

    drawNumberBox(window, 550, 390);
    drawNumberBox(window, 750, 390);

}

/*
void sidebar::drawMenu(sf::RenderWindow &window) {
    //BASICALLY DRAW THE MENU ITEMS THROUGH A FOR LOOP,
    //SO GETTING THE MOUSE POSITION & CHANGE DISPLAY COLOR OF THE ITEMS
    //WILL BE A BIT EASIER.
//    for(pos_x = lef  )
}

void sidebar::drawItem(sf::RenderWindow &window, bool entered) {

}
*/

void sidebar::drawText(sf::Color color, string textString,
                  int pos_x, int pos_y, sf::RenderWindow &window) {
    //DRAWS A SINGLE STRING TO A DESTINED POSITION ON THE RENDERWINDOW
    sb_text.setString(textString);
    sb_text.setFillColor(color);
    sb_text.setPosition(pos_x, pos_y);
    window.draw(sb_text);
}

void sidebar::drawNumberBox(sf::RenderWindow &window, int leftTop_x, int leftTop_y) {
    //DRAW THE "NUMBER BOX" TO THE DESTINE POSITION ON THE RENDERWINDOW
    rect.setSize(sf::Vector2f(40, 40));
    rect.setFillColor(sf::Color::Black);
    rect.setOutlineThickness(2);
    rect.setOutlineColor(sf::Color(100, 100, 100));
    rect.setPosition(sf::Vector2f(550, 350));

    sf::Text text;
    int num = 0;
    std::string numString = "0";

    for(int row = 0; row < 3; row++) {
        for(int col = 0; col < 3; col++) {
            num++;
            int vectorX= leftTop_x + col*(42);
            int vectorY= leftTop_y + row*(42);
            rect.setPosition(sf::Vector2f(vectorX, vectorY));
            window.draw(rect);
            numString = std::to_string(num);
            drawText(sf::Color::White, numString, vectorX + 13, vectorY+5, window);
        }
    }

}

void sidebar::setButtonState(BUTTON_STATE buttonState) {
    _buttonState = buttonState;
}


