#include <iostream>
#include <fstream>
#include "game_of_life_sfml.h"
#include "game_of_life.h"

void SaveSelection(sf::Vector2i LT, sf::Vector2i RB, bool tempArray[][MAX_COL], bool world[][MAX_COL]) {
    /* SAVE SELECTION TO TEMPARRAY.
     * LT: leftTop position, in pixels;
     * RB: RightBottom position, in pixels.
     * tempArray: an array for saving the small area, like a clipboard
     */
    int LT_i = 0,
            LT_j = 0,
            RB_i = 0,
            RB_j = 0;
    pixelToCell(LT.x, LT.y, LT_i, LT_j);
    pixelToCell(RB.x, RB.y, RB_i, RB_j);
    swapInt(LT_i, RB_i, (LT_i > RB_i));
    swapInt(LT_j, RB_j, (LT_j > RB_j));
    int size_i = RB_i - LT_i + 1;
    int size_j = RB_j - LT_j + 1;
    for(int i = 0; i < size_i; i++) {
        for(int j = 0; j < size_j; j++) {
            tempArray[i][j] = world[LT_i + i][LT_j + j];
            //DEBUG
            std::cout<<tempArray[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

void PasteSelection(sf::Vector2i LT, sf::Vector2i RB,
                    int mouse_i, int mouse_j, bool tempArray[][MAX_COL], bool world[][MAX_COL]) {
    /* PASTE SELECTION FROM TEMPARRAY.
     * LT: leftTop position, in pixels;
     * RB: RightBottom position, in pixels.
     * mouse_i & mouse_j: the location of the mouse, in "i and j" -- the coordinates inside of
     *     the world array
     * tempArray: an array for saving the small area, like a clipboard
     */
    int LT_i = 0,
            LT_j = 0,
            RB_i = 0,
            RB_j = 0;
    pixelToCell(LT.x, LT.y, LT_i, LT_j);
    pixelToCell(RB.x, RB.y, RB_i, RB_j);
    swapInt(LT_i, RB_i, (LT_i > RB_i));
    swapInt(LT_j, RB_j, (LT_j > RB_j));
    int size_i = RB_i - LT_i + 1;
    int size_j = RB_j - LT_j + 1;
    for(int i = 0; i < size_i; i++) {
        for(int j = 0; j < size_j; j++) {
            world[mouse_i + i][mouse_j + j] = tempArray[i][j];
            //DEBUG
        }
    }
}

bool SaveSelectionToFile(std::string fileName, sf::Vector2i LT, sf::Vector2i RB, bool world[][MAX_COL]) {
    /* SAVE SELECTION TO FILE. FILE IS TXT. SELECTION IS SAVED BY SEPARATING EVERY
     * CELL WITH ' ', AND RETURN AFTER EVERY LINE ENDINGS
     * fileName: the name of the file to be saved, includes ".txt"
     * LT: leftTop position, in pixels;
     * RB: RightBottom position, in pixels.
     * tempArray: an array for saving the small area, like a clipboard
     */
    int LT_i = 0,
            LT_j = 0,
            RB_i = 0,
            RB_j = 0;
    pixelToCell(LT.x, LT.y, LT_i, LT_j);
    pixelToCell(RB.x, RB.y, RB_i, RB_j);
    swapInt(LT_i, RB_i, (LT_i > RB_i));
    swapInt(LT_j, RB_j, (LT_j > RB_j));
    int size_i = RB_i - LT_i + 1;
    int size_j = RB_j - LT_j + 1;

    ofstream outFile;
    outFile.open(fileName);
    if(outFile.fail()) {
//        cout << "can't write to file" << endl;
        cin.get();
        return false;
    }
    for(int i = 0; i < size_i; i++) {
        for(int j = 0; j < size_j; j++) {
            outFile << world[LT_i + i][LT_j + j] << ' ';
            //DEBUG
//            std::cout<<tempArray[i][j]<<" ";
        }
//        std::cout<<std::endl;
        outFile << endl;
    }
    outFile.close();
    return true;
}

bool PasteSelectionFromFile(std::string fileName,
                       int mouse_i, int mouse_j, bool world[][MAX_COL]) {
    /* PASTE SELECTION FROM FILE.
     * fileName: the name of the file, includes ".txt"
     * mouse_i & mouse_j: the location of the mouse, in "i and j" -- the coordinates inside of
     *     the world array, so they are integers
     * tempArray: an array for saving the small area, like a clipboard
     */
    ifstream is(fileName);      //open file

    char c;
    int j = 0;
    int i = 0;
    while (is.get(c))  {
        if(c == '\n') {
            //cout<<" |"<<endl;
            j = 0;
            i++;
        }
        else if(c == ' ') {
            //cout<<"-";
        } else {
            //cout<<c;
            int c_int = c - 48;
            if((mouse_i + i <= GRID_HEIGHT)
                    && (mouse_j + j <= GRID_WIDTH))
                world[mouse_i + i][mouse_j + j] = c_int;
            j++;
        }
    }
    fill_margin(world);
    is.close();
    return true;
}

void FillShapes(sf::RectangleShape shapeArray[][GRID_WIDTH],
                int themeNumber, bool world[][MAX_COL]){
    /* SET THE IDENDITIES OF THE SMALL SQUARES INSIDE OF THE GRID.
     * shapeArray: the array consist of all the small RectangleShapes
     * themeNumber: the number for the color theme
     */
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
    /* DISPLAY THE SHAPES TO THE WINDOW
     * window: the main window in the program
     * shapeArray: the grid made of many small RectangleShapes
     */
    for (int row=0; row<GRID_HEIGHT; row++){
        for (int col=0; col<GRID_WIDTH; col++){
            window.draw(shapeArray[row][col]);
        }
    }

}

void DrawText(sf::Text &text, sf::Font font, sf::Color color,
              std::string textString, int pos_x, int pos_y,
              sf::RenderWindow &window) {
    /* DRAW THE TEXT OBJECT ONTO THE WINDOW WITH THESE IDENTITIES.
     * text: text object file.
     * font: font file.
     * color: sf::Color, with different ways to express
     * textString: the textString content to be displayed.
     * pos_x and pos_y: the location on the window that the text object should be drawn.
     * window: the window object.
     */
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

void DrawSelection(sf::RenderWindow &window, sf::Vector2i LT, sf::Vector2i mouseLoc) {
    /* DRAW THE SELECTION RECTANGLE WHICH STARTS FROM LT AND ENDS AT MOUSELOC.
     * MOUSELOC IS LIVE UPDATED, BUT IS GENERATED OUTSIDE THIS FUNCTION.
     * window: the object window
     * LT: the leftTop position in pixels,
     * mouseLoc: the mouse location in pixels
     */
    sf::RectangleShape rec;
//    vector2f size(RB.x - LT.x, RB.y - LT.y);
//    int width = RB.x - LT.x;
//    int height = RB.y - LT.y;
    sf::Vector2i LT_ij;
    sf::Vector2i mouseLoc_ij;
    sf::Vector2f LT_aligned;
    sf::Vector2f mouseLoc_aligned;
    pixelToCell(LT.x, LT.y, LT_ij.x, LT_ij.y);
    LT_ij.x --;
    LT_ij.y --;
    pixelToCell(mouseLoc.x, mouseLoc.y, mouseLoc_ij.x, mouseLoc_ij.y);
    cellToPixel(LT_ij.x, LT_ij.y, LT_aligned);
    cellToPixel(mouseLoc_ij.x, mouseLoc_ij.y, mouseLoc_aligned);
    rec.setSize(sf::Vector2f(mouseLoc_aligned.x - LT_aligned.x,
                             mouseLoc_aligned.y - LT_aligned.y));
    rec.setFillColor(sf::Color(255, 199, 0, 70));  //50 = alpha = transparency
    rec.setOutlineColor(sf::Color(255, 199, 0, 200));
    rec.setOutlineThickness(1);
    rec.setPosition(LT_aligned.x, LT_aligned.y);
    window.draw(rec);
}

bool ButtonDetect(int mouse_x, int mouse_y, int leftTop_x, int leftTop_y,
                  int rightBottom_x, int rightBottom_y) {
    /* RETURNS TRUE IF MOUSE LOCATION IS INSIDE OF THE RECTANGLE
     * mouse_x, mouse_y: location of the mouse of
     * leftTop_x, leftTop_y: lo
     */
    return ((mouse_x >= leftTop_x && mouse_y >= leftTop_y)
        && (mouse_x <= rightBottom_x && mouse_y <= rightBottom_y));
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
    case 2: //mint theme
        Red = Random(0, 255);
        Green = 255;
        Blue = 0.49 * Red + 131;
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
    case 4: //magenta theme
        Green = Random(0, 255);
        Blue = 0.72 * Green + 72;
        if (Blue > 255)
            Blue = 255;
        Red = 255;
        break;
    case 5: //pride theme
    {
        int code = Random(0, 5);
        switch (code) {
        case 0:
            Red = 231; Green = 0; Blue = 0;
            break;
        case 1:
            Red = 255; Green = 140; Blue = 0;
            break;
        case 2:
            Red = 255; Green = 239; Blue = 0;
            break;
        case 3:
            Red = 0; Green = 129; Blue = 31;
            break;
        case 4:
            Red = 0; Green = 68; Blue = 255;
            break;
        case 5:
            Red = 118; Green = 0; Blue = 137;
            break;
        }
        break;
    }
    default:
        Red = 255;
        Green = 255;
        Blue = 255;
        break;
    }
}

void pixelToCell(int pixel_x, int pixel_y, int &i, int &j) {
    i = pixel_y / (CELL_SIZE + 1) + 1;
    j = pixel_x / (CELL_SIZE + 1) + 1;
}

void cellToPixel(int i, int j, sf::Vector2f &pixelLoc) {
    pixelLoc.x = j * (CELL_SIZE + 1);
    pixelLoc.y = i * (CELL_SIZE + 1);
}

int Random(int lo, int hi){
    int r = rand() % (hi + 1) + lo;
    //so if Random(0, 255)
    //== rand() % 256
    //returns int value in [0, 255]
    return r;
}

void swapInt(int &a, int &b, bool condition) {
//    swap the value of a and b if condition is true
    if (condition) {
        int c = a;
        a = b;
        b = c;
    }
}
