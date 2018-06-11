//
// Created by anter on 5/23/18.
//

#ifndef GAME_OF_LIFE_CONSTANTS_H
#define GAME_OF_LIFE_CONSTANTS_H

const int MAX_ROW = 40 + 2;
const int MAX_COL = 40 + 2;
const int SCREEN_WIDTH = 960;      //the demension of the window
const int SCREEN_HEIGHT = 540;
const int GRID_WIDTH = MAX_COL - 2;          //the "grid" on the screen
const int GRID_HEIGHT = MAX_ROW - 2;
const int CELL_SIZE = 12;

enum STATE {NORMAL, PAUSED,
            SELECTING_MOUSE_NOT_PRESSED, //when user just pressed the select button
                                        //but haven't started selecting
            SELECTING_MOUSE_PRESSED,    //when user is dragging to select region
            PASTING,                    //when user finished dragging, finding a place to paste
            ERASING,
           };
enum BUTTON_STATE {B_NORMAL,
                   B_PAUSED,
                   B_SELECTING,
};

#endif //GAME_OF_LIFE_CONSTANTS_H
