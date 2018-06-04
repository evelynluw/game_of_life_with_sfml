#ifndef GAME_OF_LIFE_SFML_H
#define GAME_OF_LIFE_SFML_H

void FillShapes(sf::RectangleShape shapeArray[][GRID_WIDTH]);
void ShowShapes(sf::RenderWindow &window,
                sf::RectangleShape shapeArray[][GRID_WIDTH] );
void ClearShapes(sf::RectangleShape shapeArray[][GRID_WIDTH],
                 sf::RenderWindow &window);
void DrawText(sf::Text &text, sf::Font font,
              string textString, sf::RenderWindow &window);
void colorGenerator(int &Red, int &Green, int &Blue, int themeNumber);
int Random(int lo, int hi);


#endif // GAME_OF_LIFE_SFML_H
