#ifndef GAME_OF_LIFE_SFML_H
#define GAME_OF_LIFE_SFML_H

#include "constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void SaveSelection(sf::Vector2i LT, sf::Vector2i RB, bool tempArray[][MAX_COL], bool world[][MAX_COL]);
void PasteSelection(sf::Vector2i LT, sf::Vector2i RB,
                    int mouse_i, int mouse_j, bool tempArray[][MAX_COL], bool world[][MAX_COL]);
bool SaveSelectionToFile(std::string fileName, sf::Vector2i LT, sf::Vector2i RB, bool world[][MAX_COL]);
bool PasteSelectionFromFile(std::string fileName,
                       int mouse_i, int mouse_j, bool world[][MAX_COL]);
void FillShapes(sf::RectangleShape shapeArray[][GRID_WIDTH],
                int themeNumber, bool world[][MAX_COL]);
void ShowShapes(sf::RenderWindow &window,
                sf::RectangleShape shapeArray[][GRID_WIDTH] );
void ClearShapes(sf::RectangleShape shapeArray[][GRID_WIDTH],
                 sf::RenderWindow &window);
//void DrawNumberBox(sf::RenderWindow &window, int leftTop_x, int leftTop_y, sf::Font font);
void DrawText(sf::Text &text, sf::Font font, sf::Color color,
              std::string textString, int pos_x, int pos_y,
              sf::RenderWindow &window);
void DrawSelection(sf::RenderWindow &window, sf::Vector2i LT, sf::Vector2i mouseLoc);
bool ButtonDetect(int mouse_x, int mouse_y, int leftTop_x, int leftTop_y,
                  int rightBottom_x, int rightBottom_y);
void colorGenerator(int &Red, int &Green, int &Blue, int themeNumber);
void pixelToCell(int pixel_x, int pixel_y, int &i, int &j);
void cellToPixel(int i, int j, sf::Vector2f &pixelLoc);
int Random(int lo, int hi);
void swapInt(int &a, int &b, bool condition);


#endif // GAME_OF_LIFE_SFML_H
