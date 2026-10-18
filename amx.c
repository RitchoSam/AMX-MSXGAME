//-----------------------------------------------------------------------------
// amx.c — Protótipo: robô + loop principal sincronizado por VBlank
// MSXgl v1.2.4 — alvo: MSX2+ (Machine = "2P")
//-----------------------------------------------------------------------------

#include "msxgl.h"

// Padrão do robô 16x16 (Sprite Mode 2 = 4 células: esq/dir × topo/base)
const u8 g_RobotPattern[32] = {
	// Célula 0 — metade esquerda, linhas 0-7 (cabeça)
	0x03, 0x07, 0x07, 0x06, 0x07, 0x01, 0x1F, 0x1F,
	// Célula 1 — metade direita, linhas 0-7
	0xC0, 0xE0, 0xE0, 0x60, 0xE0, 0x80, 0xF8, 0xF8,
	// Célula 2 — metade esquerda, linhas 8-15 (corpo e pernas)
	0x3F, 0x37, 0x37, 0x1F, 0x0C, 0x0C, 0x1C, 0x1C,
	// Célula 3 — metade direita, linhas 8-15
	0xFC, 0xCC, 0xCC, 0xF8, 0x30, 0x30, 0x38, 0x38,
};

// Estado do robô
u8 g_RobotX = 120;
u8 g_RobotY = 100;

void main(void)
{
	// --- Setup do vídeo ---
	VDP_SetMode(VDP_MODE_GRAPHIC4);         // SCREEN 5: 256x212, 16 cores
	VDP_ClearVRAM();                        // VRAM zerada → tela toda na cor 0
	VDP_SetPaletteEntry(0, RGB16(0, 0, 4)); // cor 0 = azul escuro (céu)

	// --- Setup do robô ---
	VDP_SetSpriteFlag(VDP_SPRITE_SIZE_16);                   // sprites 16x16
	VDP_LoadSpritePattern(g_RobotPattern, 0, 4);             // padrão 0 (4 células)
	VDP_SetSpriteExUniColor(0, g_RobotX, g_RobotY, 0, 0x0F); // sprite 0, branco

	// --- Sincronismo: habilita a interrupção de VBlank ---
	VDP_EnableVBlank(TRUE);

	// --- Loop principal: 1 iteração = 1 frame ---
	while(TRUE)
	{
		Halt();  // dorme até o próximo VBlank (instrução HALT do Z80)

		// Entrada (teclado)
		if(Keyboard_IsKeyPressed(KEY_RIGHT) && (g_RobotX < 240)) g_RobotX++;
		if(Keyboard_IsKeyPressed(KEY_LEFT)  && (g_RobotX > 0))   g_RobotX--;
		if(Keyboard_IsKeyPressed(KEY_DOWN)  && (g_RobotY < 196)) g_RobotY++;
		if(Keyboard_IsKeyPressed(KEY_UP)    && (g_RobotY > 0))   g_RobotY--;

		// Atualiza a posição do sprite na tela
		VDP_SetSpritePosition(0, g_RobotX, g_RobotY);
	}
}