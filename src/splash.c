/* splash.c — exibe a splash AMX-1 em Screen 5 */
#include "msxgl.h"
#include "assets/gen/splash.h"   /* ajuste o caminho ao layout final */

#define SPLASH_WIDTH        256u
#define SPLASH_HEIGHT       212u
#define SPLASH_WAIT_FRAMES  180u   /* ~3 s a 60 Hz */

void Splash_Show(void)
{
    u16 i;

    VDP_EnableDisplay(FALSE);
    VDP_SetMode(VDP_MODE_SCREEN5);
    VDP_SetLineCount(VDP_LINE_212);
    VDP_SetPalette(g_Splash_palette);
    VDP_CommandHMMC(g_Splash, 0, 0, SPLASH_WIDTH, SPLASH_HEIGHT);
    VDP_CommandWait();
    VDP_EnableDisplay(TRUE);

    for (i = 0; i < SPLASH_WAIT_FRAMES; ++i) {
        Halt();
        if (Keyboard_IsKeyPressed(KEY_RETURN)) {
            break;
        }
    }
}