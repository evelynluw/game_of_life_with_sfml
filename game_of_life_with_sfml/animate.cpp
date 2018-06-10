#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "constants.h"
#include "animate.h"
#include "sidebar.h"
#include "game_of_life.h"
#include "game_of_life_sfml.h"


animate::animate()
{
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game of Life");
    window.setFramerateLimit(frameRate);
    window.setVerticalSyncEnabled(true);

    // GAME OF LIFE
    // initialize the array
    initialize_2d(world);
    initial_config(world);

}

void animate::run() {
    while (window.isOpen()) {
      processEvents();
      update();
      render(); //clear/draw/display
    }
      cout<<endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;
}

void animate::processEvents() {
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
        case sf::Event::Closed:{
            window.close();
            break;

            // key pressed
        }
        case sf::Event::KeyPressed:{
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
                std::cout<<"color: mint"<<std::endl;
            }
            if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                    && sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                themeNumber = 3;
                std::cout<<"color: purple"<<std::endl;
            }
            if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                    && sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
                themeNumber = 4;
                std::cout<<"color: magenta"<<std::endl;
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

            if(event.key.code == sf::Keyboard::L) {
                std::cout << "loading from ";
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
                    std::cout << "1" << std::endl;
                    std::string fileName = "\0";
                    fileName = std::to_string(1);
                    fileName += ".txt";
                    read2dBoolArray(fileName, world);
                }
            }

            if(event.key.code == sf::Keyboard::S) {
                std::cout << "saving to ";
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){
                    std::cout << "1" << std::endl;
                    std::string fileName = "\0";
                    fileName = std::to_string(1);
                    fileName += ".txt";
                    write2dBoolArray(fileName, world);
                }
            }

            if(event.key.code == sf::Keyboard::E) {
//                std::cout << "selecting ... "<<std::endl;
//                sidebar.state = sele
            }

            break;
        }
        case sf::Event::MouseMoved:{
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
                    && state == NORMAL) {
                int x = sf::Mouse::getPosition().x - window.getPosition().x - 5;
                int y = sf::Mouse::getPosition().y - window.getPosition().y - 30;
                if(ButtonDetect(x, y, 0, 0, 520, 520)) {
                    int i = y / (CELL_SIZE + 1) + 1;
                    int j = x / (CELL_SIZE + 1) + 1;
                    if(!world[i][j])
                        world[i][j] = true;
                    fill_margin(world);
                    std::cout<<"tile is drawn"<<std::endl;
                }
            }
            break;
        }
        case sf::Event::MouseButtonPressed:{
            std::cout<<"MouseButtonPressed"<<std::endl;
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                int x = event.mouseButton.x;
                int y = event.mouseButton.y;
                if(ButtonDetect(x, y, 0, 0, 520, 520)) {
                    //  DETECTION IF MOUSE IS INSIDE THE GRID AREA

                        //2. get the mouse position & convert it to i, j...
                        //(go to grid mouse event detection part)
                    //PUT THEM INTO SIDEBAR AS VARIABLES
//                        int LT_i = 0;       //LeftTop
//                        int LT_j = 0;
//                        int RB_i = 0;       //RightBottom
//                        int RB_j = 0;

                        switch (state) {
                        //2.1. get press down / left-top pos & i, j
                        case SELECTING_MOUSE_NOT_PRESSED: {
                            std::cout<<"SELECTING_MOUSE_NOT_PRESSED"<<std::endl;
                            pixelToCell(x, y, select_LT.x, select_LT.y);
                            std::cout << "LT select pos registered" << std::endl;
                            state = SELECTING_MOUSE_PRESSED;    //SET TO NEXT SELECT STATE
                            std::cout<<"LT: "<<x<<", "<<y<<"; "
                                    <<select_LT.x<<", "<<select_LT.y<<std::endl;
                            //NOW IT SHOULD EXIT PROCESS EVENTS & DRAW A DOT AT LT
                            //                            circle.setPosition(event.mouseButton.x, event.mouseButton.y);
                            //                            window.draw(circle);
                            //                            std::cout<<"circle 1 drawn"<<std::endl; set the draw flag true?
                            //                            selectStep = 1;
                            break;
                        }
                        default: {
                            //DRAWING MODE, NOT SELECTING
                            std::cout<<"MOUSE IN GRID, DRAWING MODE"<<std::endl;
                            int i = 0;
                            int j = 0;
                            pixelToCell(x, y, i, j);
                            if(!world[i][j])
                                world[i][j] = true;
                            fill_margin(world);
                            std::cout<<"tile is drawn"<<std::endl;
                            break;
                        }
                        }

                }
            }
            break;
        }
        case sf::Event::MouseButtonReleased:{
            if (event.mouseButton.button == sf::Mouse::Right)
            {
                std::cout << "the right button was pressed" << std::endl;
                std::cout << "mouse x: " << event.mouseButton.x << ", "
                          << event.mouseButton.x * 1.0 / window.getSize().x  << std::endl;
                std::cout << "mouse y: " << event.mouseButton.y << ", "
                          << event.mouseButton.y * 1.0 / window.getSize().y << std::endl;
                std::cout << "window size:" << window.getSize().x << 'x'
                          << window.getSize().y << std::endl;

            }
            else if (event.mouseButton.button == sf::Mouse::Left) {
                std::cout<<"left button pressed"<<std::endl;

                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                if(ButtonDetect(x, y, 0, 0, 520, 520)) {
                    //  DETECTION IF MOUSE IS INSIDE THE GRID AREA
                    if(state == SELECTING_MOUSE_PRESSED) {
                        std::cout<<"SELECTING_MOUSE_PRESSED"<<std::endl;
                        pixelToCell(x, y, select_RB.x, select_RB.y);
                        std::cout << "RB select point registered" << std::endl;
                        state = PASTING;    //CHANGE THE STATE to PASTING
                        std::cout<<"RB: "<<x<<", "<<y<<"; "
                                <<select_RB.x<<", "<<select_RB.y<<std::endl;
                        //NOW SAVE THE REGION TO A TEMPARRAY (WILL CHANGE TO FILES)
                        SaveSelection(select_LT, select_RB, tempArray, world);
                        std::cout<<"SELECTION SAVED"<<std::endl;
                        //THE CONFUSION READER MAY HAVE : select_LT.x is actually "i"
                    }
                    else if(state == PASTING) {
                        std::cout<<"PASTING MODE"<<std::endl;
                        int mouse_i = 0;
                        int mouse_j = 0;
                        pixelToCell(x, y, mouse_i, mouse_j);
                        PasteSelection(select_LT, select_RB,
                                       mouse_i, mouse_j, tempArray, world);
                        std::cout<<"SELECTION PASTED"<<std::endl;
                        state = PAUSED;
                    }
                }

                if(ButtonDetect(x, y, 544, 30, 620, 60)) {
                    //PAUSE BUTTON DETECTION
                    //                    if(!paused) {
                    if(state != PAUSED) {
                        //NOT PAUSED YET, SO SET TO PAUSED
                        state = PAUSED;
                        sideBar.setButtonState(B_PAUSED);
                        std::cout << "Paused" << std::endl;
                    } else {
                        //ALREADY PAUSED, SO RESUME
                        state = NORMAL;
                        sideBar.setButtonState(B_NORMAL);
                        std::cout << "Resumed" << std::endl;
                    }
                }
                if(ButtonDetect(x, y, 544, 90, 640, 120)) {
                    //RANDOM BUTTON DETECTION
                    std::cout << "Randomizing" << std::endl;
                    initial_random(world, 50);
                    //                    DrawText(textButton, font, sf::Color::Yellow, "Random", 550, 150, window);
                }
                if(ButtonDetect(x, y, 544, 150, 605, 180)) {
                    //CLEAR BUTTON DETECTION
                    std::cout << "clearing" << std::endl;
                    initialize_2d(world);

                }
                if(ButtonDetect(x, y, 544, 210, 600, 240)) {
                    //EXIT BUTTON DETECTION
                    std::cout << "exiting" << std::endl;
                    window.close();
                }
                if(ButtonDetect(x, y, 544, 270, 600, 300)) {
                    //SELECT BUTTON DETECTION

                    //1. set the flag to true/false
                    if (state == SELECTING_MOUSE_NOT_PRESSED
                            || state == SELECTING_MOUSE_PRESSED){
                        //ALREADY IN SELECTING MODE. NOW QUIT S.M.
                        state = NORMAL;
                        std::cout << "exit selecting mode" << std::endl;
                    } else {
                        //NOT IN SELECTING MODE, THEN ENTER S.M.
                        state = SELECTING_MOUSE_NOT_PRESSED;
                        std::cout << "enter selecting mode" << std::endl;
                    }
                    //2. get the mouse position & convert it to i, j...
                    //go to grid mouse event detection part
                }

                //FOR SAVE TO SLOTS:
                int num = 0;
                for(int row = 0; row < 3; row++) {
                    for(int col = 0; col < 3; col++) {
                        num++;
                        int vectorX= 550 + col*(42);
                        int vectorY= 390 + row*(42);
                        if(ButtonDetect(x, y, vectorX, vectorY,
                                        vectorX + 42, vectorY + 42)) {
                            std::cout << "saving to " << num << std::endl;
                            std::string fileName = "\0";
                            fileName = std::to_string(num);
                            fileName += ".txt";
                            if(!write2dBoolArray(fileName, world))
                                std::cout << "save failed" << std::endl;
                        }
                    }
                }

                //FOR LOAD FROM SLOTS:
                num = 0;

                for(int row = 0; row < 3; row++) {
                    for(int col = 0; col < 3; col++) {
                        num++;
                        int vectorX= 750 + col*(42);
                        int vectorY= 390
                                + row*(42);
                        if(ButtonDetect(x, y, vectorX, vectorY,
                                        vectorX + 42, vectorY + 42)) {
                            std::cout << "loading from " << num << std::endl;
                            std::string fileName = "\0";
                            fileName = std::to_string(num);
                            fileName += ".txt";
                            if(!read2dBoolArray(fileName, world))
                                std::cout << "load failed" << std::endl;
                        }
                    }
                }

                //FOR DRAWING ON THE GRID:

                //                if(ButtonDetect(x, y, 0, 0, 520, 520)) {
                //                    int i = y / (CELL_SIZE + 1) + 1;
                //                    int j = x / (CELL_SIZE + 1) + 1;
                //                    if(world[i][j])
                //                        world[i][j] = false;
                //                    else
                //                        world[i][j] = true;
                //                    fill_margin(world);
                //                }


            }
            break;
        }
        default:
            break;
        }
    }

}

void animate::update() {
    if(state == NORMAL) {
        //IF THE GAME IS NOT PAUSED...
        step(world);
    }
}

void animate::render() {
    window.clear();
    FillShapes(shapeArray, themeNumber, world);
    ShowShapes(window, shapeArray);
    sideBar.draw(window);
    window.display();

}

void animate::Draw() {

}
