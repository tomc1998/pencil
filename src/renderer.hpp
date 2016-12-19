#pragma once

class State; // Fwd decl

class Renderer {
  public:
    /** Get the renderer singleton instance */
    static Renderer* getRenderer();

    /** Render some state */
    void render(State& state);

  private:
    /** Static renderer instance for singleton pattern */
    static Renderer* renderer;
    /** Private constructor */
    Renderer();
};
