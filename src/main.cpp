#include <iostream>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include "renderer.hpp"
#include "state.hpp"

GLFWwindow* window = NULL;

/** Initialise GLFW (window handler) */
void init_glfw(float screen_width, float screen_height) {
  // Need to call this before running any GLFW stuff!
  glfwInit();

  // Create a window
  window = glfwCreateWindow(screen_width, screen_height, "Pencil", NULL, NULL);

  // Set OpenGL to work with the window we just created
  glfwMakeContextCurrent(window);
}

int main(int argc, char** argv) {
  float screen_width = 800;
  float screen_height = 600;
  // Initialise a window
  init_glfw(screen_width, screen_height);

  // Initialise OpenGL stuff (see function for details)
  Renderer* renderer = Renderer::get_renderer();
  renderer->initialise_renderer(screen_width, screen_height);

  State game_state;

  while(1) {
    renderer->render(game_state);
    // Poll input events, i.e keyboard, window, mouse etc.
    glfwPollEvents();
    // Swap buffers, show what we've drawn. We need this at the end of each
    // render!
    glfwSwapBuffers(window); 
  }
}
