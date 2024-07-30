#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
  SDL_Renderer *renderer;
  SDL_Window *window;
} App;

App *initSDL(int screen_width, int screen_height);

void prepareScene(App *app);

void presentScene(App *app);

/**
 * Loads a texture.
 */
SDL_Texture *loadTexture(App *app, char *filename);

/**
 * Draws a texture at a given position
 */
void drawTextureAt(App *app, SDL_Texture *texture, int x_pos, int y_pos,
                   int width, int height);