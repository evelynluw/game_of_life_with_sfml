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
    animate();
    void run();
    void processEvents();
    void update();
    void render();
    void Draw();
private:
    sf::RenderWindow window;
    sf::CircleShape mousePoint;
    int command;
    sf::Font font;
    sf::Text myTextLabel;
//    bool mouseIn;
    sidebar sideBar;
    int themeNumber = 0;
    int frameRate = 5;
    bool world[MAX_ROW][MAX_COL];
    sf::RectangleShape shapeArray[GRID_HEIGHT][GRID_WIDTH];
//    bool paused = false;
//    bool selecting = false;
    sf::Vector2i select_LT; //LeftTop
    sf::Vector2i select_RB; //RightBottom
    STATE state = NORMAL;
    bool tempArray[MAX_ROW][MAX_COL];
    std::string fileName = "\0";

//    sf::Vector2f mouseLoc;
};

string mouse_pos_string(sf::RenderWindow& window);

#endif // ANIMATE_H
