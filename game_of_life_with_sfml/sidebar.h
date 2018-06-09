#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
//all the components in the class
//are copied from single ball..

class sidebar
{
public:
    sidebar();
    void draw(sf::RenderWindow& window);
    void drawMenu(sf::RenderWindow &window);
    void drawItem(sf::RenderWindow &window, bool entered);
    void drawText(sf::Color color, std::string textString,
                  int pos_x, int pos_y, sf::RenderWindow &window);
    void drawNumberBox(sf::RenderWindow &window, int leftTop_x, int leftTop_y);
    void setMousePos(float mouse_x, float mouse_y);
    string& operator [](int index);
    bool paused = false;
    bool selecting = false;
private:
    sf::RectangleShape rect;
    vector<string> items;
    sf::Font font;
    sf::Text sb_text;
    float _leftTop_x;
    float _leftTop_y;
    float _width;
    float _mouse_x;
    float _mouse_y;
};

#endif // SIDEBAR_H
