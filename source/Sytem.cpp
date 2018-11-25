#include <nds.h>
#include "System.h"

void LoadRam()
{
	vramSetBankA(VRAM_A_MAIN_SPRITE);
	vramSetBankB(VRAM_B_MAIN_BG);
	vramSetBankC(VRAM_C_SUB_BG);
	vramSetBankD(VRAM_D_SUB_SPRITE);
}
void LoadVideo()
{
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D);
}
void LoadOam()
{
	oamInit(&oamMain,SpriteMapping_1D_32,false);	
	oamInit(&oamSub,SpriteMapping_1D_32,false);	
}

void LoadBg(int layer, BgType type,BgSize bgsize, int mapBase, int tileBase,bool main,const void* source,void* dest,uint32 Tilesize,const void*sourcePal,uint32 PalSize)
{
    if(main)
    {
        int LOADBG=bgInit(layer,type,bgsize,mapBase,tileBase);
        dmaCopy(source,dest,Tilesize);
        dmaCopy(sourcePal,BG_PALETTE,PalSize);
    }
    if(!main)
    {
        int LOADBG=bgInitSub(layer,type,bgsize,mapBase,tileBase);
        dmaCopy(source,dest,Tilesize);
        dmaCopy(sourcePal,BG_PALETTE_SUB,PalSize);
    }
}

void LoadMap(
            int LOADMAP,
            int layer, BgType type,BgSize bgsize, int mapBase, int tileBase, //BGINIT
            bool main,
            const void* sourceTiles,uint32 sourceTilesLen,
            const void* sourcePal,uint32 sourcePalLen,
            const void* sourceMap,uint32 sourceMapLen)
{
    if(main)
    {
        LOADMAP=bgInit(layer,type,bgsize,mapBase,tileBase);
        dmaCopy(sourceTiles,bgGetGfxPtr(LOADMAP),sourceTilesLen);
        dmaCopy(sourceMap,bgGetMapPtr(LOADMAP),sourceMapLen);
        dmaCopy(sourcePal,BG_PALETTE,sourcePalLen);
    }
    if(!main)
    {
        LOADMAP=bgInitSub(layer,type,bgsize,mapBase,tileBase);
        dmaCopy(sourceTiles,bgGetGfxPtr(LOADMAP),sourceTilesLen);
        dmaCopy(sourceMap,bgGetMapPtr(LOADMAP),sourceMapLen);
        dmaCopy(sourcePal,BG_PALETTE_SUB,sourcePalLen);
    }
}

void SystemLoop()
{
	oamUpdate(&oamMain);
	oamUpdate(&oamSub);
	bgUpdate();
	scanKeys();
	swiWaitForVBlank();
}
