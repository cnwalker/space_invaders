#include "game.h"

Character::Character(int start_x, int start_y, int start_width,
                     int start_height, int start_health) {
  x_pos = start_x;
  y_pos = start_y;
  width = start_width;
  height = start_height;
  health = start_health;
};

Game::Game(int num_invaders, int screen_width, int screen_height) {
  int player_width = 50;
  int player_height = 50;
  player = new Character(screen_width / 2, screen_height - player_height - 20,
                         player_width, player_height, 3);

  int invader_width = (screen_width / 2) / num_invaders;
  int invader_height = (screen_height / 2) / num_invaders;
  int next_start_x = invader_width / 2;
  int next_start_y = invader_height / 2;
  int invader_margin = std::max(invader_width / 4, 10);
  int max_invaders_per_row =
      ((3 * screen_width) / 4) / (invader_width + invader_margin);

  for (int cur_invaders = 0; cur_invaders < num_invaders; cur_invaders++) {
    Character invader =
        Character(next_start_x, next_start_y, invader_width, invader_height, 1);
    invaders.push_back(invader);
    next_start_x += invader_width;
    if (cur_invaders % max_invaders_per_row == 0) {
      next_start_y += invader_height + invader_margin;
    }
  }
};