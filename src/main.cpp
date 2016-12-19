#include <iostream>
#include <cstdlib>
#include <GLFW/glfw3.h>

GLFWwindow* window = NULL;

/** Initialise GLFW (window handler) */
void init_glfw() {
  // Need to call this before running any GLFW stuff!
  glfwInit();

  // Create a window
  window = glfwCreateWindow(800, 600, "Pencil", NULL, NULL);

  // Set OpenGL to work with the window we just created
  glfwMakeContextCurrent(window);
}

/** Initialise OpenGL (matrices etc) */
void init_gl() {
  // Set 'clear colour' to black (when we clear the screen the window will be
  // black)
  glClearColor(0, 0, 0, 1);
  
  // Set up orthographic projection matrices...
  // This sets up how world coordinates map to screen coordinates. For now, we
  // just want the mapping 1 to 1 - if we want to draw a circle at screen
  // position (200, 300), then the circle's world position should be (200,
  // 300). An 'orthographic projection' is used as we're just handling 2D at
  // the moment, as opposed to a 'perspective projection' which makes things
  // which are further away in the 3rd dimension appear smaller.
  glMatrixMode(GL_PROJECTION); // Make sure we're dealing with projection matrices
  glLoadIdentity();            // Load identity matrix
  glOrtho(0, 800, 600, 0, -1, 1); // Add an orthographic transformation
  glMatrixMode(GL_MODELVIEW); // Return to modelview matrix mode
}

int main(int argc, char** argv) {
  // Initialise a window
  init_glfw();
  // Initialise openGL stuff (see function for details)
  init_gl();

  while(1) {
    // Clear the color buffer (screen's RGB values)
    glClear(GL_COLOR_BUFFER_BIT); 
    // Draw a square (using immediate mode)
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(300, 0);
    glVertex2f(300, 300);
    glVertex2f(0, 300);
    glEnd();

    // Poll input events, i.e keyboard, window, mouse etc.
    glfwPollEvents();
    // Swap buffers, show what we've drawn. We need this at the end of each
    // render!
    glfwSwapBuffers(window); 
  }
}
