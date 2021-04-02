#include <string>
#include <cstring>

#include <psp2/ctrl.h>
#include <psp2/kernel/processmgr.h>
#include <psp2/kernel/clib.h>
#include <vita2d.h>

#include "screen.h"
#include "game.h"

void Game::StartGame()
{
    vita2d_init();
    Map map;
    vita2d_pgf *pgf;
    pgf = vita2d_load_default_pgf();
    vita2d_texture *redHeart = vita2d_load_PNG_file("app0:assets/redHeart.png");
    vita2d_texture *grayHeart = vita2d_load_PNG_file("app0:assets/grayHeart.png");

    map.ghosts[0].x = 9;
    map.ghosts[0].y = 7;
    map.ghosts[1].x = 8;
    map.ghosts[1].y = 9;
    map.ghosts[2].x = 10;
    map.ghosts[2].y = 9;
    map.ghosts[3].x = 9;
    map.ghosts[3].y = 9;
    Screen screen;

    SceCtrlData ctrl;
    memset(&ctrl, 0, sizeof(ctrl));

    while (gameOver == false)
    {
      vita2d_start_drawing();
      vita2d_clear_screen();
      CollidedWithGhost(map);
      std::string pacX = std::to_string(map.pacmanPos.x);
      std::string pacY = std::to_string(map.pacmanPos.y);
      std::string scrString = "Score: " + std::to_string(score);

      vita2d_pgf_draw_text(pgf, 30, 30, RGBA8(0,255,0,255), 1.0f, pacX.data());
      vita2d_pgf_draw_text(pgf, 30, 60, RGBA8(0,255,0,255), 1.0f, pacY.data());
      vita2d_pgf_draw_text(pgf, 698, screen.screenHeight - 19, RGBA8(0,255,0,255), 1.0f, scrString.data());

      if(lives == 3)
      {
        vita2d_draw_texture_scale(redHeart, 700, screen.screenHeight - 60, 1.0f, 1.0f);
        vita2d_draw_texture_scale(redHeart, 780, screen.screenHeight - 60, 1.0f, 1.0f);
        vita2d_draw_texture_scale(redHeart, 860, screen.screenHeight - 60, 1.0f, 1.0f);

      }
      else if(lives == 2)
      {
        vita2d_draw_texture_scale(redHeart, 700, screen.screenHeight - 60, 1.0f, 1.0f);
        vita2d_draw_texture_scale(redHeart, 780, screen.screenHeight - 60, 1.0f, 1.0f);
        vita2d_draw_texture_scale(grayHeart, 860, screen.screenHeight - 60, 1.0f, 1.0f);

      }
      else if(lives == 1)
      {
        vita2d_draw_texture_scale(redHeart, 700, screen.screenHeight - 60, 1.0f, 1.0f);
        vita2d_draw_texture_scale(grayHeart, 780, screen.screenHeight - 60, 1.0f, 1.0f);
        vita2d_draw_texture_scale(grayHeart, 860, screen.screenHeight - 60, 1.0f, 1.0f);

      }
      else if(lives <= 0)
        gameOver = true;

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
        }
        else
        {
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
      }
      else if(ctrl.buttons & SCE_CTRL_RIGHT)//Move to the right
      {
        if(map.pacmanPos.y == 9 && map.pacmanPos.x == 18)//Right screen hole
        {
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');
            map.pacmanPos.x = 0;
            map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
            map.pacmanPos.rotation = 1;
        }
        else
        {
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
      }

      if (ctrl.buttons & SCE_CTRL_SELECT) //Exit
  			break;

        map.DrawMap();
        map.MoveGhosts();

        vita2d_end_drawing();
        vita2d_swap_buffers();

        //1000000 is one second
        //Currently sleeping 90ms
        sceKernelDelayThread(90000);
    }
    vita2d_fini();
    vita2d_free_texture(map.pacmanSR);
    vita2d_free_texture(map.pacmanSL);
    vita2d_free_texture(map.pacmanSU);
    vita2d_free_texture(map.pacmanSD);

    vita2d_free_texture(map.bGhostD);
    vita2d_free_texture(map.bGhostL);
    vita2d_free_texture(map.bGhostR);
    vita2d_free_texture(map.bGhostU);

    vita2d_free_texture(map.oGhostD);
    vita2d_free_texture(map.oGhostL);
    vita2d_free_texture(map.oGhostR);
    vita2d_free_texture(map.oGhostU);

    vita2d_free_texture(map.pGhostD);
    vita2d_free_texture(map.pGhostL);
    vita2d_free_texture(map.pGhostR);
    vita2d_free_texture(map.pGhostU);

    vita2d_free_texture(map.rGhostD);
    vita2d_free_texture(map.rGhostL);
    vita2d_free_texture(map.rGhostR);
    vita2d_free_texture(map.rGhostU);

    vita2d_free_texture(redHeart);
    vita2d_free_texture(grayHeart);
    
    screen.EndScreen(score);
}
/*
void MovePacman(int xStep, int yStep, Map& map)
{
  switch (map.GetYX(map.pacmanPos.y + yStep, map.pacmanPos.x + xStep))
  {
    case 'w': break;
    case 'p':
      --totalPellets;
      ++score;
      map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');

      if(yStep > 0)
      {
        map.pacmanPos.y = map.pacmanPos.y + yStep;
        map.pacmanPos.rotation = 4;
      }
      else if(yStep < 0)
      {
        map.pacmanPos.y = map.pacmanPos.y + yStep;
        map.pacmanPos.rotation = 3;
      }
      else if(xStep > 0)
      {
        map.pacmanPos.x = map.pacmanPos.x + xStep;
        map.pacmanPos.rotation = 1;
      }
      else if(xStep < 0)
      {
        map.pacmanPos.x = map.pacmanPos.x + xStep;
        map.pacmanPos.rotation = 2;
      }

      map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
      break;
    case 's': //Special pellet
      --totalPellets;
      ++score;
      map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');

      if(yStep > 0)
      {
        map.pacmanPos.y = map.pacmanPos.y + yStep;
        map.pacmanPos.rotation = 4;
      }
      else if(yStep < 0)
      {
        map.pacmanPos.y = map.pacmanPos.y + yStep;
        map.pacmanPos.rotation = 3;
      }
      else if(xStep > 0)
      {
        map.pacmanPos.x = map.pacmanPos.x + xStep;
        map.pacmanPos.rotation = 1;
      }
      else if(xStep < 0)
      {
        map.pacmanPos.x = map.pacmanPos.x + xStep;
        map.pacmanPos.rotation = 2;
      }
      map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
      break;
    case 'e':
      map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'e');

      if(yStep > 0)
      {
        map.pacmanPos.y = map.pacmanPos.y + yStep;
        map.pacmanPos.rotation = 4;
      }
      else if(yStep < 0)
      {
        map.pacmanPos.y = map.pacmanPos.y + yStep;
        map.pacmanPos.rotation = 3;
      }
      else if(xStep > 0)
      {
        map.pacmanPos.x = map.pacmanPos.x + xStep;
        map.pacmanPos.rotation = 1;
      }
      else if(xStep < 0)
      {
        map.pacmanPos.x = map.pacmanPos.x + xStep;
        map.pacmanPos.rotation = 2;
      }

      map.SetYX(map.pacmanPos.y, map.pacmanPos.x, 'Y');
      break;
    default: break;
  }
}
*/
