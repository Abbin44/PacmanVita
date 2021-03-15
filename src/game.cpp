#include <string>
#include <cstring>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <vita2d.h>

#include "screen.h"
#include "game.h"
#include "player.h"
#include "map.h"

void Game::StartGame()
{
    vita2d_init();
    vita2d_set_clear_color(RGBA8(0, 0, 0, 255));

    vita2d_pgf *pgf;
    pgf = vita2d_load_default_pgf();
    Map map;
    Screen screen;

    SceCtrlData ctrl;
    memset(&ctrl, 0, sizeof(ctrl));

    while (gameOver == false)
    {
      vita2d_start_drawing();
      vita2d_clear_screen();

      std::string pacX = std::to_string(map.pacmanPos.x);
      std::string pacY = std::to_string(map.pacmanPos.y);
      std::string scrString = "Score: " + std::to_string(score);

      vita2d_pgf_draw_text(pgf, 30, 30, RGBA8(0,255,0,255), 1.0f, pacX.data());
      vita2d_pgf_draw_text(pgf, 30, 60, RGBA8(0,255,0,255), 1.0f, pacY.data());
      vita2d_pgf_draw_text(pgf, 698, screen.screenHeight - 19, RGBA8(0,255,0,255), 1.0f, scrString.data());

      sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
      sceCtrlPeekBufferPositive(0, &ctrl, 1);

      if(ctrl.buttons & SCE_CTRL_UP)//Move up
      {
        switch (map.mapString[map.pacmanPos.y - 1][map.pacmanPos.x])
        {
          case 'w': break; //Wall
          case 'p': //Normal pellet
            --totalPellets;
            ++score;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'e';
            --map.pacmanPos.y;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'Y';
            break;
          case 's': //Special pellet
            --totalPellets;
            ++score;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'e';
            --map.pacmanPos.y;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'Y';
            break;
          case 'e': //Empty void
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'e';
            --map.pacmanPos.y;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'Y';
            break;
          default: break;
        }

      }
      else if(ctrl.buttons & SCE_CTRL_DOWN)//Move down
      {
        switch (map.mapString[map.pacmanPos.y + 1][map.pacmanPos.x])
        {
          case 'w': break;
          case 'p':
            --totalPellets;
            ++score;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'e';
            ++map.pacmanPos.y;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'Y';
            break;
          case 's': //Special pellet
            --totalPellets;
            ++score;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'e';
            ++map.pacmanPos.y;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'Y';
            break;
          case 'e':
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'e';
            ++map.pacmanPos.y;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'Y';
            break;
          default: break;
        }
      }
      else if(ctrl.buttons & SCE_CTRL_LEFT)//Move to the left
      {
        if(map.pacmanPos.y == 9 && map.pacmanPos.x == 0)//Left screen hole
        {
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'e';
            map.pacmanPos.x = 18;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'Y';
        }

        switch (map.mapString[map.pacmanPos.y][map.pacmanPos.x - 1])
        {
          case 'w': break;
          case 'p':
            --totalPellets;
            ++score;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'e';
            --map.pacmanPos.x;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'Y';
            break;
          case 's': //Special pellet
            --totalPellets;
            ++score;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'e';
            --map.pacmanPos.x;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'Y';
            break;
          case 'e':
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'e';
            --map.pacmanPos.x;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'Y';
            break;
          default: break;
        }
      }
      else if(ctrl.buttons & SCE_CTRL_RIGHT)//Move to the right
      {
        if(map.pacmanPos.y == 9 && map.pacmanPos.x == 18)//Right screen hole
        {
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'e';
            map.pacmanPos.x = 0;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'Y';
        }

        switch (map.mapString[map.pacmanPos.y][map.pacmanPos.x + 1])
        {
          case 'w': break;
          case 'p':
            --totalPellets;
            ++score;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'e';
            ++map.pacmanPos.x;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'Y';
            break;
          case 's': //Special pellet
            --totalPellets;
            ++score;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'e';
            ++map.pacmanPos.x;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'Y';
            break;
          case 'e':
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'e';
            ++map.pacmanPos.x;
            map.mapString[map.pacmanPos.y][map.pacmanPos.x] = 'Y';
            break;
          default: break;
        }
      }

      if (ctrl.buttons & SCE_CTRL_START) //Exit
  			break;

        map.GenerateMap();

        vita2d_end_drawing();
        vita2d_swap_buffers();

        //1000000 is one second
        //Currently sleeping 75ms
        sceKernelDelayThread(75000);
    }
    vita2d_fini();
}
