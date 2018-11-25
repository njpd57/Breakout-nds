#include "Sprite.h"

sprite::sprite(int snum)
{
	spritenum=snum;
	Mosaic=false;
	Vflip=false;
	Hflip=false;
	Hide=false;
	DoubleSize=false;	
};


void sprite::SizeAndFormat(SpriteSize size,SpriteColorFormat color)
{
	spriteSize=size;
	spriteColor=color;
};

void sprite::setTiles(const void* tiles,uint32 size,int palette)
{
	spriteTiles=tiles;
	TileSize=size;
	paletteNum=palette;
};
void sprite::setXY(int sx,int sy)
{
	x=sx;
	y=sy;
};
void sprite::loadGfx(bool onMain,int size)
{
	switch(onMain)
	{
		case true:
			Main=true;
			gfx=oamAllocateGfx(&oamMain,spriteSize,spriteColor);
			for(int i=0; i < size * size /2;i++)
			{
				gfx[i]=1| (1<<8);
			};
			dmaCopyHalfWords(0,spriteTiles,gfx,TileSize);
			break;

		case false:
			Main=false;
			gfx=oamAllocateGfx(&oamSub,spriteSize,spriteColor);
			for(int i=0; i < size * size /2;i++)
			{
				gfx[i]=1| (1<<8);
			};
			dmaCopyHalfWords(0,spriteTiles,gfx,TileSize);
			break;
	}
};

void sprite::setPalette(const void* palete,uint32 palsize)
{
	spritePal=palete;
	PalSize=palsize;

    switch(paletteNum)
        {
        case 0:
            dmaCopy(spritePal,SPRITE_PALETTE,PalSize);
            break;
        case 1:
            dmaCopy(spritePal,SPRITE_PALETTE+16,PalSize);
            break;
        case 2:
            dmaCopy(spritePal,SPRITE_PALETTE+32,PalSize);
            break;
        case 3:
            dmaCopy(spritePal,SPRITE_PALETTE+48,PalSize);
            break;
        case 4:
            dmaCopy(spritePal,SPRITE_PALETTE+64,PalSize);
            break;
        case 5:
            dmaCopy(spritePal,SPRITE_PALETTE+80,PalSize);
            break;
        case 6:
            dmaCopy(spritePal,SPRITE_PALETTE+96,PalSize);
            break;
        case 7:
            dmaCopy(spritePal,SPRITE_PALETTE+112,PalSize);
            break;
        case 8:
            dmaCopy(spritePal,SPRITE_PALETTE+128,PalSize);
            break;
        case 9:
            dmaCopy(spritePal,SPRITE_PALETTE+144,PalSize);
            break;
        case 10:
            dmaCopy(spritePal,SPRITE_PALETTE+160,PalSize);
            break;
        case 11:
            dmaCopy(spritePal,SPRITE_PALETTE+176,PalSize);
            break;
        case 12:
            dmaCopy(spritePal,SPRITE_PALETTE+192,PalSize);
            break;
        case 13:
            dmaCopy(spritePal,SPRITE_PALETTE+208,PalSize);

	};
};

void sprite::Update()
{
	switch (Main)
	{
		case true:
			oamSet(&oamMain,spritenum,x,y,0,paletteNum,spriteSize,spriteColor,gfx,-1,DoubleSize,Hide,Hflip,Vflip,Mosaic);
			break;
		case false:
			oamSet(&oamSub,spritenum,x,y,0,paletteNum,spriteSize,spriteColor,gfx,-1,DoubleSize,Hide,Hflip,Vflip,Mosaic);
			break;
	}
};
void sprite::setMosaic(bool mosaic)
{
	Mosaic = mosaic;
};
void sprite::VerticalFlip(bool vflip)
{
	Vflip = vflip;
};
void sprite::HorizontalFlip(bool hflip)
{
	Hflip=hflip;
};
void sprite::setHide(bool SHW)
{
	Hide=SHW;
};
