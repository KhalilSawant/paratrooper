#include <graphics.h>
#include <conio.h>
#include <math.h>

#include "common.h"
#include "Paratrooper.h"
#include "Turret.h"
#include "Plane.h"
#include "Bullet.h"

extern unsigned int score;
extern unsigned int soldiersOnGround;

unsigned int WaitTimeBeforeStartingPlane = 20;
unsigned int WaitTimeBeforeBigBlast = 1000;
unsigned int WaitTimeAfterBigBlast = 3000;

unsigned int Base4Random4Plane = 100;
unsigned int Base4Random4PlaneDirection = 2000;

unsigned int Value4Random4Plane = 5;
unsigned int Value4Random4PlaneDirection = 1000;

unsigned int getKey() {
	fflush(stdin);
	while ( !kbhit() )
		;
	return getch();
}

void pause() {
	unsigned int key = getKey();
	while (key != KEY_INSERT)
		key = getKey();
}

void bigblast(Turret* t);
int isCheatCode();

int main() {

	srand(time(NULL));
	
	int cheat = 0;
//	cheat = isCheatCode();

	int gd = DETECT;
	int gm;
	initgraph(&gd, &gm, "");

	Paratrooper::initialize();
	Plane::initialize();
	closegraph();
	
	initgraph(&gd, &gm, "");

	rectangle(X_MIN, Y_MIN, X_MAX, Y_MAX);
	setbkcolor(LIGHTBLUE);
	line(X_MIN, HEADER_HEIGHT, X_MAX, HEADER_HEIGHT);
	setfillstyle(1, LIGHTGRAY);
	bar(X_MIN+1,Y_MIN+1,X_MAX-1,HEADER_HEIGHT-1);
	write(X_MAX/2, HEADER_HEIGHT/2, "PARATROOPER");
	
	Turret t;
	
	int key = getKey();
	
	while (key != 27) {

		switch(key) {

			case KEY_LEFT:
				t.moveLeft();
				break;
			case KEY_RIGHT:
				t.moveRight();
				break;
			case KEY_UP:
				{
					unsigned int x, y;
					t.getTip(x,y);
					Bullet::create( x, y, t.getAngle() );
					score--;
					redrawScore();
					printf("\a");
				}
				break;
			case KEY_DOWN:
				pause();
				break;
		}
		
		while ( true )
		{
			fflush(stdin);
			
			Plane::advance();
			Paratrooper::advance();
			Bullet::advance();

			delay(WaitTimeBeforeStartingPlane);
			
			if ( (rand() % Base4Random4Plane) < Value4Random4Plane) {
				if ( (rand() % Base4Random4PlaneDirection) < Value4Random4PlaneDirection) {
					Plane::create(false);
				} else {
					Plane::create(true);
				}
			}			
			
			if ( (4+cheat*4) == soldiersOnGround)
				bigblast(&t);
				
			if ( kbhit() ) {
				key = getch();
				break;
			}
		}
	}
}

void bigblast(Turret* t)
{
	delay(WaitTimeBeforeBigBlast);

	t->bigblast();

	int x = X_MAX/2;
	int y = 478;
	int k = 0;
	int count = 0;
	for (int i = 0; i < 100; i += 10)
	{
		k++;
		for (int j = 180; j < 360; j += 10)
		{
			if ( (count%2) == 0)
			{
				setcolor(YELLOW);
				circle((int)(x + i* cos(rad(j))), (int)(y + i* sin(rad(j))), k);
				setfillstyle(6, YELLOW);
				floodfill((int)(x + i* cos(rad(j))), (int)(y + i* sin(rad(j))), YELLOW);
				printf("\a");
				delay(75);
			}
			else
			{
				setcolor(RED);
				circle((int)(x + i* cos(rad(j))), (int)(y + i* sin(rad(j))), k);
				setfillstyle(6, RED);
				circle((int)(x + i* cos(rad(j))), (int)(y + i* sin(rad(j))), RED);
				printf("\a");				
			}
			count++;
		}
	}
	delay(WaitTimeAfterBigBlast);
	cleardevice();
	setbkcolor(BLACK);
	setcolor(LIGHTBLUE);
	settextstyle(3,0,9);
	write(X_MAX/2,Y_MAX/2, "GAME OVER");
	getch();
	exit(0);
}

int isCheatCode() {
	char code[80];
	for (int i = 0; i < 80; i++) code[i] = 0;
	
	printf("Enter the cheat code :");
	int m = -1;
	while (code[m] != '\r')
	{
		code[++m] = getch();
		if ( code[m] == 8)
		{
			if ( m != 0)
			{
				putch(8);
				putch(32);
				putch(8);
				code[m] = 0;
				m = m - 2;				
			}
			else
				m--;
		}
		else putch('*');
	}
	code[m] = 0;
	
	if ( !strcmp(code, "pioneer") )
		return 1;
	else
		return 0;
}
