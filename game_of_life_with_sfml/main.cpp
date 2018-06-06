/* TODO:
 * 1. text buttons
 * 2. save / load
 * 3. drag to make cells alive
 * 4. change color according how long cells have lived
 */

#include <iostream>
#include <time.h>
#include "game_of_life.h"
#include "game_of_life_sfml.h"
#include "constants.h"

int themeNumber = 0;
int frameRate = 5;
bool world[MAX_ROW][MAX_COL];
bool paused = false;

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
    sf::Text textButton;

    sf::RectangleShape recShape;

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


        //DRAW MAIN FUNCTION BUTTONS
        DrawText(textButton, font, sf::Color::White, "Pause", 550, 30, window);
        DrawText(textButton, font, sf::Color::White, "Resume", 550, 90, window);
        DrawText(textButton, font, sf::Color::White, "Random", 550, 150, window);
        DrawText(textButton, font, sf::Color::White, "Clear", 550, 210, window);
        DrawText(textButton, font, sf::Color::White, "Exit", 550, 270, window);

        //DRAW COLOR SELECTION BUTTONS
        DrawText(textButton, font, sf::Color::White, "Colors:", 750, 30, window);
        DrawText(textButton, font, sf::Color(15, 91, 255), "Blue", 750, 70, window);
        DrawText(textButton, font, sf::Color(16, 237, 141), "Mint", 750, 110, window);
        DrawText(textButton, font, sf::Color(154, 54, 255), "Purple", 750, 150, window);

        //DRAW SAVE/LOAD NUMBER BOXES
        DrawNumberBox(window, 550, 350, font);

        //set up the next frame:
        FillShapes(shapeArray, themeNumber, world);

        //draw the shapes on the window object:
        ShowShapes(window, shapeArray);

        //display the window and all its shapes:
        window.display();

        //GAME OF LIFE
        //getting to the "next situation"
        if(!paused) {
            step(world);
        }
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
                sf::Vector2f mousePosition;

                std::cout << "the right button was pressed" << std::endl;
                mousePosition.x = event.mouseButton.x;
                mousePosition.y = event.mouseButton.y;
                std::cout << "mouse x: " << mousePosition.x << std::endl;
                std::cout << "mouse y: " << mousePosition.y << std::endl;






            }
            else{
                std::cout<<"left button?"<<std::endl;

                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                //IF TEXT COLOR NEEDS TO BE CHANGED...
                sf::Font font;
                if(!font.loadFromFile("../res/sunflower.ttf")) {
                    std::cout << "open font error" << std::endl;
                }
                sf::Text textButton;

//                Pause: the right button was pressed
//                mouse x: 595
//                mouse y: 31
//                the right button was pressed
//                mouse x: 669
//                mouse y: 60
//                left button?
//                Resume: the right button was pressed
//                mouse x: 599
//                mouse y: 93
//                the right button was pressed
//                mouse x: 691
//                mouse y: 122

                if(ButtonDetect(x, y, 544, 30, 620, 60)) {
                    //PAUSE BUTTON DETECTION
                    std::cout << "Paused" << std::endl;
                    paused = true;
                }

                if(ButtonDetect(x, y, 544, 93, 640, 122)) {
                    std::cout << "Resumed" << std::endl;
                    paused = false;
                }

                if(ButtonDetect(x, y, 544, 150, 640, 179)) {
                    //RANDOM BUTTON DETECTION
                    std::cout << "Randomizing" << std::endl;
                    initial_random(world, 50);
//                    DrawText(textButton, font, sf::Color::Yellow, "Random", 550, 150, window);
                }

                if(ButtonDetect(x, y, 544, 210, 605, 237)) {
                    //CLEAR BUTTON DETECTION
                    std::cout << "clearing" << std::endl;
                    initialize_2d(world);

                }

                if(ButtonDetect(x, y, 544, 268, 600, 300)) {
                    //EXIT BUTTON DETECTION
                    std::cout << "exiting" << std::endl;
                    window.close();
                }


            }


            break;
        default:
            break;
        }
    }

}
