#include "draw.h"
#include <SDL2/SDL.h>
#include <string>
#include <vector>

struct Character {
    int x_pos;
    int y_pos;
    int width;
    int height;
    int health;
    Character(int start_x, int start_y, int start_width, int start_height, int start_health);
    SDL_Texture *texture;
};

struct Game {
    std::vector<Character *> invaders;
    Character *player;
    Game(int num_invaders, int num_invaders_per_row, int screen_width, int screen_height);
};