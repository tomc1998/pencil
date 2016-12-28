#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "renderer.hpp"
#include "state.hpp"
#include "block.hpp"
#include <GLFW/glfw3.h>

GLFWwindow* window = NULL;

/** Initialise GLFW (window handler) */
void init_glfw(float screen_width, float screen_height) {
  // Need to call this before running any GLFW stuff!
  glfwInit();

  // Create a window
  window = glfwCreateWindow(screen_width, screen_height, "Tetris", NULL, NULL);

  // Set OpenGL to work with the window we just created
  glfwMakeContextCurrent(window);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  State* state = static_cast<State*>(glfwGetWindowUserPointer(window));
  if (key == GLFW_KEY_UP && action == GLFW_PRESS) {

    state->grid[state->currentBlock->coordinates[0]] = 0;
    state->grid[state->currentBlock->coordinates[1]] = 0;
    state->grid[state->currentBlock->coordinates[2]] = 0;
    state->grid[state->currentBlock->coordinates[3]] = 0;

    state->currentBlock->rotateClockwise();

    if (state->currentBlock->outOfBounds()) {
      state->currentBlock->rotateAnticlockwise();
    }
    else {
      for (int i = 0;i < 4;i++) {
        if (state->grid[state->currentBlock->coordinates[i]] > 0) {
          state->currentBlock->rotateAnticlockwise();
          break;
        }
      }
    }
    state->grid[state->currentBlock->coordinates[0]] = state->currentBlock->colour;
    state->grid[state->currentBlock->coordinates[1]] = state->currentBlock->colour;
    state->grid[state->currentBlock->coordinates[2]] = state->currentBlock->colour;
    state->grid[state->currentBlock->coordinates[3]] = state->currentBlock->colour;
  }
  if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
    state->currentBlock->right = true;
  }
  else if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE){
    state->currentBlock->right = false;
  }
  if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
    state->currentBlock->left = true;
  }
  else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE){
    state->currentBlock->left = false;
  }
  if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
    state->softDrop = true;
    state->stepTimer = 0;
  }
  if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
    state->softDrop = false;
  }
}


int main(int argc, char** argv) {
  float screen_width = 300;
  float screen_height = 900;
  // Initialise a window
  init_glfw(screen_width, screen_height);

  glfwSetKeyCallback(window, key_callback);

  // Initialise OpenGL stuff (see function for details)
  Renderer* renderer = Renderer::get_renderer();
  renderer->initialise_renderer(screen_width, screen_height);
  State* game_state = new State();

  srand(time(NULL));
  
  int randIndex = rand() % 7;

  game_state->currentBlock = new Block(game_state->possibleShapes[randIndex], game_state->possibleColours[randIndex]);

  glfwSetWindowUserPointer(window, game_state);
  while(1) {
    if (game_state->softDrop == true) {
      game_state->stepLength = 5;
    } 
    else {
      game_state->stepLength = 20;
    }
    game_state->stepTimer -= 1;
    game_state->moveTimer -= 1;
    renderer->render(game_state);
    // Poll input events, i.e keyboard, window, mouse etc.
    glfwPollEvents();
    if (game_state->currentBlock->left == true && game_state->moveTimer <= 0 && game_state->currentBlock->blockOnLeft(game_state) == false) {
      game_state->moveTimer = 8;
      game_state->grid[game_state->currentBlock->coordinates[0]] = 0;
      game_state->grid[game_state->currentBlock->coordinates[1]] = 0;
      game_state->grid[game_state->currentBlock->coordinates[2]] = 0;
      game_state->grid[game_state->currentBlock->coordinates[3]] = 0;

      for (int i = 0; i < 4; i++) {
        game_state->currentBlock->coordinates[i] -= 1;
      }

      if (game_state->currentBlock->outOfBounds()) {
        for (int i = 0; i < 4; i++) {
          game_state->currentBlock->coordinates[i] += 1;
        }
      }
  
      game_state->grid[game_state->currentBlock->coordinates[0]] = game_state->currentBlock->colour;
      game_state->grid[game_state->currentBlock->coordinates[1]] = game_state->currentBlock->colour;
      game_state->grid[game_state->currentBlock->coordinates[2]] = game_state->currentBlock->colour;
      game_state->grid[game_state->currentBlock->coordinates[3]] = game_state->currentBlock->colour;
    }

    if (game_state->currentBlock->right == true && game_state->moveTimer <= 0 && game_state->currentBlock->blockOnRight(game_state) == false) {
      game_state->moveTimer = 8;
      game_state->grid[game_state->currentBlock->coordinates[0]] = 0;
      game_state->grid[game_state->currentBlock->coordinates[1]] = 0;
      game_state->grid[game_state->currentBlock->coordinates[2]] = 0;
      game_state->grid[game_state->currentBlock->coordinates[3]] = 0;

      for (int i = 0; i < 4; i++) {
        game_state->currentBlock->coordinates[i] += 1;
      }
  
      if (game_state->currentBlock->outOfBounds()) {
        for (int i = 0; i < 4; i++) {
          game_state->currentBlock->coordinates[i] -= 1;
        }
      }
      game_state->grid[game_state->currentBlock->coordinates[0]] = game_state->currentBlock->colour;
      game_state->grid[game_state->currentBlock->coordinates[1]] = game_state->currentBlock->colour;
      game_state->grid[game_state->currentBlock->coordinates[2]] = game_state->currentBlock->colour;
      game_state->grid[game_state->currentBlock->coordinates[3]] = game_state->currentBlock->colour;
    }
    if (game_state->stepTimer <= 0) {
      game_state->stepTimer = game_state->stepLength;
      game_state->step();
    }
    // Swap buffers, show what we've drawn. We need this at the end of each
    // render!
    glfwSwapBuffers(window); 
  }
}
