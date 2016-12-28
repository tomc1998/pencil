#include "state.hpp"
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <iostream>
#include "block.hpp"
State::State() {
  std::memset(grid, 0, sizeof(grid));
  stepLength = 20;
  stepTimer = stepLength;
  moveTimer = 8;
}

bool State::step() {
  bool finished = false;
  int max = 0;
  for (int i = 0; i < 4; i++) {
    if (currentBlock->coordinates[i] / 10 > max) {
      max = currentBlock->coordinates[i] / 10;
    }
  }

  if (max == 29) {
    finished = true;
    delete currentBlock;

    for (int i = 0; i < 300; i += 10) {
      int count = 0;
      for (int x = 0; x < 10; x ++) {
        if (grid[x + i] > 0) {
         count ++; 
        }
      }
      if (count == 10) {
        for (int x = 0; x < 10; x ++) {
          grid[x + i] = 0;
        }
        for (int row = i - 10;row > 0;row -= 10) {
          for (int col = 0; col < 10; col ++) {
            grid[(row + 10) + col] = grid[row + col];
            grid[row + col] = 0;
          }
        }
      }
    }
    
    currentBlock = nextBlock;
    srand(time(NULL));
    int randIndex = rand() % 7;
    nextBlock = new Block(possibleShapes[randIndex], possibleColours[randIndex]);
  }

  for (int i = 0; i < 4; i++) {
    if (grid[currentBlock->coordinates[i] + 10] > 0 && 
        std::find(currentBlock->coordinates, 
          currentBlock->coordinates + 4, 
          currentBlock->coordinates[i] + 10) 
        == currentBlock->coordinates + 4) {
      delete currentBlock;

      finished = true;
      for (int i = 0; i < 300; i += 10) {
        int count = 0;
        for (int x = 0; x < 10; x ++) {
          if (grid[x + i] > 0) {
           count ++; 
          }
        }
        if (count == 10) {
          for (int x = 0; x < 10; x ++) {
            grid[x + i] = 0;
          }
          for (int row = i - 10;row > 0;row -= 10) {
            for (int col = 0; col < 10; col ++) {
              grid[(row + 10) + col] = grid[row + col];
              grid[row + col] = 0;
            }
          }
        }
      }

      currentBlock = nextBlock;
      srand(time(NULL));
      int randIndex = rand() % 7;
      nextBlock = new Block(possibleShapes[randIndex], possibleColours[randIndex]);
    }
  }
  grid[currentBlock->coordinates[0]] = 0;
  grid[currentBlock->coordinates[1]] = 0;
  grid[currentBlock->coordinates[2]] = 0;
  grid[currentBlock->coordinates[3]] = 0;
  for (int i = 0; i < 4; i++) {
    currentBlock->coordinates[i] += 10;
  }

  grid[currentBlock->coordinates[0]] = currentBlock->colour;
  grid[currentBlock->coordinates[1]] = currentBlock->colour;
  grid[currentBlock->coordinates[2]] = currentBlock->colour;
  grid[currentBlock->coordinates[3]] = currentBlock->colour;

  return finished;
}
