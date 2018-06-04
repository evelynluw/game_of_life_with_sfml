#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <time.h>
#include "game_of_life.h"

const int SCREEN_WIDTH = 800;      //the demension of the window
const int SCREEN_HEIGHT = 600;
const int GRID_WIDTH = MAX_COL - 2;          //the "grid" on the screen
const int GRID_HEIGHT = MAX_ROW - 2;
const int CELL_SIZE = 10;
int themeNumber = 0;
int frameRate = 1;

using namespace std;

void ShowGrid(sf::RectangleShape shapeArray[][GRID_WIDTH]);
void FillShapes(sf::RectangleShape shapeArray[][GRID_WIDTH]);
void ShowShapes(sf::RenderWindow &window,
                sf::RectangleShape shapeArray[][GRID_WIDTH] );
void ProcessEvents(sf::RenderWindow &window);
bool processArray[MAX_ROW][MAX_COL];
void colorGenerator(int &Red, int &Green, int &Blue, int themeNumber);
int Random(int lo, int hi);


int main(int argc, char *argv[])
{
    //----------S E T U P ------------------------------:

    //declare a window object:
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML works!");
    //
    //VideoMode class has functions to detect screen size etc.
    //RenderWindow constructor has a third argumnet to set style
    //of the window: resize, fullscreen etc.
    //
    //or...
    // you could do this:
    //sf::RenderWindow window;
    //window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window!");
    //

    window.setFramerateLimit(frameRate);
    //This number is literally the framerate of this program.
    //increase the number to make the changes faster,
    //or decrease to make it slower.

    //this is where we keep all the shapes.
    sf::RectangleShape shapeArray[GRID_HEIGHT][GRID_WIDTH];


    window.setVerticalSyncEnabled(true); // call it once, after creating the window
    //Application runs at the same freq as monitor

    //. . . . . . . SHAPES ............
    //this is how you would declare and manipulate shapes:
    //sf::CircleShape shape(250.f);
    //shape.setFillColor(sf::Color::Green);
    //// set a 10-pixel wide orange outline
    //shape.setOutlineThickness(1);
    //shape.setOutlineColor(sf::Color(250, 150, 100));


    //// define a 120x50 rectangle
    //sf::RectangleShape rectangle(sf::Vector2f(120, 50));
    //// change the size to 100x100
    ////rectangle.setSize(sf::Vector2f(10, 10));
    //. . . . . . . . . . . . . . . . . . . . . . . . . . .

    // GAME OF LIFE
    // initialize the array
    initialize_2d(processArray);
    initial_config(processArray);

    //DISPLAY THE GRID
    ShowGrid(shapeArray);


    // run the program as long as the window is open
    while (window.isOpen())
    {
        //Process mouse and keyboard events:
        ProcessEvents(window);

        //necessary: get read for the next frame:
        window.clear();
        //        window.draw(shape);
        //        window.draw(rectangle);

        //set up the next frame:
        FillShapes(shapeArray);

        //draw the shapes on the window object:
        ShowShapes(window, shapeArray);

        //display the window and all its shapes:
        window.display();;

        //GAME OF LIFE
        //getting to the "next situation"
        step(processArray);
    }
    return 0;
}

void ProcessEvents(sf::RenderWindow &window){
    // check all the window's events that were triggered since the last iteration of the loop

    sf::Event event;

    //go through all the pending events: keyboard, mouse, close, resize, etc.
    //pollEvent and waitEvent are the only two functions that can fill event
    while (window.pollEvent(event))//or waitEvent
    {
        // check the type of the event...
        switch (event.type)
        {
        // window closed
        // "close requested" event: we close the window
        case sf::Event::Closed:
            window.close();
            break;

            // key pressed
        case sf::Event::KeyPressed:
            if(event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
                themeNumber = 0;
                std::cout<<"color: random"<<std::endl;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                themeNumber = 1;
                std::cout<<"color: blue"<<std::endl;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                themeNumber = 2;
                std::cout<<"color: green"<<std::endl;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                themeNumber = 3;
                std::cout<<"color: purple"<<std::endl;
            }
            // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)
            //     || sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
            //     frameRate += 2;
            //     std::cout<<"frameRate: "<<frameRate<<std::endl;
            // }
            //...
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
                std::cout<<"clearing"<<std::endl;
                initialize_2d(processArray);
            }
//            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if(event.key.code == sf::Keyboard::R) {
                std::cout<<"randomizing"<<std::endl;
                initial_random(processArray, 50);
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
                std::cout<<"exit program"<<std::endl;
                window.close();
            }
            break;
        case sf::Event::MouseButtonReleased:
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                std::cout << "the right button was pressed" << std::endl;
                std::cout << "mouse x: " << event.mouseButton.x << std::endl;
                std::cout << "mouse y: " << event.mouseButton.y << std::endl;
            }
            else{
                std::cout<<"left button?"<<std::endl;
                std::cout<<"randomizing"<<std::endl;
                initial_random(processArray, 50);
            }


            break;
        default:
            break;
        }
    }

}

void ShowGrid(sf::RectangleShape shapeArray[][GRID_WIDTH]) {
    for (int row=0; row<GRID_HEIGHT; row++){
        for (int col=0; col<GRID_WIDTH; col++){
            int vectorY=row*(CELL_SIZE+1);
            int vectorX=col*(CELL_SIZE+1);
            shapeArray[row][col].setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
            shapeArray[row][col].setPosition(sf::Vector2f(vectorX,vectorY));
            shapeArray[row][col].setFillColor(sf::Color(0,0,0));
            shapeArray[row][col].setOutlineThickness(1);
            shapeArray[row][col].setOutlineColor(sf::Color(50,50,50));
        }
    }
}


void FillShapes(sf::RectangleShape shapeArray[][GRID_WIDTH]){
    int Red = 0, Green = 0, Blue = 0;
    for (int row=0; row<GRID_HEIGHT; row++){
        for (int col=0; col<GRID_WIDTH; col++){
            int vectorY=row*(CELL_SIZE+1);
            int vectorX=col*(CELL_SIZE+1);
            shapeArray[row][col].setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
            shapeArray[row][col].setPosition(sf::Vector2f(vectorX,vectorY));
            colorGenerator(Red, Green, Blue, themeNumber);
            if(processArray[row+1][col+1]) //if ALIVE
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
            //bug: weird pink color (255, 0, 255)
        default:
            Red = 255;
            Green = 255;
            Blue = 255;
            break;
    }
}

int Random(int lo, int hi){
    int r = rand()%(hi+1)+lo+1;
    return r;
}
