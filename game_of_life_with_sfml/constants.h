//
// Created by anter on 5/23/18.
//

#ifndef GAME_OF_LIFE_CONSTANTS_H
#define GAME_OF_LIFE_CONSTANTS_H

const int MAX_ROW = 40 + 2;         //the max row numbers of the worldArray
const int MAX_COL = 40 + 2;         //the max col numbers of the worldArray
const int SCREEN_WIDTH = 960;       //the width of the window
const int SCREEN_HEIGHT = 540;      //the height of the window
const int GRID_WIDTH = MAX_COL - 2;     //the display array on the screen - width
const int GRID_HEIGHT = MAX_ROW - 2;    //the display array on the screen - height
const int CELL_SIZE = 12;           //the size of the cell

enum STATE {NORMAL, PAUSED,
            SELECTING_MOUSE_NOT_PRESSED, //when user just pressed the select button
                                        //but haven't started selecting
            SELECTING_MOUSE_PRESSED,    //when user is dragging to select region
            PASTING,                    //user finishes dragging & finding a place to paste
            LOADING_PATTERN,            //after user press "Load Pattern" button
            ERASING,                    //erasing mode
           };
enum BUTTON_STATE {B_NORMAL,            //button: normal
                   B_PAUSED,            //button: paused so should "resume"
                   B_SELECTING,         //button: is selecting so should "exit"
                   B_LOADING_PATTERN,   //button: is loading so should "exit"
};

#endif //GAME_OF_LIFE_CONSTANTS_H
