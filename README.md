# Report for the basic functions:
- Pause/resume: works properly, however sometimes the program will pause with operations that shouldn't have paused the program.
- Random: works properly. It generates a set amount of alive cells to random locations.
- Clear: works properly. It clears every living cell from the display grid.
- Select: works properly.
    - First, user can press select then choose the area on the grid that they wish to copy from;
    - After this, user can choose to
        - Select a cell on the display grid to "paste" the pattern to the grid, or
        - Select a slot to save the pattern.
- Load pattern: works properly. This is for the user to load previously saved patterns from the local slots and paste them into the grid.
    - User can paste continuiously as long as they are in the load pattern mode.
    - User can also select another slot and continue with pasting patterns to the display grid.
- Color selections: works properly, however they could trigger a pause to the game when pressed.
    - A color series is created by randomizing the "independent variable" and generate the "dependent variables" according to some linear formula.
- Drawing: works properly. User can draw by clicking or dragging on the screen in resumed / paused state.
    - to erase user needs to press "E" to activate erasing mode. Press E again to exit erasing mode.
- Exit: works properly. It exits the game.

# Other known bugs:
- when selecting, the rectangle could be drawn outside of the grid area and cause the program to stop working.
- if user tries to load from a nonexistent file, program will stop working and will not return error value, even if it's written in the code.

# Desired features in the future:
- let buttons change color when mouse is "hovering" over the text buttons.
- hints on the left bottom corner of the window.
