#include "renderer.hpp"
#include "state.hpp"

Renderer* Renderer::renderer = new Renderer();

Renderer::Renderer() {
}

Renderer* Renderer::getRenderer() {
  return Renderer::renderer;
}

void Renderer::render(State& state) {
}
