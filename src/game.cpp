#include <string>
#include <cstring>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/clib.h>
#include <vita2d.h>

#include "screen.h"
#include "game.h"
#include "map.h"

void Game::StartGame()
{
    vita2d_init();

    vita2d_pgf *pgf;
    pgf = vita2d_load_default_pgf();
    Map map;
    map.rGhostPos.icon = 'R';
    map.gGhostPos.icon = 'G';
    map.oGhostPos.icon = 'O';
    map.pGhostPos.icon = 'P';

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

      std::string a = "RGhostX: " + std::to_string(map.rGhostPos.x);
      std::string b = "RGhostY: " + std::to_string(map.rGhostPos.y);
      std::string c = "GGhostX: " + std::to_string(map.gGhostPos.x);
      std::string d = "GGhostY: " + std::to_string(map.gGhostPos.y);
      std::string e = "PGhostX: " + std::to_string(map.pGhostPos.x);
      std::string f = "PGhostY: " + std::to_string(map.pGhostPos.y);
      std::string g = "OGhostX: " + std::to_string(map.oGhostPos.x);
      std::string h = "OGhostY: " + std::to_string(map.oGhostPos.y);

      sceClibPrintf("%d\n", map.rGhostPos.x);
      sceClibPrintf("%o\n", map.rGhostPos.y);
      sceClibPrintf("%u\n", map.gGhostPos.x);
      sceClibPrintf("%d\n", map.gGhostPos.y);
      sceClibPrintf("%d\n", map.pGhostPos.x);
      sceClibPrintf("%d\n", map.pGhostPos.y);
      sceClibPrintf("%d\n", map.oGhostPos.x);
      sceClibPrintf("%d\n", map.oGhostPos.y);

      vita2d_pgf_draw_text(pgf, 30, 30, RGBA8(0,255,0,255), 1.0f, pacX.data());
      vita2d_pgf_draw_text(pgf, 30, 60, RGBA8(0,255,0,255), 1.0f, pacY.data());
      vita2d_pgf_draw_text(pgf, 30, 90, RGBA8(0,255,0,255), 1.0f, a.data());
      vita2d_pgf_draw_text(pgf, 30, 120, RGBA8(0,255,0,255), 1.0f, b.data());
      vita2d_pgf_draw_text(pgf, 30, 150, RGBA8(0,255,0,255), 1.0f, c.data());
      vita2d_pgf_draw_text(pgf, 30, 180, RGBA8(0,255,0,255), 1.0f, d.data());
      vita2d_pgf_draw_text(pgf, 30, 210, RGBA8(0,255,0,255), 1.0f, e.data());
      vita2d_pgf_draw_text(pgf, 30, 240, RGBA8(0,255,0,255), 1.0f, f.data());
      vita2d_pgf_draw_text(pgf, 30, 270, RGBA8(0,255,0,255), 1.0f, g.data());
      vita2d_pgf_draw_text(pgf, 30, 300, RGBA8(0,255,0,255), 1.0f, h.data());

      vita2d_pgf_draw_text(pgf, 698, screen.screenHeight - 19, RGBA8(0,255,0,255), 1.0f, scrString.data());

      sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
      sceCtrlPeekBufferPositive(0, &ctrl, 1);

      if(ctrl.buttons & SCE_CTRL_UP)//Move up
      {
        switch (map.GetYX(map.pacmanPos.y - 1, map.pacmanPos.x))
        {
          case 'w': break; //Wall
          case 'p': //Normal pellet
            --totalPellets;
            ++score;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            --map.pacmanPos.y;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 3;
            break;
          case 's': //Special pellet
            --totalPellets;
            ++score;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            --map.pacmanPos.y;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 3;
            break;
          case 'e': //Empty
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            --map.pacmanPos.y;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 3;
            break;
          default: break;
        }

      }
      else if(ctrl.buttons & SCE_CTRL_DOWN)//Move down
      {
        switch (map.GetYX(map.pacmanPos.y + 1, map.pacmanPos.x))
        {
          case 'w': break;
          case 'p':
            --totalPellets;
            ++score;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            ++map.pacmanPos.y;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 4;
            break;
          case 's': //Special pellet
            --totalPellets;
            ++score;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            ++map.pacmanPos.y;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 4;
            break;
          case 'e'://Empty
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            ++map.pacmanPos.y;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 4;
            break;
          default: break;
        }
      }
      else if(ctrl.buttons & SCE_CTRL_LEFT)//Move to the left
      {
        if(map.pacmanPos.y == 9 && map.pacmanPos.x == 0)//Left screen hole
        {
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            map.pacmanPos.x = 19;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 2;
            break;
        }

        switch (map.GetYX(map.pacmanPos.y, map.pacmanPos.x - 1))
        {
          case 'w': break;
          case 'p':
            --totalPellets;
            ++score;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            --map.pacmanPos.x;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 2;
            break;
          case 's': //Special pellet
            --totalPellets;
            ++score;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            --map.pacmanPos.x;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 2;
            break;
          case 'e'://Empty
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            --map.pacmanPos.x;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 2;
            break;
          default: break;
        }
      }
      else if(ctrl.buttons & SCE_CTRL_RIGHT)//Move to the right
      {
        if(map.pacmanPos.y == 9 && map.pacmanPos.x == 18)//Right screen hole
        {
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            map.pacmanPos.x = 0;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 1;
            break;
        }

        switch (map.GetYX(map.pacmanPos.y, map.pacmanPos.x + 1))
        {
          case 'w': break;
          case 'p':
            --totalPellets;
            ++score;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            ++map.pacmanPos.x;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 1;
            break;
          case 's': //Special pellet
            --totalPellets;
            ++score;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            ++map.pacmanPos.x;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 1;
            break;
          case 'e':
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            ++map.pacmanPos.x;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 1;
            break;
          default: break;
        }
      }

      if (ctrl.buttons & SCE_CTRL_SELECT) //Exit
  			break;

        map.GenerateMap();
        map.MoveGhosts();

        vita2d_end_drawing();
        vita2d_swap_buffers();

        //1000000 is one second
        //Currently sleeping 75ms
        sceKernelDelayThread(75000);
    }
    vita2d_fini();
}
