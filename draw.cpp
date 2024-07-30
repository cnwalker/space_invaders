#include "draw.h"
#include <iostream>

App *initSDL(int screen_width, int screen_height) {
  int rendererFlags = SDL_RENDERER_ACCELERATED;
  int windowFlags = 0;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "Couldn't initialize SDL: " << SDL_GetError() << std::endl;
    exit(1);
  }

  App *app = new App();
  app->window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED, screen_width,
                                 screen_height, windowFlags);

  if (!app->window) {
    std::cerr << "Failed to open window: " << SDL_GetError() << std::endl;
    exit(1);
  }

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
  app->renderer = SDL_CreateRenderer(app->window, -1, rendererFlags);

  if (!app->renderer) {
    std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
    exit(1);
  }

  /**
   * Allow loading jpgs as textures
   */
  IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
  return app;
}

void prepareScene(App *app) {
  SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
  SDL_RenderClear(app->renderer);
}

void presentScene(App *app) { SDL_RenderPresent(app->renderer); }

/**
 * Loads a texture.
 */
SDL_Texture *loadTexture(App *app, char *filename) {
  SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                 "Loading %s", filename);
  return IMG_LoadTexture(app->renderer, filename);
}

/**
 * Draws a texture at a given position
 */
void drawTextureAt(App *app, SDL_Texture *texture, int x_pos, int y_pos,
                   int width, int height) {
  SDL_Rect canvas;
  canvas.x = x_pos;
  canvas.y = y_pos;
  SDL_QueryTexture(texture, NULL, NULL, &canvas.w, &canvas.h);
  canvas.w = width;
  canvas.h = height;
  SDL_RenderCopy(app->renderer, texture, NULL, &canvas);
}