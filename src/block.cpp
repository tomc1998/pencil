#include "block.hpp"
#include "state.hpp"
#include <iostream>
#include <cmath>
Block::Block(char blockShape, int blockColour) {
  rotationStage = 0;
  left = false;
  right = false;
  colour = blockColour;
  shape = blockShape; 

  if (shape == 'z') {
    coordinates[0] = 3;
    coordinates[1] = 4;
    coordinates[2] = 14;
    coordinates[3] = 15;
  }

  else if (shape == 's') {
    coordinates[0] = 13;
    coordinates[1] = 14;
    coordinates[2] = 4;
    coordinates[3] = 5;
  }

  else if (shape == 't') {
    coordinates[0] = 3;
    coordinates[1] = 4;
    coordinates[2] = 5;
    coordinates[3] = 14;
  }

  else if (shape == 'j') {
    coordinates[0] = 3;
    coordinates[1] = 13;
    coordinates[2] = 14;
    coordinates[3] = 15;
  }
  else if (shape == 'l') {
    coordinates[0] = 5;
    coordinates[1] = 4;
    coordinates[2] = 3;
    coordinates[3] = 13;
  }

  else if (shape == 'i') {
    coordinates[0] = 3;
    coordinates[1] = 4;
    coordinates[2] = 5;
    coordinates[3] = 6;
  }

  else if (shape == 'o') {
    coordinates[0] = 3;
    coordinates[1] = 4;
    coordinates[2] = 13;
    coordinates[3] = 14; 
  }
}

void Block::rotateClockwise() {
  rotationStage = (rotationStage + 1) % 4;

  if (shape == 'z') {
    if (rotationStage == 1 || rotationStage == 3) {
      coordinates[0] += 11;
      coordinates[2] += 9;
      coordinates[3] -= 2;
    }
    else {
      coordinates[0] -= 11;
      coordinates[2] -= 9;
      coordinates[3] += 2;
    }
  }
  if (shape == 's') {
    if (rotationStage == 1 || rotationStage == 3) {
      coordinates[0] -= 20;
      coordinates[1] -= 11;
      coordinates[3] += 9;
    }
    else {
      coordinates[0] += 20;
      coordinates[1] += 11;
      coordinates[3] -= 9;
    }
  }
  if (shape == 't') {
    if (rotationStage == 0) {
      coordinates[0] -= 11;
      coordinates[2] += 11;
      coordinates[3] += 9;
    }
    else if (rotationStage == 1) {
      coordinates[0] -= 9;
      coordinates[2] += 9;
      coordinates[3] -= 11;
    }
    else if (rotationStage == 2) {
      coordinates[0] += 11;
      coordinates[2] -= 11;
      coordinates[3] -= 9;
    }
    else {
      coordinates[0] += 9;
      coordinates[2] -= 9;
      coordinates[3] += 11;
    }
  }
  if (shape == 'j') {
    if (rotationStage == 0) {
      coordinates[0] -= 20;
      coordinates[1] -= 11;
      coordinates[3] += 11;
    }
    else if (rotationStage == 1) {
      coordinates[0] += 2;
      coordinates[1] -= 9;
      coordinates[3] += 9;
    }
    else if (rotationStage == 2) {
      coordinates[0] += 20;
      coordinates[1] += 11;
      coordinates[3] -= 11;
    }
    else {
      coordinates[0] -= 2;
      coordinates[1] += 9;
      coordinates[3] -= 9;
    }
  }
  if (shape == 'l') {
    if (rotationStage == 0) {
      coordinates[0] += 11;
      coordinates[2] -= 11;
      coordinates[3] -= 2;
    }
    else if (rotationStage == 1) {
      coordinates[0] += 9;
      coordinates[2] -= 9;
      coordinates[3] -= 20;
    }
    else if (rotationStage == 2) { 
      coordinates[0] -= 11;
      coordinates[2] += 11;
      coordinates[3] += 2;
    }
    else {
      coordinates[0] -= 9;
      coordinates[2] += 9;
      coordinates[3] += 20;
    }
  }
  if (shape == 'i') {
    if (rotationStage == 1 || rotationStage == 3) {
      coordinates[0] -= 9;
      coordinates[2] += 9;
      coordinates[3] += 18;
    }
    else {
      coordinates[0] += 9;
      coordinates[2] -= 9;
      coordinates[3] -= 18;
    }
  }
}

void Block::rotateAnticlockwise() {
  
  rotationStage = (rotationStage - 1) % 4;

  if (rotationStage < 0) {
    rotationStage += 4;
  }
  if (shape == 'z') {
    if (rotationStage == 1 || rotationStage == 3) {
      coordinates[0] += 11;
      coordinates[2] += 9;
      coordinates[3] -= 2;
    }
    else {
      coordinates[0] -= 11;
      coordinates[2] -= 9;
      coordinates[3] += 2;
    }
  }
  if (shape == 's') {
    if (rotationStage == 1 || rotationStage == 3) {
      coordinates[0] -= 20;
      coordinates[1] -= 11;
      coordinates[3] += 9;
    }
    else {
      coordinates[0] += 20;
      coordinates[1] += 11;
      coordinates[3] -= 9;
    }
  }
  if (shape == 't') {
    if (rotationStage == 0) {
      coordinates[0] += 9;
      coordinates[2] -= 9;
      coordinates[3] += 11;
    }
    else if (rotationStage == 1) {
      coordinates[0] -= 11;
      coordinates[2] += 11;
      coordinates[3] += 9;
        ;
    }
    else if (rotationStage == 2) {
      coordinates[0] -= 9;
      coordinates[2] += 9;
      coordinates[3] -= 11;
    }
    else {
      coordinates[0] += 11;
      coordinates[2] -= 11;
      coordinates[3] -= 9;
    }
  }
  if (shape == 'j') {
    if (rotationStage == 0) {
      coordinates[0] -= 2;
      coordinates[1] += 9;
      coordinates[3] -= 9;
    }
    else if (rotationStage == 1) {
      coordinates[0] -= 20;
      coordinates[1] -= 11;
      coordinates[3] += 11;
    }
    else if (rotationStage == 2) {
      coordinates[0] += 2;
      coordinates[1] -= 9;
      coordinates[3] += 9;
    }
    else {
      coordinates[0] += 20;
      coordinates[1] += 11;
      coordinates[3] -= 11;
    }
  }
  if (shape == 'l') {
    if (rotationStage == 0) {
      coordinates[0] -= 9;
      coordinates[2] += 9;
      coordinates[3] -= 20;
    }
    else if (rotationStage == 1) { 
      coordinates[0] += 11;
      coordinates[2] -= 11;
      coordinates[3] -= 2;
    }
    else if (rotationStage == 2) {
      coordinates[0] += 9;
      coordinates[2] -= 9;
      coordinates[3] -= 20;
    }
    else {
      coordinates[0] -= 11;
      coordinates[2] += 11;
      coordinates[3] += 2;
    }
  }
  if (shape == 'i') {
    if (rotationStage == 1 || rotationStage == 3) {
      coordinates[0] -= 9;
      coordinates[2] += 9;
      coordinates[3] += 18;
    }
    else {
      coordinates[0] += 9;
      coordinates[2] -= 9;
      coordinates[3] -= 18;
    }
  }
}

bool Block::isMovementOutOfBounds(bool isLeft) {
  if (isLeft) {
    for (int ii = 0; ii < 4; ii ++) {
      if (coordinates[ii] % 10 == 0) {
        return true;
      }
    }
  }
  else {
    for (int ii = 0; ii < 4; ii ++) {
      if (coordinates[ii] % 10 == 9) {
        return true;
      }
    }
  }
  return false;
}

bool Block::outOfBounds() {
  int min = 10;
  for (int i = 0; i < 4; i++) {
    if (coordinates[i] % 10 < min) {
      min = coordinates[i] % 10;
    }
  }
  int max = 0;
  for (int i = 0; i < 4; i++) {
    if (coordinates[i] % 10 > max) {
      max = coordinates[i] % 10;
    }
  }
  if (max - min >= 7) {
   return true; 
  }
  else {
    return false;
  }
}

bool Block::blockOnLeft(State* state) {
  for (int i = 0; i < 4; i++) {
    if (state->grid[coordinates[i] - 1] > 0 && 
        std::find(coordinates, 
          coordinates + 4, 
          coordinates[i] - 1) 
        == coordinates + 4) {
      return true;
    }
  }
  return false;
}

bool Block::blockOnRight(State* state) {
  for (int i = 0; i < 4; i++) {
    if (state->grid[coordinates[i] + 1] > 0 && 
        std::find(coordinates, 
          coordinates + 4, 
          coordinates[i] + 1) 
        == coordinates + 4) {
      return true;
    }
  }
  return false;
}
