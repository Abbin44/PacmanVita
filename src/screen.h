#include <cstring>

#include <psp2/ctrl.h>
#include <vita2d.h>

class Screen
{
public:
  int screenWidth = 944;
  int screenHeight = 544;

  void StartScreen()
  {
      vita2d_init();
      vita2d_pgf *pgf;

      pgf = vita2d_load_default_pgf();

      SceCtrlData ctrl;
      memset(&ctrl, 0, sizeof(ctrl));

      while(1)
      {
        sceCtrlPeekBufferPositive(0, &ctrl, 1);

        if (ctrl.buttons & SCE_CTRL_START)
            break;
        else if(ctrl.buttons & SCE_CTRL_SELECT)
            sceKernelExitProcess(0);

        vita2d_start_drawing();
        vita2d_clear_screen();

        vita2d_pgf_draw_text(pgf, screenWidth / 3 + 15, screenHeight / 2 - 10, RGBA8(255,255,255,255), 1.0f, "PRESS START TO PLAY!");
    		vita2d_pgf_draw_text(pgf, screenWidth / 3 + 15, screenHeight / 2 + 10, RGBA8(255,255,255,255), 1.0f, "PRESS SELECT TO EXIT!");


        vita2d_end_drawing();
        vita2d_swap_buffers();
      }
      vita2d_fini();
      vita2d_free_pgf(pgf);
  }
};
