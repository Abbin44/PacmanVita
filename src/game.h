#include "map.h"

class Game
{
public:
  void StartGame();
  bool gameOver = false;
  int totalPellets = 150;
  int score = 0;
  int lives = 3;
  char lastDir = ' ';
  bool moving = true;
private:
  void CollidedWithGhost(Map map)
  {
      for (size_t i = 0; i < 4; ++i)
          if(map.pacmanPos.x == map.ghosts[i].x && map.pacmanPos.y == map.ghosts[i].y)
            --lives;
  }
};
