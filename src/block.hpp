#pragma once

class State; //Forward declaration

class Block {
  public:
    int coordinates[4];
    int colour;
    int rotationStage;
    bool left;
    bool right;
    char shape;
    /* Shape codes
     * 
     * z:   12
     *       34
     *
     * s:    34
     *      12
     *
     * t:   123
     *       4
     * 
     * j:   1
     *      234
     *
     * l:   321
     *      4
     *
     * i:   1234
     *
     * o:   12
     *      34  
     */
    
     Block(char blockShape, int blockColour);
     void rotateClockwise();
     void rotateAnticlockwise();
     bool isMovementOutOfBounds(bool isLeft);
     bool outOfBounds();
     bool blockOnLeft(State* state);
     bool blockOnRight(State* state);
 };
