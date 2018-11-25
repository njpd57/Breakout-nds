#include <nds.h>

#include "Input.h"


#define PAD_SPEED 2

void Input()
{
	CurrentK=keysCurrent();

	//DPAD
	if(CurrentK&KEY_LEFT)Sx+=PAD_SPEED;
	if(CurrentK&KEY_RIGHT)Sx-=PAD_SPEED;
	if(CurrentK&KEY_UP);
	if(CurrentK&KEY_DOWN);

	//Buttons
	if(CurrentK&KEY_X);
	if(CurrentK&KEY_Y);
	if(CurrentK&KEY_A);
	if(CurrentK&KEY_B);

	//Triggers
	if(CurrentK&KEY_L);
	if(CurrentK&KEY_R);

	//Menu
	if(CurrentK&KEY_START);
	if(CurrentK&KEY_SELECT);



};

int ReturnSX()
{
	return Sx;
};
int ReturnSY()
{
	return Sy;
};
