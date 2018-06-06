#include <iostream>
#include "game_of_life_sfml.h"

//#include "constants_variables.h"

void FillShapes(sf::RectangleShape shapeArray[][GRID_WIDTH],
                int themeNumber, bool world[][MAX_COL]){
    int Red = 0, Green = 0, Blue = 0;
    for (int row=0; row<GRID_HEIGHT; row++){
        for (int col=0; col<GRID_WIDTH; col++){
            int vectorY=row*(CELL_SIZE+1);
            int vectorX=col*(CELL_SIZE+1);
            shapeArray[row][col].setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
            shapeArray[row][col].setPosition(sf::Vector2f(vectorX,vectorY));
            //DISPLAYING THE GRID
            shapeArray[row][col].setOutlineThickness(1);
            shapeArray[row][col].setOutlineColor(sf::Color(50,50,50));
            //GENERATE COLOR
            colorGenerator(Red, Green, Blue, themeNumber);
            //NOW DISPLAY THE ARRAY
            if(world[row+1][col+1]) //if ALIVE
                shapeArray[row][col].setFillColor(sf::Color(Red, Green, Blue));
            else                           //if DEAD
                shapeArray[row][col].setFillColor(sf::Color(0,0,0));
        }
    }

}

void ShowShapes(sf::RenderWindow& window,
                sf::RectangleShape shapeArray[][GRID_WIDTH] ){
    for (int row=0; row<GRID_HEIGHT; row++){
        for (int col=0; col<GRID_WIDTH; col++){
            window.draw(shapeArray[row][col]);
        }
    }

}

void ClearShapes(sf::RectangleShape shapeArray[][GRID_WIDTH],
                 sf::RenderWindow &window) {
    for (int row=0; row<GRID_HEIGHT; row++){
        for (int col=0; col<GRID_WIDTH; col++){
            //CHANGE THE GRID TO BLACK
            shapeArray[row][col].setOutlineColor(sf::Color(0,0,0));
            //CHANGE THE SHAPE TO BLACK                         //if DEAD
            shapeArray[row][col].setFillColor(sf::Color(0,0,0));
            window.draw(shapeArray[row][col]);
        }
    }
}

void DrawNumberBox(sf::RenderWindow &window, int leftTop_x, int leftTop_y, sf::Font font) {
    sf::RectangleShape rec;
    rec.setSize(sf::Vector2f(40, 40));
    rec.setFillColor(sf::Color::Black);
//    rec.setFillColor(sf::Color::White);
    rec.setOutlineThickness(2);
    rec.setOutlineColor(sf::Color(100, 100, 100));
    rec.setPosition(sf::Vector2f(550, 350));
//    window.draw(rec);

    sf::Text text;
    int num = 0;
    std::string numString = "0";

    for(int row = 0; row < 3; row++) {
        for(int col = 0; col < 3; col++) {
            num++;
            int vectorX= leftTop_x + col*(42);
            int vectorY= leftTop_y + row*(42);
            rec.setPosition(sf::Vector2f(vectorX, vectorY));
            window.draw(rec);
            numString = std::to_string(num);
            DrawText(text, font, sf::Color::White, numString, vectorX + 12, vectorY+5, window);
        }
    }
}

void DrawText(sf::Text &text, sf::Font font, sf::Color color,
              std::string textString, int pos_x, int pos_y,
              sf::RenderWindow &window) {
    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(24);
    text.setFillColor(color);
    //try set the position (600, 30)
    text.setPosition(pos_x, pos_y);
    window.draw(text);

//    std::cout << textString << " is drawn at"
//              << text.getPosition().x << ','
//              << text.getPosition().y << std:: endl;
}

bool ButtonDetect(int mouse_x, int mouse_y, int leftTop_x, int leftTop_y,
                  int rightBottom_x, int rightBottom_y) {
    if((mouse_x >= leftTop_x && mouse_y >= leftTop_y)
        && (mouse_x <= rightBottom_x && mouse_y <= rightBottom_y))
        return true;
    else
        return false;
}

void colorGenerator(int &Red, int &Green, int &Blue, int themeNumber) {
    switch(themeNumber) {
        case 0: //purely random
            Red = Random(0, 255);
            Green = Random(0, 255);
            Blue = Random(0, 255);
            break;
        case 1: //blue theme
            Red = Random(0, 255);
            Green = 0.68 * Red + 81;
            if (Green > 255)
                Green = 255;
            Blue = 255;
            break;
        case 2: //green theme
            Red = Random(0, 255);
            Green = 255;
            Blue = 0.75 * Red + 63;
            if (Blue > 255)
                Blue = 255;
            break;
        case 3: //purple theme
            Green = Random(0, 255);
            Red = 0.5 * Green + 127;
            if (Red > 255)
                Red = 255;
            Blue = 255;
            break;
            //--bug: weird pink color (255, 0, 255)--
            //resolved by correcting Random function
        default:
            Red = 255;
            Green = 255;
            Blue = 255;
            break;
    }
}

int Random(int lo, int hi){
    int r = rand() % (hi + 1) + lo;
    //so if Random(0, 255)
    //== rand() % 256
    //returns int value in [0, 255]
    return r;
}
