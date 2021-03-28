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
    "eeewpweeeReeewpweee",
    "wwwwpwewwewwewpwwww",
    "eeeepeewBPOweepeeee",
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

  void GenerateMap()
  {
      for (size_t i = 0; i < 21; ++i)
      {
        for (size_t j = 0; j < 20; ++j)
        {
          if(GetYX(i, j) == 'w')
          {
            vita2d_draw_rectangle(x, y, tileUnitSize, tileUnitSize, RGBA8(0, 0, 255, 255));
              //Draw a wall
          }
          else if(GetYX(i, j) == 'p')
          {
            vita2d_draw_rectangle(x + 6, y + 6, tileUnitSize / 2, tileUnitSize / 2, RGBA8(255, 255, 255, 255));
              //Draw a pellet
          }
          else if(GetYX(i, j) == 's')
          {
            vita2d_draw_rectangle(x + 6, y + 6, tileUnitSize / 2 + 4, tileUnitSize / 2 + 4, RGBA8(255, 0, 0, 255));
              //Draw a special pellet
          }
          else if(GetYX(i, j) == 'e')
          {
            vita2d_draw_rectangle(x, y, tileUnitSize, tileUnitSize, RGBA8(0, 0, 0, 255));
              //Draw empty space
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
          else if(GetYX(i, j) == 'B')//Blue Ghost
          {
              ghosts[0].y = i;
              ghosts[0].x = j;
              vita2d_draw_rectangle(ghosts[0].x * tileUnitSize + 213, ghosts[0].y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(0, 225, 255, 255));
          }
          else if(GetYX(i, j) == 'O')//Orange Ghost
          {
              ghosts[1].y = i;
              ghosts[1].x = j;
              vita2d_draw_rectangle(ghosts[1].x * tileUnitSize + 213, ghosts[1].y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(255, 170, 40, 255));
          }
          else if(GetYX(i, j) == 'P')//Pink Ghost
          {
              ghosts[2].y = i;
              ghosts[2].x = j;
              vita2d_draw_rectangle(ghosts[2].x * tileUnitSize + 213, ghosts[2].y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(255, 115, 210, 255));
          }
          else if(GetYX(i, j) == 'R')//Red Ghost
          {
              ghosts[3].y = i;
              ghosts[3].x = j;
              vita2d_draw_rectangle(ghosts[3].x * tileUnitSize + 213, ghosts[3].y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(255, 0, 0, 255));
          }
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
          if(pacmanPos.y > ghosts[i].y)//If pacman is below the ghost
          {
              if(pacmanPos.x >= ghosts[i].x)
              {
                    if(GetYX(ghosts[i].y + 1, ghosts[i].x) != 'w' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'P') //Down
                    {
                      Move(ghosts[i], true, 1);
                      continue;
                    }
                    else if(GetYX(ghosts[i].y + 1, ghosts[i].x) == 'w' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'P')
                      ghosts[i].lastDirection = ' ';

                    if(GetYX(ghosts[i].y, ghosts[i].x + 1) != 'w' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'P')//Right
                    {
                      Move(ghosts[i], false, 1);
                      continue;
                    }
                    else if(GetYX(ghosts[i].y, ghosts[i].x + 1) == 'w' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'P')
                      ghosts[i].lastDirection = ' ';

                    if(GetYX(ghosts[i].y, ghosts[i].x - 1) != 'w' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'P')//Left
                    {
                      Move(ghosts[i], false, -1);
                      continue;
                    }
                    else if(GetYX(ghosts[i].y, ghosts[i].x - 1) == 'w' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'P')
                      ghosts[i].lastDirection = ' ';

                    if(GetYX(ghosts[i].y - 1, ghosts[i].x) != 'w' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'P')//Up
                    {
                      Move(ghosts[i], true, -1);
                      continue;
                    }
                    else if(GetYX(ghosts[i].y - 1, ghosts[i].x) == 'w' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'P')
                      ghosts[i].lastDirection = ' ';
                  }
                  else
                  {
                      if(GetYX(ghosts[i].y + 1, ghosts[i].x) != 'w' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'P') //Down
                      {
                        Move(ghosts[i], true, 1);
                        continue;
                      }
                      else if(GetYX(ghosts[i].y + 1, ghosts[i].x) == 'w' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'P')
                        ghosts[i].lastDirection = ' ';

                      if(GetYX(ghosts[i].y, ghosts[i].x - 1) != 'w' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'P')//Left
                      {
                        Move(ghosts[i], false, -1);
                        continue;
                      }
                      else if(GetYX(ghosts[i].y, ghosts[i].x - 1) == 'w' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'P')
                        ghosts[i].lastDirection = ' ';

                      if(GetYX(ghosts[i].y, ghosts[i].x + 1) != 'w' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'P')//Right
                      {
                        Move(ghosts[i], false, 1);
                        continue;
                      }
                      else if(GetYX(ghosts[i].y, ghosts[i].x + 1) == 'w' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'P')
                        ghosts[i].lastDirection = ' ';

                      if(GetYX(ghosts[i].y - 1, ghosts[i].x) != 'w' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'P')//Up
                      {
                        Move(ghosts[i], true, -1);
                        continue;
                      }
                      else if(GetYX(ghosts[i].y - 1, ghosts[i].x) == 'w' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'P')
                        ghosts[i].lastDirection = ' ';
                  }
          }
          else if(pacmanPos.y <= ghosts[i].y)//If pacman is above the ghost
          {
            if(pacmanPos.x <= ghosts[i].x)
            {
                if(GetYX(ghosts[i].y - 1, ghosts[i].x) != 'w' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'P')//Up
                {
                  Move(ghosts[i], true, -1);
                  continue;
                }
                else if(GetYX(ghosts[i].y - 1, ghosts[i].x) == 'w' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'P')
                  ghosts[i].lastDirection = ' ';

                if(GetYX(ghosts[i].y, ghosts[i].x - 1) != 'w' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'P')//Left
                {
                  Move(ghosts[i], false, -1);
                  continue;
                }
                else if(GetYX(ghosts[i].y, ghosts[i].x - 1) == 'w' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'P')
                  ghosts[i].lastDirection = ' ';

                if(GetYX(ghosts[i].y, ghosts[i].x + 1) != 'w' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'P')//Right
                {
                  Move(ghosts[i], false, 1);
                  continue;
                }
                else if(GetYX(ghosts[i].y, ghosts[i].x + 1) == 'w' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'P')
                  ghosts[i].lastDirection = ' ';

                if(GetYX(ghosts[i].y + 1, ghosts[i].x) != 'w' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'P') //Down
                {
                  Move(ghosts[i], true, 1);
                  continue;
                }
                else if(GetYX(ghosts[i].y + 1, ghosts[i].x) == 'w' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'P')
                  ghosts[i].lastDirection = ' ';
            }
            else
            {
                if(GetYX(ghosts[i].y - 1, ghosts[i].x) != 'w' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'P')//Up
                {
                  Move(ghosts[i], true, -1);
                  continue;
                }
                else if(GetYX(ghosts[i].y - 1, ghosts[i].x) == 'w' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y - 1, ghosts[i].x) != 'P')
                  ghosts[i].lastDirection = ' ';

                if(GetYX(ghosts[i].y, ghosts[i].x + 1) != 'w' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'P')//Right
                {
                  Move(ghosts[i], false, 1);
                  continue;
                }
                else if(GetYX(ghosts[i].y, ghosts[i].x + 1) == 'w' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x + 1) != 'P')
                  ghosts[i].lastDirection = ' ';

                if(GetYX(ghosts[i].y, ghosts[i].x - 1) != 'w' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'P')//Left
                {
                  Move(ghosts[i], false, -1);
                  continue;
                }
                else if(GetYX(ghosts[i].y, ghosts[i].x - 1) == 'w' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'R' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'B' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'O' && GetYX(ghosts[i].y, ghosts[i].x - 1) != 'P')
                  ghosts[i].lastDirection = ' ';

                if(GetYX(ghosts[i].y + 1, ghosts[i].x) != 'w' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'P') //Down
                {
                  Move(ghosts[i], true, 1);
                  continue;
                }
                else if(GetYX(ghosts[i].y + 1, ghosts[i].x) == 'w' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'R' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'B' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'O' && GetYX(ghosts[i].y + 1, ghosts[i].x) != 'P')
                  ghosts[i].lastDirection = ' ';
             }
          }
       }
    }

    void Move(Character& ghost, bool isYAxis, int step)
    {
      if(isYAxis)
      {
          if(step < 0 && ghost.lastDirection != 'D' || step > 0 && ghost.lastDirection != 'U')
          {
              SetYX(ghost.y, ghost.x, ghost.currentCell);
              char targetLocation = GetYX(ghost.y + step, ghost.x);
              if(targetLocation != 'w' && targetLocation != 'R' && targetLocation != 'B' && targetLocation != 'O' && targetLocation != 'P')
                 ghost.currentCell = targetLocation;
              ghost.y = ghost.y + step;
              SetYX(ghost.y, ghost.x, ghost.icon);
              SetYX(ghost.y - step, ghost.x, ghost.currentCell);
              if( step < 0 )
                ghost.lastDirection = 'U';
              else
                ghost.lastDirection = 'D';
            }
        }
        else
        {
            if(step < 0 && ghost.lastDirection != 'R')
            {
                SetYX(ghost.y, ghost.x, ghost.currentCell);
                if(GetYX(ghost.y, ghost.x - 1) != 'w' && GetYX(ghost.y, ghost.x - 1) != 'R' && GetYX(ghost.y, ghost.x - 1) != 'B' && GetYX(ghost.y, ghost.x - 1) != 'O' && GetYX(ghost.y, ghost.x - 1) != 'P')//Left
                  ghost.currentCell = GetYX(ghost.y, ghost.x - 1);

                ghost.x = ghost.x + step;
                SetYX(ghost.y, ghost.x, ghost.icon);
                SetYX(ghost.y, ghost.x + 1, ghost.currentCell);
                ghost.lastDirection = 'L';
            }
            else if(step > 0 && ghost.lastDirection != 'L')
            {
                SetYX(ghost.y, ghost.x, ghost.currentCell);
                if(GetYX(ghost.y, ghost.x + 1) != 'w' && GetYX(ghost.y, ghost.x + 1) != 'R' && GetYX(ghost.y, ghost.x + 1) != 'B' && GetYX(ghost.y, ghost.x + 1) != 'O' && GetYX(ghost.y, ghost.x + 1) != 'P')//Right
                  ghost.currentCell = GetYX(ghost.y, ghost.x + 1);

                ghost.x = ghost.x + step;
                SetYX(ghost.y, ghost.x, ghost.icon);
                SetYX(ghost.y, ghost.x - 1, ghost.currentCell);
                ghost.lastDirection = 'R';
            }

        }
    }
};
