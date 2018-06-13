#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "constants.h"
using namespace std;
//all the components in the class
//are copied from single ball..

class sidebar
{
public:
    sidebar();  //CTOR
    void draw(sf::RenderWindow& window);        //draw the sidebar
//    void drawMenu(sf::RenderWindow &window);
//    void drawItem(sf::RenderWindow &window, bool entered);
    void drawText(sf::Color color, std::string textString,
                  int pos_x, int pos_y, sf::RenderWindow &window);
        //draw text with these identities
    void drawNumberBox(sf::RenderWindow &window, int leftTop_x, int leftTop_y);
        //draw number box for saving / loading
    void setButtonState(BUTTON_STATE buttonState);
        //set the button state to buttonState
    const float _button_width = 70;
    const float _button_height = 24;
    const float _button_spacing = 36;
//    bool paused = false;
//    bool selecting = false;
//    STATE state = NORMAL;
private:
    sf::RectangleShape rect;
//    vector<string> items;
    sf::Font font;
    sf::Text sb_text;
    float _leftTop_x;
    float _leftTop_y;
    float _mouse_x;
    float _mouse_y;
    sf::Vector2f _mouseLoc;
    BUTTON_STATE _buttonState = B_NORMAL;
//    string itemStringList[] =
//        {"Resume",
//        "Random",
//        "Clear",
//        "Exit",
//        "Select",};
};

#endif // SIDEBAR_H
