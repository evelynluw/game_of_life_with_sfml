//
// Created by anter on 5/23/18.
//

#ifndef GAME_OF_LIFE_GAME_OF_LIFE_H
#define GAME_OF_LIFE_GAME_OF_LIFE_H

#include "constants.h"
#include <string>
using namespace std;

void initialize_2d(bool twod[][MAX_COL]);                   //set every cell to 0
void initial_config(bool twod[][MAX_COL]);                  //set some cells to 1
void initial_random(bool twod[][MAX_COL], int count_arg);   //initialize randomly
void step(bool twod[][MAX_COL]);                            //get the next generation.
    //note: copy the main array to a temp array;
    //according to the temp array,
    //do changes to the main array
void copy_2d(bool dest[][MAX_COL], bool src[][MAX_COL]);    //copy src to dest
int count_neighbors(bool twod[][MAX_COL], int i, int j);    //count the alive neighbors.
    //note: the logic: avoid the cells near the walls first.
    //then deal with those not in corners.
    //then deal with corners.
void fill_margin(bool twod[][MAX_COL]);     //update buffer area, so grid is continuous
                                            //at the borders and corners
void print_2d(bool twod[][MAX_COL]);        //output the 2d array

//small functions
void live_or_die(bool &cell, int neighborCount);    //set cell to alive or dead according
                                                    //to its neighbours
bool all_dead(bool twod[][MAX_COL]);    //return true if all cellse are dead
void copy_1d(bool oned[]);              //copy 1d array
void print_1d(bool oned[]);             //print 1d array

//file in/out
bool write2dBoolArray(string fileName, bool boolArray[][MAX_COL]);
                                    //write the 2d bool array to a file with fileName
bool read2dBoolArray(string fileName, bool boolArray[][MAX_COL]);
                                    //load the 2d bool array from a file with fileName
void printBoolArray(bool boolArray[], int size);
                                    //output the 2d bool array




#endif //GAME_OF_LIFE_GAME_OF_LIFE_H
