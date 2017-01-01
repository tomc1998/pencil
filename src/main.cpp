#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SOIL.h>
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
    state->stepLength = 5;
    state->stepTimer = 0;
  }
  if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
    state->stepLength = 20;
  }
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
    while(true){
      if (state->step()){
        break;
      }
    }
  }
}


int main(int argc, char** argv) {
  /* load an image file directly as a new OpenGL texture */
  GLuint tex_2d = SOIL_load_OGL_texture
    (
     "img.png",
     SOIL_LOAD_AUTO,
     SOIL_CREATE_NEW_ID,
     SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
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
  game_state->nextBlock = new Block(game_state->possibleShapes[randIndex], game_state->possibleColours[randIndex]); 

  glfwSetWindowUserPointer(window, game_state);
  while(1) {
    if (game_state->flashTimer < 0) {
      game_state->stepTimer -= 1;
      game_state->moveTimer -= 1;
      // Poll input events, i.e keyboard, window, mouse etc.
      glfwPollEvents();
      //LEFT MOVEMENT
      if (game_state->currentBlock->left == true &&
          game_state->moveTimer <= 0 &&
          game_state->currentBlock->blockOnLeft(game_state) == false &&
          !game_state->currentBlock->isMovementOutOfBounds(true)) {
        game_state->moveTimer = 8;
        game_state->grid[game_state->currentBlock->coordinates[0]] = 0;
        game_state->grid[game_state->currentBlock->coordinates[1]] = 0;
        game_state->grid[game_state->currentBlock->coordinates[2]] = 0;
        game_state->grid[game_state->currentBlock->coordinates[3]] = 0;

        for (int i = 0; i < 4; i++) {
          game_state->currentBlock->coordinates[i] -= 1;
        }

        game_state->grid[game_state->currentBlock->coordinates[0]] = game_state->currentBlock->colour;
        game_state->grid[game_state->currentBlock->coordinates[1]] = game_state->currentBlock->colour;
        game_state->grid[game_state->currentBlock->coordinates[2]] = game_state->currentBlock->colour;
        game_state->grid[game_state->currentBlock->coordinates[3]] = game_state->currentBlock->colour;
      }
      //RIGHT MOVEMENT
      if (game_state->currentBlock->right == true &&
          game_state->moveTimer <= 0 &&
          game_state->currentBlock->blockOnRight(game_state) == false &&
          !game_state->currentBlock->isMovementOutOfBounds(false)) {
        game_state->moveTimer = 8;
        game_state->grid[game_state->currentBlock->coordinates[0]] = 0;
        game_state->grid[game_state->currentBlock->coordinates[1]] = 0;
        game_state->grid[game_state->currentBlock->coordinates[2]] = 0;
        game_state->grid[game_state->currentBlock->coordinates[3]] = 0;

        for (int i = 0; i < 4; i++) {
          game_state->currentBlock->coordinates[i] += 1;
        }

        game_state->grid[game_state->currentBlock->coordinates[0]] = game_state->currentBlock->colour;
        game_state->grid[game_state->currentBlock->coordinates[1]] = game_state->currentBlock->colour;
        game_state->grid[game_state->currentBlock->coordinates[2]] = game_state->currentBlock->colour;
        game_state->grid[game_state->currentBlock->coordinates[3]] = game_state->currentBlock->colour;
      }
      if (game_state->stepTimer <= 0) {
        game_state->stepTimer = game_state->stepLength;
        game_state->step();
        if (game_state->needNewBlock) {
          delete game_state->currentBlock;
          game_state->currentBlock = game_state->nextBlock;
          srand(time(NULL));
          randIndex = rand() % 7;
          game_state->nextBlock = new Block(game_state->possibleShapes[randIndex], game_state->possibleColours[randIndex]); 
          game_state->needNewBlock = false;
          std::cout << game_state->flashTimer << std::endl;

        }
        std::cout << game_state->nextBlock->shape << std::endl;
      }
    }
    else {
      game_state->flashTimer -= 1;
      std::cout << game_state->flashTimer << std::endl;
    }
    renderer->render(game_state);
    // Swap buffers, show what we've drawn. We need this at the end of each
    // render!
    glfwSwapBuffers(window); 
  }
}
