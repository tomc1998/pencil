#pragma once

class State; // Fwd decl

class Renderer {
  public:
    /** Get the renderer singleton instance */
    static Renderer* get_renderer();

    /** (re)Initialise the renderer using the size of the framebuffer */
    void initialise_renderer(float width, float height);

    /** Render some state */
    void render(State& state);

  private:
    /** Static renderer instance for singleton pattern */
    static Renderer* renderer;
    /** Private constructor */
    Renderer();
};
