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
  needNewBlock = false;
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
    needNewBlock = true;

    for (int i = 0; i < 300; i += 10) {
      int count = 0;
      for (int x = 0; x < 10; x ++) {
        if (grid[x + i] > 0) {
         count ++; 
        }
      }
      if (count == 10) {
        for (int x = 0; x < 10; x ++) {
          if (grid[x + i] != 8) {
            grid[x + i] = 8;
            flashTimer = 30;
          }
        }
        if (flashTimer <= 0) {
          for (int row = i - 10;row > 0;row -= 10) {
            for (int col = 0; col < 10; col ++) {
              grid[(row + 10) + col] = grid[row + col];
              grid[row + col] = 0;
            }
          }
        }
      }
    }
  needNewBlock = true;
  }

  for (int i = 0; i < 4; i++) {
    if (grid[currentBlock->coordinates[i] + 10] > 0 && grid[currentBlock->coordinates[i] + 10] < 8 && 
        std::find(currentBlock->coordinates, 
          currentBlock->coordinates + 4, 
          currentBlock->coordinates[i] + 10) 
        == currentBlock->coordinates + 4) {

      needNewBlock = true;
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
            if (grid[x + i] != 8) {
              grid[x + i] = 8;
              flashTimer = 20;
            }
          }
          if (flashTimer <= 0) {
            for (int row = i - 10;row > 0;row -= 10) {
              for (int col = 0; col < 10; col ++) {
                grid[(row + 10) + col] = grid[row + col];
                grid[row + col] = 0;
              }
            }
          }
        }
      }

    }
  }
  for (int ii = 0; ii < 300; ii += 10) {

    if (flashTimer <= 0 && grid[ii] == 8) {
      for (int row = ii - 10; row > 0; row -= 10) {
        for (int col = 0; col < 10; col ++) {
          grid[(row + 10) + col] = grid[row + col];
          grid[row + col] = 0;
        }
      }
    }
  }

  if (!needNewBlock) {
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
  }

  return finished;
}
