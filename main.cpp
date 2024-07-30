
#include "game.h"
#include <array>
#include <iostream>

void readInputs() {
  SDL_Event event;

  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      exit(0);
      break;
    default:
      break;
    }
  }
}

void drawCharacter(App *app, Character *character) {
  drawTextureAt(app, character->texture, character->x_pos,
                    character->y_pos, character->width,
                    character->height);
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
  int default_screen_width = 1280;
  int default_screen_height = 720;
  App *app = initSDL(default_screen_width, default_screen_height);
  Game *game = new Game(40, 10, default_screen_width, default_screen_height);

  game->player->texture = loadTexture(app, "assets/star_fox_ship.jpg");

  for (int i = 0; i < game->invaders.size(); i++) {
    game->invaders.at(i)->texture =
        loadTexture(app, "assets/space_invaders_enemy_red.png");
  }

  while (true) {
    prepareScene(app);
    readInputs();
    drawAssets(app, game);
    presentScene(app);
    SDL_Delay(16); // What is this?
  }

  return 0;
}