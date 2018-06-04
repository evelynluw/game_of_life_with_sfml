/* TODO:
 * 1. text buttons
 * 2. save / load
 * 3. drag to make cells alive
 * 4. change color according how long cells have lived
 */

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
int frameRate = 5;
bool world[MAX_ROW][MAX_COL];

using namespace std;

void ProcessEvents(sf::RenderWindow &window);


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
    initialize_2d(world);
    initial_config(world);

    //DISPLAY THE GRID

    //SHOW TEXT BUTTONS
    sf::Font font;
    if(!font.loadFromFile("../res/sunflower.ttf")) {
        std::cout << "open font error" << std::endl;
    }
    sf::Text button1;
//    DrawText(button1, font, "Button1", window);


    // run the program as long as the window is open
    while (window.isOpen())
    {
        //Process mouse and keyboard events:
        ProcessEvents(window);

        //necessary: get read for the next frame:
        window.clear();
        //GET RID OF WINDOW CLEAR.
        //ONLY CLEAR THE RECTANGLE ARRAY
        //        window.draw(shape);
        //        window.draw(rectangle);

        DrawText(button1, font, "Button1", window);

        //set up the next frame:
        FillShapes(shapeArray);

        //draw the shapes on the window object:
        ShowShapes(window, shapeArray);

        //display the window and all its shapes:
        window.display();;

        //GAME OF LIFE
        //getting to the "next situation"
        step(world);
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
            //USE CTRL+NUM TO CHANGE COLOR SCHEME
            //this is not handled in an elegant way right now.
            //however the low framerates limits the usability
            //of nested if brackets
            if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                    && sf::Keyboard::isKeyPressed(sf::Keyboard::Num0)) {
                themeNumber = 0;
                std::cout<<"color: random"<<std::endl;
            }
            if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                    && sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                themeNumber = 1;
                std::cout<<"color: blue"<<std::endl;
            }
            if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                    && sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                themeNumber = 2;
                std::cout<<"color: green"<<std::endl;
            }
            if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                    || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                    && sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                themeNumber = 3;
                std::cout<<"color: purple"<<std::endl;
            }

            //ATTEMPTING TO INCREASE THE FRAMERATE
            //DOESNT WORK.
            // if(sf::Keyboard::isKeyPressed(sf::Keyboard::Equal)
            //     || sf::Keyboard::isKeyPressed(sf::Keyboard::Add)) {
            //     frameRate += 2;
            //     std::cout<<"frameRate: "<<frameRate<<std::endl;
            // }
            //...

            //CLEAR THE WORLD
            if(event.key.code == sf::Keyboard::C) {
                std::cout<<"clearing"<<std::endl;
                initialize_2d(world);
            }
            //ADD 50 RANDOM LIVING CELLS TO THE WORLD
            if(event.key.code == sf::Keyboard::R) {
                std::cout<<"randomizing"<<std::endl;
                initial_random(world, 50);
            }
            //EXIT WITH X
            if(event.key.code == sf::Keyboard::X) {
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
            }


            break;
        default:
            break;
        }
    }

}
