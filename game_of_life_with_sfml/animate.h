#ifndef ANIMATE_H
#define ANIMATE_H
#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "sidebar.h"
//#include "game_of_life.h"
//#include "game_of_life_sfml.h"

class animate
{
public:
    //CTOR
    animate();
    void run();             //run the game
    void processEvents();   //handle events, e.g. mouse clicks, key pressings
    void update();          //change the state of the game
    void render();          //render the game: clear, draw, display
private:
    sf::RenderWindow window;
    sf::Font font;
    sidebar sideBar;
    int themeNumber = 0;
    int frameRate = 8;
    bool world[MAX_ROW][MAX_COL];
    sf::RectangleShape shapeArray[GRID_HEIGHT][GRID_WIDTH];
    sf::Vector2i select_LT; //LeftTop
    sf::Vector2i select_RB; //RightBottom
    STATE state = NORMAL;
    bool tempArray[MAX_ROW][MAX_COL];
    std::string fileName = "\0";
};

string mouse_pos_string(sf::RenderWindow& window);

#endif // ANIMATE_H
