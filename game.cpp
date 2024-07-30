#include "game.h"

Character::Character(int start_x, int start_y, int start_width,
                     int start_height, int start_health) {
  x_pos = start_x;
  y_pos = start_y;
  width = start_width;
  height = start_height;
  health = start_health;
};

Player::Player(int start_x, int start_y, int start_width, int start_height,
               int start_health)
    : Character(start_x, start_y, start_width, start_height, start_health) {
  moving_left = false;
  moving_right = false;
  movement_speed = 4;
}

Game::Game(int num_invaders, int num_invaders_per_row, int invader_move_speed,
           int input_screen_width, int input_screen_height) {
  screen_width = input_screen_width;
  screen_height = input_screen_height;
  int player_width = 50;
  int player_height = 50;
  player = new Player(screen_width / 2, screen_height - player_height - 20,
                      player_width, player_height, 3);

  invader_movement_speed = invader_move_speed;
  invaders_per_row = num_invaders_per_row;
  invader_width = (screen_width / 2) / invaders_per_row;
  invader_height = invader_width;
  invader_margin = invader_width / 4;
  int next_start_y = invader_height / 2;

  /**
   * Create invaders with the correct Y positions.
   */
  for (int cur_invader = 0; cur_invader < num_invaders; cur_invader++) {
    Character *invader =
        new Character(0, next_start_y, invader_width, invader_height, 1);
    invaders.push_back(invader);
    if (cur_invader != 0 && (cur_invader + 1) % invaders_per_row == 0) {
      next_start_y += invader_height + invader_margin;
    }
  }

  /**
   * Reset invader X positions.
   */
  resetInvaderXPositions();
};

void Game::resetInvaderXPositions() {
  int next_start_x = invader_width / 2;
  for (int cur_invader = 0; cur_invader < invaders.size(); cur_invader++) {
    Character *invader = invaders.at(cur_invader);
    invader->x_pos = next_start_x;
    next_start_x += invader_width + invader_margin;
    if (cur_invader != 0 && (cur_invader + 1) % invaders_per_row == 0) {
      next_start_x = invader_width / 2;
    }
  }
}

void Game::movePlayer() {
  int player_max_x = screen_width - player->width;
  if (player->moving_right && player->x_pos < player_max_x) {
    player->x_pos += player->movement_speed;
  }
  if (player->moving_left && player->x_pos > 0) {
    player->x_pos -= player->movement_speed;
  }
}

void Game::moveInvaders() {
  bool reached_end_of_line = false;
  for (int i = 0; i < invaders.size(); i++) {
    Character *invader = invaders.at(i);
    if (invader->x_pos >= (screen_width - invader_width - invader_margin)) {
      reached_end_of_line = true;
      break;
    }
  }

  if (reached_end_of_line) {
    for (int cur_invader = 0; cur_invader < invaders.size(); cur_invader++) {
      Character *invader = invaders.at(cur_invader);
      invader->y_pos += invader_height + invader_margin;
    }
    resetInvaderXPositions();
    return;
  }

  for (int cur_invader = 0; cur_invader < invaders.size(); cur_invader++) {
    Character *invader = invaders.at(cur_invader);
    invader->x_pos += invader_movement_speed;
  }
}

void Game::runStep() {
  movePlayer();
  moveInvaders();
}