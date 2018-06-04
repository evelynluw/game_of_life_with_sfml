//
// Created by anter on 5/23/18.
//

#include "game_of_life.h"
#include "constants.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void initialize_2d(bool twod[][MAX_COL]) {
    //so the twod[] will be declared as twod[MAX_ROW][MAX_COL]
    for(int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            twod[i][j] = false;
        }
    }
//    printf("DEBUG: init cpl\n");
}

void initial_config(bool twod[][MAX_COL]) {
    //make some random cells "alive".
//    twod[1][2] = true;
//    twod[1][3] = true;
//    twod[1][4] = true;

/*
    int pos_i = 0;
    int pos_j = 0;
    for(int i = 0; i < 50; i++) {
        pos_i = rand() % (MAX_ROW - 2) + 1;
        pos_j = rand() % (MAX_COL - 2) + 1;
//        cout << "DEBUG: ";
//        printf("(%d, %d)\n", pos_i, pos_j);
        twod[pos_i][pos_j] = true;
    }
    cout << endl;
  */
    twod[1][2] = true;
    twod[2][3] = true;
    twod[3][1] = true;
    twod[3][2] = true;
    twod[3][3] = true;
    fill_margin(twod);
}

void initial_random(bool twod[][MAX_COL], int count_arg) {
    srand (time(NULL));
    int pos_i = 0;
    int pos_j = 0;
    int count = count_arg;
    while (count > 0){
        pos_i = rand() % (MAX_ROW - 2) + 1;
        pos_j = rand() % (MAX_COL - 2) + 1;
//        cout << "DEBUG: ";
//        printf("(%d, %d)\n", pos_i, pos_j);
        if (!twod[pos_i][pos_j]){
            twod[pos_i][pos_j] = true;
            count --;
        }
    }
    cout << endl;
}

void step(bool twod[][MAX_COL]) {
    bool temp[MAX_ROW][MAX_COL];
    copy_2d(temp, twod);
    for(int i = 1; i < MAX_ROW - 1; i++) {
        for(int j = 1; j < MAX_COL - 1; j++) {
            live_or_die(twod[i][j], count_neighbors(temp, i, j));
        }
    }
    fill_margin(twod);
}

void copy_2d(bool dest[][MAX_COL], bool src[][MAX_COL]) {
    for(int i = 0; i < MAX_ROW; i++) {
        for(int j = 0; j < MAX_COL; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

int count_neighbors(bool twod[][MAX_COL], int i, int j) {
    int count = 0;
    for(int i1 = i - 1; i1 <= i + 1; i1 ++) {
        for(int j1 = j - 1; j1 <= j + 1; j1 ++) {
            if(i1 == i && j1 == j)
                continue;
            if(twod[i1][j1])
                count++;
        }
    }
    return count;
}

void fill_margin(bool twod[][MAX_COL]) {
    //copy column (max-2) to col (0)
    for(int i = 0; i < MAX_ROW; i++) {
        twod[i][0] = twod[i][MAX_COL - 2];
    }
    //copy col (1) to col (max-1)
    for(int i = 0; i < MAX_ROW; i++) {
        twod[i][MAX_COL - 1] = twod[i][1];
    }
    //copy row(max - 2) to row(0)
    for(int j = 0; j < MAX_COL; j++) {
        twod[0][j] = twod[MAX_ROW -2][j];
    }
    //copy row(1) to row (max - 1)
    for(int j = 0; j < MAX_COL; j++) {
        twod[MAX_ROW - 1][j] = twod[1][j];
    }
}

void print_2d(bool twod[][MAX_COL]) {
    for(int i = 1; i < MAX_ROW - 1; i++) {
        for(int j = 1; j < MAX_COL - 1; j++) {
//            cout << twod[i][j] << ' ';
            if(twod[i][j])
                cout << "o ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}

void live_or_die(bool &cell, int neighborCount) {
    if(cell) {  // cell is alive
        if(neighborCount < 2)
            cell = false;
        if(neighborCount > 3)
            cell = false;
    }
    else {      // cell is dead
        if(neighborCount == 3)
            cell = true;
    }
}

bool all_dead(bool twod[][MAX_COL]) {
    bool allDead = true;
    for(int i = 1; i < MAX_ROW - 1; i++) {
        for(int j = 1; j < MAX_COL - 1; j++) {
            if(twod[i][j])
                allDead = false;
        }
    }
    return allDead;
}

void copy_1d(bool oned[]) {
    //do we need this?
}

void print_1d(bool oned[]) {
    int length = max(MAX_ROW, MAX_COL);
    for(int i = 0; i < length; i++) {
        cout << oned[i] << ' ';
    }
    cout << endl;
}

bool write2dBoolArray(string fileName, bool boolArray[][MAX_COL]) {
    ofstream outFile;
    outFile.open(fileName);
    if (outFile.fail()) {
//        cout << "can't write file" << endl;
        cin.get();
        //why is this line??
        return false;
    }
    for(int i = 1; i < MAX_ROW - 1; i++) {
        for (int j = 1; j < MAX_COL - 1; j++) {
            outFile << boolArray[i][j] << ' ';
        }
        outFile << endl;
    }
    outFile.close();
    return true;
}

bool read2dBoolArray(string fileName, bool boolArray[][MAX_COL]) {
    ifstream inFile;
    inFile.open(fileName);
    if (inFile.fail()) {
//        cout << "can't open file" << endl;
        cin.get();
        //same question
        return false;
    }
//    inFile >> size;
    for(int i = 1; i < MAX_ROW - 1; i++) {
        for (int j = 1; j < MAX_COL - 1; j++) {
            inFile >> boolArray[i][j];
        }
    }
    fill_margin(boolArray);
    inFile.close();
    return true;
}

void printBoolArray(bool *boolArray, int size) {
    for (int i = 0; i < size; i++) {
        cout << boolArray[i] << ' ';
    }
    cout << endl;
}

