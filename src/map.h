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
  Character rGhostPos;
  Character gGhostPos;
  Character oGhostPos;
  Character pGhostPos;
  Character ghosts[4] = {rGhostPos, gGhostPos, oGhostPos, pGhostPos};
  vita2d_texture *pacmanSR = vita2d_load_PNG_file("app0:assets/pacmanR.png");
  vita2d_texture *pacmanSL = vita2d_load_PNG_file("app0:assets/pacmanL.png");
  vita2d_texture *pacmanSU = vita2d_load_PNG_file("app0:assets/pacmanU.png");
  vita2d_texture *pacmanSD = vita2d_load_PNG_file("app0:assets/pacmanD.png");

  void GenerateMap()
  {
      for (size_t i = 0; i < 21; ++i)
      {
        for (size_t j = 0; j < 20; ++j)
        {
          if(mapString[i][j] == 'w')
          {
            vita2d_draw_rectangle(x, y, tileUnitSize, tileUnitSize, RGBA8(0, 0, 255, 255));
            x += tileUnitSize;
              //Draw a wall
          }
          else if(mapString[i][j] == 'p')
          {
            vita2d_draw_rectangle(x + 6, y + 6, tileUnitSize / 2, tileUnitSize / 2, RGBA8(255, 255, 255, 255));
            x += tileUnitSize;
              //Draw a pellet
          }
          else if(mapString[i][j] == 's')
          {
            vita2d_draw_rectangle(x + 6, y + 6, tileUnitSize / 2 + 4, tileUnitSize / 2 + 4, RGBA8(255, 0, 0, 255));
            x += tileUnitSize;
              //Draw a special pellet
          }
          else if(mapString[i][j] == 'e')
          {
            vita2d_draw_rectangle(x, y, tileUnitSize, tileUnitSize, RGBA8(0, 0, 0, 255));
            x += tileUnitSize;
              //Draw empty space
          }
          else if(mapString[i][j] == 'Y')//Pacman
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
          else if(mapString[i][j] == 'G')//Green Ghost
          {
              gGhostPos.y = i;
              gGhostPos.x = j;
              vita2d_draw_rectangle(gGhostPos.x * tileUnitSize + 213, gGhostPos.y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(0, 255, 0, 255));
              x += tileUnitSize;
          }
          else if(mapString[i][j] == 'O')//Orange Ghost
          {
              oGhostPos.y = i;
              oGhostPos.x = j;
              vita2d_draw_rectangle(oGhostPos.x * tileUnitSize + 213, oGhostPos.y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(255, 170, 40, 255));
              x += tileUnitSize;
          }
          else if(mapString[i][j] == 'P')//Pink Ghost
          {
              pGhostPos.y = i;
              pGhostPos.x = j;
              vita2d_draw_rectangle(pGhostPos.x * tileUnitSize + 213, pGhostPos.y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(255, 115, 210, 255));
              x += tileUnitSize;
          }
          else if(mapString[i][j] == 'R')//Red Ghost
          {
              rGhostPos.y = i;
              rGhostPos.x = j;
              vita2d_draw_rectangle(rGhostPos.x * tileUnitSize + 213, rGhostPos.y * tileUnitSize, tileUnitSize, tileUnitSize, RGBA8(255, 0, 0, 255));
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
          if (pacmanPos.y > ghosts[i].y && ghosts[i].lastDirection != 'U')//GO DOWN
          {
              if (mapString[ghosts[i].y + 1][ghosts[i].x] != 'w')//If char below ghost is not a wall
              {
                 ghosts[i].currentCell = mapString[ghosts[i].y + 1][ghosts[i].x];
                 ++ghosts[i].y;
                 mapString[ghosts[i].y - 1][ghosts[i].x] = ghosts[i].currentCell;
                 mapString[ghosts[i].y][ghosts[i].x] = ghosts[i].icon;
                 ghosts[i].lastDirection = 'D';
                 continue;
              }
          }
          else if(pacmanPos.y < ghosts[i].y && ghosts[i].lastDirection != 'D')//GO UP
          {
              if (mapString[ghosts[i].y - 1][ghosts[i].x] != 'w')
              {
                ghosts[i].currentCell = mapString[ghosts[i].y - 1][ghosts[i].x];
                --ghosts[i].y;
                mapString[ghosts[i].y + 1][ghosts[i].x] = ghosts[i].currentCell;
                mapString[ghosts[i].y][ghosts[i].x] = ghosts[i].icon;
                ghosts[i].lastDirection = 'U';
                continue;
              }
          }
          else if(pacmanPos.x < ghosts[i].x && ghosts[i].lastDirection != 'R')//GO LEFT
          {
              if (mapString[ghosts[i].y][ghosts[i].x - 1] != 'w')
              {
                ghosts[i].currentCell = mapString[ghosts[i].y][ghosts[i].x - 1];
                --ghosts[i].x;
                mapString[ghosts[i].y][ghosts[i].x + 1] = ghosts[i].currentCell;
                mapString[ghosts[i].y][ghosts[i].x] = ghosts[i].icon;
                ghosts[i].lastDirection = 'L';
                continue;
              }
          }
          else if(pacmanPos.x > ghosts[i].x && ghosts[i].lastDirection != 'L')//GO RIGHT
          {
              if (mapString[ghosts[i].y][ghosts[i].x + 1] != 'w')
              {
                ghosts[i].currentCell = mapString[ghosts[i].y][ghosts[i].x + 1];
                ++ghosts[i].x;
                mapString[ghosts[i].y][ghosts[i].x - 1] = ghosts[i].currentCell;
                mapString[ghosts[i].y][ghosts[i].x] = ghosts[i].icon;
                ghosts[i].lastDirection = 'R';
                continue;
              }
          }
      }
  }
};
