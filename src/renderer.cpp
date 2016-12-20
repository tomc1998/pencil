#include <GLFW/glfw3.h>
#include "renderer.hpp"
#include "state.hpp"

Renderer* Renderer::renderer = new Renderer();

Renderer::Renderer() {
}

Renderer* Renderer::get_renderer() {
  return Renderer::renderer;
}

void Renderer::initialise_renderer(float width, float height) {
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
  glOrtho(0, width, height, 0, -1, 1); // Add an orthographic transformation
  glMatrixMode(GL_MODELVIEW); // Return to modelview matrix mode
}

void Renderer::render(State& state) {
    // Clear the color buffer (screen's RGB values)
    glClear(GL_COLOR_BUFFER_BIT); 
    // Draw a square (using immediate mode)
    glBegin(GL_QUADS);
    glVertex2f(0, 0);
    glVertex2f(300, 0);
    glVertex2f(300, 300);
    glVertex2f(0, 300);
    glEnd();

}
