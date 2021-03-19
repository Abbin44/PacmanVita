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
    "eeeepeewGPOweepeeee",
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
  Character ghosts[0];
  Character ghosts[1];
  Character ghosts[2];
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
            x += tileUnitSize;
              //Draw a wall
          }
          else if(GetYX(i, j) == 'p')
          {
            vita2d_draw_rectangle(x + 6, y + 6, tileUnitSize / 2, tileUnitSize / 2, RGBA8(255, 255, 255, 255));
            x += tileUnitSize;
              //Draw a pellet
          }
          else if(GetYX(i, j) == 's')
          {
            vita2d_draw_rectangle(x + 6, y + 6, tileUnitSize / 2 + 4, tileUnitSize / 2 + 4, RGBA8(255, 0, 0, 255));
            x += tileUnitSize;
              //Draw a special pellet
          }
          else if(GetYX(i, j) == 'e')
          {
            vita2d_draw_rectangle(x, y, tileUnitSize, tileUnitSize, RGBA8(0, 0, 0, 255));
            x += tileUnitSize;
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
              //vita2d_draw_fill_circle(pacmanPos.x * tileUnitSize + 213 + 12, pacmanPos.y * tileUnitSize + 12, 12, RGBA8(255, 255, 0, 255));//Yellow pacman
              x += tileUnitSize;
          }
          else if(GetYX(i, j) == 'G')//Green Ghost
          {
              ghosts[0].y = i;
              ghosts[0].x = j;
              vita2d_draw_rectangle(ghosts[0].x * tileUnitSize + 213, ghosts[0].y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(0, 255, 0, 255));
              x += tileUnitSize;
          }
          else if(GetYX(i, j) == 'O')//Orange Ghost
          {
              ghosts[1].y = i;
              ghosts[1].x = j;
              vita2d_draw_rectangle(ghosts[1].x * tileUnitSize + 213, ghosts[1].y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(255, 170, 40, 255));
              x += tileUnitSize;
          }
          else if(GetYX(i, j) == 'P')//Pink Ghost
          {
              ghosts[2].y = i;
              ghosts[2].x = j;
              vita2d_draw_rectangle(ghosts[2].x * tileUnitSize + 213, ghosts[2].y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(255, 115, 210, 255));
              x += tileUnitSize;
          }
          else if(GetYX(i, j) == 'R')//Red Ghost
          {
              ghosts[3].y = i;
              ghosts[3].x = j;
              vita2d_draw_rectangle(ghosts[3].x * tileUnitSize + 213, ghosts[3].y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(255, 0, 0, 255));
              x += tileUnitSize;
          }
        }
        y += tileUnitSize;
        x = 213;
      }
      x = 213;
      y = 0;
  }


  /*
  -536496295
  20110006750
  201359368
  1
  0
  0
  0
  0
  */
  void MoveGhosts()
  {
      for (size_t i = 0; i < 4; ++i)
      {
          if(pacmanPos.y > ghosts[i].y)
          {
              if(GetYX(ghosts[i].y + 1, ghosts[i].x) != 'w') //Down
              {
                  ghosts[i].currentCell = GetYX(ghosts[i].y + 1, ghosts[i].x);
                  ++ghosts[i].y;
                  SetYX(ghosts[i].y, ghosts[i].x, ghosts[i].icon);
                  SetYX(ghosts[i].y - 1, ghosts[i].x, ghosts[i].currentCell);
                  continue;
              }

              if(GetYX(ghosts[i].y - 1, ghosts[i].x) != 'w')//Up
              {
                  ghosts[i].currentCell = GetYX(ghosts[i].y - 1, ghosts[i].x);
                  --ghosts[i].y;
                  SetYX(ghosts[i].y, ghosts[i].x, ghosts[i].icon);
                  SetYX(ghosts[i].y + 1, ghosts[i].x, ghosts[i].currentCell);
                  continue;
              }

              if(GetYX(ghosts[i].y, ghosts[i].x + 1) != 'w')//Right
              {
                  ghosts[i].currentCell = GetYX(ghosts[i].y, ghosts[i].x + 1);
                  ++ghosts[i].x;
                  SetYX(ghosts[i].y, ghosts[i].x, ghosts[i].icon);
                  SetYX(ghosts[i].y, ghosts[i].x - 1, ghosts[i].currentCell);
                  continue;
              }

              if(GetYX(ghosts[i].y, ghosts[i].x - 1) != 'w')//Left
              {
                  ghosts[i].currentCell = GetYX(ghosts[i].y, ghosts[i].x - 1);
                  --ghosts[i].x;
                  SetYX(ghosts[i].y, ghosts[i].x, ghosts[i].icon);
                  SetYX(ghosts[i].y, ghosts[i].x + 1, ghosts[i].currentCell);
                  continue;
              }
          }
      }

    void Move(Character ghost, bool isYAxis, int step)
    {
        if(isYAxis)
        {
            if(step < 0)
              ghost.currentCell = GetYX(ghost.y - 1, ghost.x);
            else
              ghost.currentCell = GetYX(ghost.y + 1, ghost.x);

            ghost.y + step;
            SetYX(ghost.y, ghost.x, ghost.icon);
            SetYX(ghost.y, ghost.x, ghost.currentCell);
        }
        else
        {
            if(step < 0)
              ghost.currentCell = GetYX(ghost.y, ghost.x - 1);
            else
              ghost.currentCell = GetYX(ghost.y, ghost.x + 1);

              ghost.x + step;
              SetYX(ghost.y, ghost.x, ghost.icon);
              SetYX(ghost.y, ghost.x, ghost.currentCell);
        }
    }
  }
};
