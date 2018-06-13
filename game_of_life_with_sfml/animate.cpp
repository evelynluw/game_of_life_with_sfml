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
    //CTOR AND CREATES THE WINDOW, INITIALIZE ARRAYS

    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Game of Life");
    window.setFramerateLimit(frameRate);
    window.setVerticalSyncEnabled(true);

    // GAME OF LIFE
    // initialize the array
    initialize_2d(world);
    initial_config(world);

}

void animate::run() {
    //RUN THE GAME
    while (window.isOpen()) {
      processEvents();
      update();
      render(); //clear/draw/display
    }
      cout<<endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;
}

void animate::processEvents() {
    //HANDLE EVENTS, E.G. MOUSE CLICKS, KEY PRESSINGS.
    //CHECKED DURING EVERY ITERATION OF THE WHILE LOOP IN RUN

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
            if((sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)
                || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl))
                    && sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) {
                themeNumber = 5;
                std::cout<<"color: pride"<<std::endl;
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
                if(state != ERASING) {
                    std::cout <<"erasing"<<std::endl;
                    state = ERASING;
                } else {
                    std::cout <<"normal mode"<<std::endl;
                    state = PAUSED;
                }
            }

            break;
        }
        case sf::Event::MouseMoved:{
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
                    && (state == NORMAL || state == PAUSED)) {
                state = PAUSED;
                sideBar.setButtonState(B_PAUSED);
                int x = sf::Mouse::getPosition(window).x;
                int y = sf::Mouse::getPosition(window).y;
                if(ButtonDetect(x, y, 0, 0, 520, 520)) {
                    int i = y / (CELL_SIZE + 1) + 1;
                    int j = x / (CELL_SIZE + 1) + 1;
                    if(!world[i][j])
                        world[i][j] = true;
                    fill_margin(world);
                    std::cout<<"tile is drawn (MOVE)"<<std::endl;
                }
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)
                    && (state == ERASING)) {
                sideBar.setButtonState(B_PAUSED);
                int x = sf::Mouse::getPosition(window).x;
                int y = sf::Mouse::getPosition(window).y;
                if(ButtonDetect(x, y, 0, 0, 520, 520)) {
                    int i = y / (CELL_SIZE + 1) + 1;
                    int j = x / (CELL_SIZE + 1) + 1;
                    if(world[i][j])
                        world[i][j] = false;
                    fill_margin(world);
                    std::cout<<"tile is erased (MOVE)"<<std::endl;
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
                        case SELECTING_MOUSE_NOT_PRESSED:
                        {
                            std::cout<<"SELECTING_MOUSE_NOT_PRESSED"<<std::endl;
//                            pixelToCell(x, y, select_LT.x, select_LT.y);
                            select_LT.x = x;
                            select_LT.y = y;
                            std::cout << "LT select pos registered" << std::endl;
                            state = SELECTING_MOUSE_PRESSED;    //SET TO NEXT SELECT STATE
                            std::cout<<"LT: "<<x<<", "<<y<<"; "
                                    <<select_LT.x<<", "<<select_LT.y<<std::endl;
                            //NOW IT SHOULD EXIT PROCESS EVENTS & START DRAWING RECTANGLE
                            break;
                        }
                        case PAUSED:
                        case NORMAL: {
                            //DRAWING MODE, NOT SELECTING
                            std::cout<<"MOUSE IN GRID, DRAWING MODE"<<std::endl;
                            state = PAUSED;
                            sideBar.setButtonState(B_PAUSED);
                            int i = 0;
                            int j = 0;
                            pixelToCell(x, y, i, j);
                            if(!world[i][j])
                                world[i][j] = true;
                            fill_margin(world);
                            std::cout<<"tile is drawn (PRESS)"<<std::endl;
                            break;
                        }
                        case ERASING: {
                            //ERASING MODE
                            std::cout<<"MOUSE IN GRID, DRAWING MODE"<<std::endl;
                            sideBar.setButtonState(B_PAUSED);
                            int i = 0;
                            int j = 0;
                            pixelToCell(x, y, i, j);
                            if(world[i][j])
                                world[i][j] = false;
                            fill_margin(world);
                            std::cout<<"tile is erased (PRESS)"<<std::endl;
                            break;
                        }
                        default:
                            break;
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
                std::cout<<"left button released"<<std::endl;

                int x = event.mouseButton.x;
                int y = event.mouseButton.y;

                if(ButtonDetect(x, y, 0, 0, 520, 520)) {
                    //  DETECTION IF MOUSE IS INSIDE THE GRID AREA
                    if(state == SELECTING_MOUSE_PRESSED) {
                        std::cout<<"SELECTING_MOUSE_PRESSED"<<std::endl;
//                        pixelToCell(x, y, select_RB.x, select_RB.y);
                        select_RB.x = x;
                        select_RB.y = y;
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
                        sideBar.setButtonState(B_NORMAL);
                    }
                    else if(state == LOADING_PATTERN) {
                        std::cout<<"READY TO LOAD PATTERN"<<std::endl;
                        int mouse_i = 0;
                        int mouse_j = 0;
                        pixelToCell(x, y, mouse_i, mouse_j);
                        if(!PasteSelectionFromFile(fileName, mouse_i, mouse_j, world)) {
                            std::cout<<"paste selection failed"<<std::endl;
                        }
                        std::cout<<"PATTERN LOADED"<<std::endl;
//                        state = PAUSED;
//                        sideBar.setButtonState(B_NORMAL);
                    }
                }

                //SIDEBAR BUTTONS DETECTION: START FROM (550, 30)
                //DISTANCE BETWEEN ITEM LT POINTS: 48.
                //48 = 24(HEIGHT OF AN ITEM) + 24(SPACING BETWEEN ITEMS)
                if(ButtonDetect(x, y, 550, 30, 640, 60)) {
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
                if(ButtonDetect(x, y, 550, 78, 640, 108)) {
                    //RANDOM BUTTON DETECTION
                    std::cout << "Randomizing" << std::endl;
                    initial_random(world, 50);
                    //                    DrawText(textButton, font, sf::Color::Yellow, "Random", 550, 150, window);
                }
                if(ButtonDetect(x, y, 550, 126, 640, 156)) {
                    //CLEAR BUTTON DETECTION
                    std::cout << "clearing" << std::endl;
                    initialize_2d(world);

                }
                if(ButtonDetect(x, y, 550, 174, 640, 204)) {
                    //SELECT BUTTON DETECTION

                    //1. set the flag to true/false
                    if (state == SELECTING_MOUSE_NOT_PRESSED
                            || state == SELECTING_MOUSE_PRESSED
                            || state == PASTING){
                        //ALREADY IN SELECTING MODE. NOW QUIT S.M.
                        state = PAUSED;
                        sideBar.setButtonState(B_NORMAL);
                        std::cout << "exit selecting mode" << std::endl;
                    } else {
                        //NOT IN SELECTING MODE, THEN ENTER S.M.
                        state = SELECTING_MOUSE_NOT_PRESSED;
                        sideBar.setButtonState(B_SELECTING);
                        std::cout << "enter selecting mode" << std::endl;
                    }
                    //2. get the mouse position & convert it to i, j...
                    //go to grid mouse event detection part
                }
                if(ButtonDetect(x, y, 550, 222, 660, 252)) {
//                    if(ButtonDetect(x, y, 550, 270, 640, 300)) {
                    //LOAD PATTERNS BUTTON DETECTION
                    if(state != LOADING_PATTERN){
                        state = LOADING_PATTERN;
                        sideBar.setButtonState(B_LOADING_PATTERN);
                    } else {
                        state = PAUSED;
                        sideBar.setButtonState(B_NORMAL);
                    }
                }
                if(ButtonDetect(x, y, 550, 270, 640, 300)) {
                    //EXIT BUTTON DETECTION
                    std::cout << "exiting" << std::endl;
                    window.close();
                }

                //COLOR SETTINGS
                {
                    if(ButtonDetect(x, y, 750, 70, 850, 100)) {
                        //BLUE
                        themeNumber = 1;
                        std::cout<<"color: blue"<<std::endl;

                    }
                    if(ButtonDetect(x, y, 750, 110, 850, 140)) {
                        //MINT
                        themeNumber = 2;
                        std::cout<<"color: mint"<<std::endl;
                    }
                    if(ButtonDetect(x, y, 750, 150, 850, 180)) {
                        //PURPLE
                        themeNumber = 3;
                        std::cout<<"color: purple"<<std::endl;
                    }
                    if(ButtonDetect(x, y, 750, 190, 850, 220)) {
                        //MAGENTA
                        themeNumber = 4;
                        std::cout<<"color: magenta"<<std::endl;
                    }
                    if(ButtonDetect(x, y, 750, 230, 850, 260)) {
                        //PRIDE
                        themeNumber = 5;
                        std::cout<<"color: pride"<<std::endl;
                    }
                    if(ButtonDetect(x, y, 750, 270, 850, 300)) {
                        //PRIDE
                        themeNumber = 0;
                        std::cout<<"color: random"<<std::endl;
                    }
                }

                //FOR SAVE TO SLOTS:
                if(ButtonDetect(x, y, 550, 390, 676, 516)) {
                    //IF PRESSED INSIDE FIRST NUMBER BOX
                    int num = 0;
                    for(int row = 0; row < 3; row++) {
                        for(int col = 0; col < 3; col++) {
                            num++;
                            int vectorX= 550 + col*(42);
                            int vectorY= 390 + row*(42);
                            if(ButtonDetect(x, y, vectorX, vectorY,
                                            vectorX + 42, vectorY + 42)) {
                                if(state == PASTING) {
                                    std::cout << "saving patterns to " << num << std::endl;
                                    fileName = "Pattern_";
                                    fileName += std::to_string(num);
                                    fileName += ".txt";
                                    if(!SaveSelectionToFile(fileName, select_LT, select_RB, world)) {
                                        std::cout << "pattern save to file failed" << std::endl;
                                    }
                                    state = PAUSED;
                                    sideBar.setButtonState(B_NORMAL);
                                }
                                else {
                                    std::cout << "saving to " << num << std::endl;
                                    fileName = std::to_string(num);
                                    fileName += ".txt";
                                    if(!write2dBoolArray(fileName, world))
                                        std::cout << "save failed" << std::endl;
                                }
                            }
                        }
                    }
                }

                //FOR LOAD FROM SLOTS:
                if(ButtonDetect(x, y, 750, 390, 876, 516)) {
                    //IF PRESSED INSIDE SECOND NUMBER BOX
                    int num = 0;
                    for(int row = 0; row < 3; row++) {
                        for(int col = 0; col < 3; col++) {
                            num++;
                            int vectorX= 750 + col*(42);
                            int vectorY= 390 + row*(42);
                            if(ButtonDetect(x, y, vectorX, vectorY,
                                            vectorX + 42, vectorY + 42)) {
                                if (state == LOADING_PATTERN){
                                    std::cout << "loading pattern from " << num << std::endl;
                                    fileName = "Pattern_";
                                    fileName += std::to_string(num);
                                    fileName += ".txt";
//                                    if(!PasteSelectionFromFile(fileName, select_LT, select_RB,
//                                                               x, y, world)) {
//                                        std::cout << "pattern load from file failed" <<std::endl;
//                                    }
//                                    state = PAUSED;
//                                    sideBar.setButtonState(B_NORMAL);
                                }
                                else {
                                    std::cout << "loading from " << num << std::endl;
                                    fileName = std::to_string(num);
                                    fileName += ".txt";
                                    if(!read2dBoolArray(fileName, world))
                                        std::cout << "load failed" << std::endl;
                                }
                            }
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
    //CHANGE THE STATE OF THE GAME
    if(state == NORMAL) {
        //IF THE GAME IS NOT PAUSED...
        step(world);
    }
}

void animate::render() {
    //RENDER THE GAME: CLEAR, DRAW, DISPLAY
    window.clear();
    FillShapes(shapeArray, themeNumber, world);
    ShowShapes(window, shapeArray);
    if(state == SELECTING_MOUSE_PRESSED) {
        DrawSelection(window, select_LT, sf::Mouse::getPosition(window));
    }
    if(state == PASTING) {
        DrawSelection(window, select_LT, select_RB);
    }
    sideBar.draw(window);
    window.display();

}

