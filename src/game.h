#include "map.h"
#include "sys/time.h"
#include "ctime"
class Game
{
public:
  int StartGame();
  bool gameOver = false;
  int totalPellets = 150;
  int score = 0;
  int lives = 3;
  char lastDir = ' ';
  bool moving = true;

  void DeltaTime()
  {
    float lastTick = time(nullptr) * 1000;//Time returns seconds so multiply by 1000 for millisec
    float dt = 0;
    while (1)
    {
        dt = (time(nullptr) * 1000 - lastTick);
        lastTick = time(nullptr) * 1000;
    }
  }
private:
  void CollidedWithGhost(Map map)
  {
      for (size_t i = 0; i < 4; ++i)
          if(map.pacmanPos.x == map.ghosts[i].x && map.pacmanPos.y == map.ghosts[i].y)
            --lives;
  }
};
