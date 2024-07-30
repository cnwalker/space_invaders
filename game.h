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
  Character(int start_x, int start_y, int start_width, int start_height,
            int start_health);
  SDL_Texture *texture;
};

struct Player : public Character {
  bool moving_right;
  bool moving_left;
  int movement_speed;
  Player(int start_x, int start_y, int start_width, int start_height,
         int start_health);
};

class Game {
public:
  int invader_movement_speed;
  int screen_width;
  int screen_height;
  int invader_width;
  int invader_height;
  int invaders_per_row;
  int invader_margin;

  Player *player;
  std::vector<Character *> invaders;

  Game(int num_invaders, int num_invaders_per_row, int invader_move_speed,
       int input_screen_width, int input_screen_height);
  void runStep();

private:
  void movePlayer();
  void moveInvaders();
  void resetInvaderXPositions();
};