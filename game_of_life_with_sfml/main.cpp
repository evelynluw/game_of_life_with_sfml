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
#include "sidebar.h"
#include "animate.h"

int main(int argc, char *argv[]) {
    animate game;
    game.run();
}
