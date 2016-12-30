#pragma once
#include "block.hpp"

/** State object which holds state of everything currently being used by the
 * engine. */
class State {
  public:
    /** Construct a state object */
    State();
    bool step();
    int stepLength;
    int stepTimer;
    int moveTimer;
    int flashTimer;
    bool needNewBlock;
    int grid[300];
    char possibleShapes[7] = {'z', 's', 't', 'j', 'l', 'i', 'o'};
    int possibleColours[7] = { 1,   2,   3,   4,   5,   6,   7};
    /*
     * Colour 1: red
     * Colour 2: green
     * Colour 3: purple
     * Colour 4: blue
     * Colour 5: orange
     * Colour 6: cyan
     * Colour 7: yellow
     */
    Block* currentBlock; 
    Block* nextBlock;

};
