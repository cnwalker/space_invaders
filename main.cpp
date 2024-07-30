
#include "game.h"
#include <array>
#include <iostream>

void handleKeyDown(Game *game, SDL_KeyboardEvent *event) {
  if (event->repeat == 0) {
    if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
      game->player->moving_right = true;
      game->player->moving_left = false;
    }

    if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
      game->player->moving_left = true;
      game->player->moving_right = false;
    }
  }
}

void handleKeyUp(Game *game, SDL_KeyboardEvent *event) {
  if (event->repeat == 0) {
    if (event->keysym.scancode == SDL_SCANCODE_RIGHT) {
      game->player->moving_right = false;
    }

    if (event->keysym.scancode == SDL_SCANCODE_LEFT) {
      game->player->moving_left = false;
    }
  }
  return;
}

void readInputs(Game *game) {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      exit(0);
      break;

    case SDL_KEYDOWN:
      handleKeyDown(game, &event.key);
      break;

    case SDL_KEYUP:
      handleKeyUp(game, &event.key);
      break;
    default:
      break;
    }
  }
}

void drawCharacter(App *app, Character *character) {
  drawTextureAt(app, character->texture, character->x_pos, character->y_pos,
                character->width, character->height);
}

void drawAssets(App *app, Game *game) {
  /**
   * First draw the invaders
   */
  for (int i = 0; i < game->invaders.size(); i++) {
    Character *invader = game->invaders.at(i);
    drawCharacter(app, invader);
  }

  /**
   * Then draw the player
   */
  drawCharacter(app, game->player);
}

int main() {
  /**
   * Set up the screen to draw on.
   */
  int default_screen_width = 1280;
  int default_screen_height = 720;
  App *app = initSDL(default_screen_width, default_screen_height);

  /**
   * Set up the game.
   */
  int num_invaders = 30;
  int num_invaders_per_row = 10;
  int invader_movement_speed = 1;
  Game *game =
      new Game(num_invaders, num_invaders_per_row, invader_movement_speed,
               default_screen_width, default_screen_height);

  game->player->texture = loadTexture(app, "assets/star_fox_ship.jpg");

  std::array<char *, 3> enemyTextures = {
      "assets/space_invaders_enemy_red.png",
      "assets/space_invader_3d.png",
      "assets/space_invaders_blue.png",
  };

  int curEnemyTexture = 0;
  for (int i = 0; i < game->invaders.size(); i++) {
    if (i != 0 && i % num_invaders_per_row == 0) {
      curEnemyTexture++;
    }
    game->invaders.at(i)->texture =
        loadTexture(app, enemyTextures[curEnemyTexture % enemyTextures.size()]);
  }

  while (true) {
    prepareScene(app);
    readInputs(game);
    game->runStep();
    drawAssets(app, game);
    presentScene(app);
    SDL_Delay(16); // What is this?
  }

  return 0;
}