#include <nds.h>
#include <stdio.h>
#include "System.h"
#include "Sprite.h"


//NDSDEFINES

#define SCREEN_RIGHT 256
#define SCREEN_LEFT 0
#define SCREEN_BOTTOM 192
#define SCREEN_TOP 0
//GAMEASSETS

#include "Pad.h"
#include "simpleBlocks.h"
#include "specialBlocks.h"
#include "SpecialPad.h"
#include "Ball.h"

//BREAKOUTDEFINES
#define PAD_WIDTH 64
#define PAD_HEIGHT 16
#define PAD_SPEED 3

//Sprites
sprite Player(1);
sprite Ball(2);

void LoadPlayer();
void LoadBall();
void Input();
void BallLogic(bool held);

//Ball
bool BallHeld=true;
bool collideLeft=false;
bool collideRight=false;
bool collideTop=false;
bool collideDown=false;
void collideLogic();
int BALL_SPEED_X=0;
int BALL_SPEED_Y=3;


int x=128-PAD_WIDTH/2;
int y=170;
int bx=x+32-4;
int by=y-9;
int key;
int main(void) {
	LoadRam();
	LoadVideo();
	LoadOam();
	LoadPlayer();
	LoadBall();
	

	while(1) {
		BallLogic(BallHeld);
		Input();
		Player.setXY(x,y);
		Player.Update();
		Ball.Update();
		SystemLoop();
	}

}

void LoadPlayer()
{
	Player.SizeAndFormat(SpriteSize_64x32,SpriteColorFormat_16Color);
	Player.setTiles(PadTiles,PadTilesLen,0);
	Player.setPalette(PadPal,PadPalLen);
	Player.setXY(10,10);
	Player.loadGfx(true,46);
};
void LoadBall()
{
	Ball.SizeAndFormat(SpriteSize_8x8,SpriteColorFormat_16Color);
	Ball.setTiles(BallTiles,BallTilesLen,2);
	Ball.setPalette(BallPal,BallPalLen);
	Ball.setXY(bx,by);
	Ball.loadGfx(true,8);
};
void BallLogic(bool held)
{
	switch(held)
	{
		case true:
			bx=x+32-4;
			by=y-9;
			Ball.setXY(bx,by);
			break;
		case false:
			collideLogic();
			by-=BALL_SPEED_Y;
			bx-=BALL_SPEED_X;
			Ball.setXY(bx,by);
			break;
	};
}

void Input()
{
		key=keysCurrent();
		if(key&KEY_LEFT)
		{
			if(x>=SCREEN_LEFT)x-=PAD_SPEED;
		}
		if(key&KEY_RIGHT)
		{
			if(x<=SCREEN_RIGHT-PAD_WIDTH)x+=PAD_SPEED;
		}
		if(key &KEY_A)
		{
			if(BallHeld)BallHeld=false;
		}
}
void collideLogic()
{
	//Screen Collision
	if(bx<=SCREEN_LEFT)BALL_SPEED_X=-BALL_SPEED_X;
	if(bx+8>=SCREEN_RIGHT)BALL_SPEED_X=-BALL_SPEED_X;
	if(by<=SCREEN_TOP)BALL_SPEED_Y=-BALL_SPEED_Y;
	if(by>=SCREEN_BOTTOM+10)BallHeld=true;

	//Pad Collision
	
	//LEFT PAD
	
	if( (bx+4>=x && bx<=x+17) && (by>=y-8 && by <= y+16-8))
	{
		BALL_SPEED_Y=-BALL_SPEED_Y;
		if(by>=y-8 && by<=y+4-8)BALL_SPEED_X=1;
		if(by>=y+4-8 && by<=y+12-8)BALL_SPEED_X=2;
		if(by>=y+12-8&&by<=y+16-8)
		{
			BALL_SPEED_Y=-BALL_SPEED_Y;
			BALL_SPEED_X=3;
		};
	}

	//CENTER
	if( (bx+4>=x+17 && bx<=x+47) && (by>=y-8))
	{
		BALL_SPEED_Y=-BALL_SPEED_Y;
	}

	//RIGHT
	if( (bx+4>=x+47 && bx<=x+64) && (by>=y-8 && by<=y+16-8))
	{
		BALL_SPEED_Y=-BALL_SPEED_Y;
		if(by>=y-8 && by<=y+4-8)BALL_SPEED_X=-1;
		if(by>=y+4-8 && by<=y+12-8)BALL_SPEED_X=-2;
		if(by>=y+12-8&&by<=y+16-8)
		{
			BALL_SPEED_Y=-BALL_SPEED_Y;
			BALL_SPEED_X=-3;
		}
	}
}
	
