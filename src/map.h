#include <vita2d.h>

#include <iostream>
#include "character.h"
class Map
{
private:
  int x = 213;//Position of tile to be drawn
  int y = 0;
public:
  char mapString[21][20] = {
    "wwwwwwwwwwwwwwwwwww",
    "wppppppppwppppppppw",
    "wswwpwwwpwpwwwpwwsw",
    "wpppppppppppppppppw",
    "wpwwpwpwwwwwpwpwwpw",
    "wppppwpppwpppwppppw",
    "wwwwpwwwewewwwpwwww",
    "eeewpweeeeeeewpweee",
    "wwwwpwewwewwewpwwww",
    "eeeepeeweeeweepeeee",
    "wwwwpwewwwwwewpwwww",
    "eeewpweeeeeeewpweee",
    "wwwwpwewwwwwewpwwww",
    "wppppppppwppppppppw",
    "wpwwpwwwpwpwwwpwwpw",
    "wspwpppppYpppppwpsw",
    "wwpwpwpwwwwwpwpwpww",
    "wppppwpppwpppwppppw",
    "wpwwwwwwpwpwwwwwwpw",
    "wpppppppppppppppppw",
    "wwwwwwwwwwwwwwwwwww",
  };
  int tileUnitSize = 25;//The size of one unit
  Character pacmanPos;
  Character ghosts[4];
  vita2d_texture *pacmanSR = vita2d_load_PNG_file("app0:assets/pacmanR.png");
  vita2d_texture *pacmanSL = vita2d_load_PNG_file("app0:assets/pacmanL.png");
  vita2d_texture *pacmanSU = vita2d_load_PNG_file("app0:assets/pacmanU.png");
  vita2d_texture *pacmanSD = vita2d_load_PNG_file("app0:assets/pacmanD.png");

  char GetYX(int y, int x)
  {
    if(y < 21 && y > -1 && x < 20 && x > -1)
      return mapString[y][x];
    else
      throw "out of bounds error";
  }

  void SetYX(int y, int x, char symbol)
  {
      if(y < 21 && y > -1 && x < 20 && x > -1)
          mapString[y][x] = symbol;
      else
        return;
  }

  bool ContainsGhost(int y, int x)
  {
      if(ghosts[0].y == y && ghosts[0].x == x || ghosts[1].y == y && ghosts[1].x == x || ghosts[2].y == y && ghosts[2].x == x || ghosts[3].y == y && ghosts[3].x == x)
        return true;
      else
        return false;
  }

  bool ContainsWall(int y, int x)
  {
      if(GetYX(y, x) == 'w')
        return true;
      else
        return false;
  }

  bool TryMove(Character& ghost, int yStep, int xStep)
  {
      if(ContainsGhost(ghost.y + yStep, ghost.x + xStep) == false && ContainsWall(ghost.y + yStep, ghost.x + xStep) == false) //Down
      {
          if(ghost.y + yStep < 0 || ghost.y + yStep > 20 || ghost.x + xStep < 0 || ghosts.x + xStep > 20)
          {
              ghost.lastDirection = ' ';
              return false;
          }
          if(yStep > 0 || yStep < 0)
            return Move(ghost, true, yStep);
          else
            return Move(ghost, false, xStep);
      }
        return false;
  }

  bool isInStartingArea(Character& ghost)
  {
      if(ghost.y >= 8 && ghost.y <= 10 && ghost.x >= 7 && ghost.x <= 11)
        return true;

      return false;
  }

  void DrawMap()
  {
      for (size_t i = 0; i < 21; ++i)
      {
        for (size_t j = 0; j < 20; ++j)
        {
          if(GetYX(i, j) == 'w')
          {
            vita2d_draw_rectangle(x, y, tileUnitSize, tileUnitSize, RGBA8(0, 0, 255, 255));//Draw a wall
          }
          else if(GetYX(i, j) == 'p')
          {
            vita2d_draw_rectangle(x + 6, y + 6, tileUnitSize / 2, tileUnitSize / 2, RGBA8(255, 255, 255, 255));//Draw a pellet
          }
          else if(GetYX(i, j) == 's')
          {
            vita2d_draw_rectangle(x + 6, y + 6, tileUnitSize / 2 + 4, tileUnitSize / 2 + 4, RGBA8(255, 0, 0, 255));//Draw a special pellet
          }
          else if(GetYX(i, j) == 'e')
          {
            vita2d_draw_rectangle(x, y, tileUnitSize, tileUnitSize, RGBA8(0, 0, 0, 255));//Draw empty space
          }
          else if(GetYX(i, j) == 'Y')//Pacman
          {
              pacmanPos.y = i;
              pacmanPos.x = j;
              switch (pacmanPos.rotation)
              {
                case 1://RIGHT
                    vita2d_draw_texture_scale(pacmanSR, pacmanPos.x * tileUnitSize + 213 + 3, pacmanPos.y * tileUnitSize + 2, 0.4f, 0.4f);
                    break;
                case 2://LEFT
                    vita2d_draw_texture_scale(pacmanSL, pacmanPos.x * tileUnitSize + 213 + 3, pacmanPos.y * tileUnitSize + 2, 0.4f, 0.4f);
                    break;
                case 3://UP
                    vita2d_draw_texture_scale(pacmanSU, pacmanPos.x * tileUnitSize + 213 + 2, pacmanPos.y * tileUnitSize + 2, 0.4f, 0.4f);
                    break;
                case 4://DOWN
                    vita2d_draw_texture_scale(pacmanSD, pacmanPos.x * tileUnitSize + 213 + 3, pacmanPos.y * tileUnitSize + 2, 0.4f, 0.4f);
                    break;
                default:
                    break;
              }
          }

          vita2d_draw_rectangle(ghosts[0].x * tileUnitSize + 213, ghosts[0].y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(0, 225, 255, 255));
          vita2d_draw_rectangle(ghosts[1].x * tileUnitSize + 213, ghosts[1].y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(255, 170, 40, 255));
          vita2d_draw_rectangle(ghosts[2].x * tileUnitSize + 213, ghosts[2].y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(255, 115, 210, 255));
          vita2d_draw_rectangle(ghosts[3].x * tileUnitSize + 213, ghosts[3].y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(255, 0, 0, 255));
          x += tileUnitSize;
        }
        y += tileUnitSize;
        x = 213;
      }
      x = 213;
      y = 0;
  }

  void MoveGhosts()
  {
      for (size_t i = 0; i < 4; ++i)
      {
          bool didMove = false;
          if(isInStartingArea(ghosts[i]))
          {
              if(TryMove(ghosts[i], -1, 0))
                continue;
          }
          if(pacmanPos.y > ghosts[i].y)//If pacman is below the ghost
          {
              if(TryMove(ghosts[i], 1, 0))
              {
                didMove = true;
                continue;
              }
              if(pacmanPos.x >= ghosts[i].x)
              {
                  if(TryMove(ghosts[i], 0, 1))
                  {
                    didMove = true;
                    continue;
                  }
                  if(TryMove(ghosts[i], 0, -1))
                  {
                    didMove = true;
                    continue;
                  }
              }
              else
              {
                  if(TryMove(ghosts[i], 0, -1))
                  {
                    didMove = true;
                    continue;
                  }
                  if(TryMove(ghosts[i], 0, 1))
                  {
                    didMove = true;
                    continue;
                  }
              }
              if(TryMove(ghosts[i], -1, 0))
              {
                didMove = true;
                continue;
              }
          }
          else if(pacmanPos.y <= ghosts[i].y)//If pacman is above the ghost
          {
              if(TryMove(ghosts[i], -1, 0))
              {
                didMove = true;
                continue;
              }
              if(pacmanPos.x <= ghosts[i].x)
              {
                  if(TryMove(ghosts[i], 0, -1))
                  {
                    didMove = true;
                    continue;
                  }
                  if(TryMove(ghosts[i], 0, 1))
                  {
                    didMove = true;
                    continue;
                  }
              }
              else
              {
                  if(TryMove(ghosts[i], 0, 1))
                  {
                    didMove = true;
                    continue;
                  }
                  if(TryMove(ghosts[i], 0, -1))
                  {
                    didMove = true;
                    continue;
                  }
              }
              if(TryMove(ghosts[i], 1, 0))
              {
                didMove = true;
                continue;
              }
          }

          if(!didMove)
            ghosts[i].lastDirection = ' ';
       }
    }

    bool Move(Character& ghost, bool isYAxis, int step)
    {
      if(isYAxis)
      {
          if(step < 0 && ghost.lastDirection != 'D' || step > 0 && ghost.lastDirection != 'U')
          {
              ghost.y = ghost.y + step;

              if(step < 0)
                ghost.lastDirection = 'U';
              else
                ghost.lastDirection = 'D';

                return true;
          }
      }
      else
      {
          if(step < 0 && ghost.lastDirection != 'R' || step > 0 && ghost.lastDirection != 'L')
          {
              ghost.x = ghost.x + step;

              if(step < 0)
                ghost.lastDirection = 'L';
              else
                ghost.lastDirection = 'R';

                return true;
          }
      }
      return false;
    }
};
