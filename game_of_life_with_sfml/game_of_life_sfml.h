#ifndef GAME_OF_LIFE_SFML_H
#define GAME_OF_LIFE_SFML_H

#include "constants.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

void SaveSelection(sf::Vector2i LT, sf::Vector2i RB, bool tempArray[][MAX_COL], bool world[][MAX_COL]);
        //save the selection of world to the tempArray
void PasteSelection(sf::Vector2i LT, sf::Vector2i RB,
                    int mouse_i, int mouse_j, bool tempArray[][MAX_COL], bool world[][MAX_COL]);
        //paste the selection from the tempArray to world
bool SaveSelectionToFile(std::string fileName, sf::Vector2i LT, sf::Vector2i RB, bool world[][MAX_COL]);
        //save the selection of world to a text file with fileName. LT: leftTop. RB: RightBottom.
bool PasteSelectionFromFile(std::string fileName,
                       int mouse_i, int mouse_j, bool world[][MAX_COL]);
        //paste the selection from the file to world
void FillShapes(sf::RectangleShape shapeArray[][GRID_WIDTH],
                int themeNumber, bool world[][MAX_COL]);
        //fill the little rectangle shapes / grid
void ShowShapes(sf::RenderWindow &window,
                sf::RectangleShape shapeArray[][GRID_WIDTH] );
        //display the grid
void DrawText(sf::Text &text, sf::Font font, sf::Color color,
              std::string textString, int pos_x, int pos_y,
              sf::RenderWindow &window);
        //display the text with textString onto the window at pos
void DrawSelection(sf::RenderWindow &window, sf::Vector2i LT, sf::Vector2i mouseLoc);
        //draw the selection rectangle
bool ButtonDetect(int mouse_x, int mouse_y, int leftTop_x, int leftTop_y,
                  int rightBottom_x, int rightBottom_y);
        //returns true if mouse press is inside of the detection area rectangle
void colorGenerator(int &Red, int &Green, int &Blue, int themeNumber);
        //generates color for every "cell"
void pixelToCell(int pixel_x, int pixel_y, int &i, int &j);
        //convert pixel location to the cell location corresponding to the world array
void cellToPixel(int i, int j, sf::Vector2f &pixelLoc);
        //convert the cell location corresponding to the world array to the pixel location on the screen
int Random(int lo, int hi);
        //generate random int in [lo, hi]
void swapInt(int &a, int &b, bool condition);
        //swap the value of a and b


#endif // GAME_OF_LIFE_SFML_H
