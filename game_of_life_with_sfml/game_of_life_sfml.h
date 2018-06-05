#ifndef GAME_OF_LIFE_SFML_H
#define GAME_OF_LIFE_SFML_H

#include "constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void FillShapes(sf::RectangleShape shapeArray[][GRID_WIDTH],
                int themeNumber, bool world[][MAX_COL]);
void ShowShapes(sf::RenderWindow &window,
                sf::RectangleShape shapeArray[][GRID_WIDTH] );
void ClearShapes(sf::RectangleShape shapeArray[][GRID_WIDTH],
                 sf::RenderWindow &window);
void DrawText(sf::Text &text, sf::Font font,
              std::string textString, int pos_x, int pos_y,
              sf::RenderWindow &window);
void ButtonDetect(sf::Vector2f position, int mouse_x, int mouse_y);
void colorGenerator(int &Red, int &Green, int &Blue, int themeNumber);
int Random(int lo, int hi);


#endif // GAME_OF_LIFE_SFML_H
