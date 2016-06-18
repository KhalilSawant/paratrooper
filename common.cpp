#include <graphics.h>
#include "common.h"

unsigned int soldiersOnGround = 0;
int score = 0;

float rad(unsigned int angle) {
	return (angle*PI/180);
}

void write(int x, int y, char* str) {
	outtextxy(x-textwidth(str)/2, y - textheight(str)/2, str);
}

void redrawScore() {
	setfillstyle(1, LIGHTGRAY);
	bar(X_MAX-60, 1, X_MAX-1, 19);
	char str[10];
	itoa(score, str, 10);
	write(X_MAX-15, 10, str);
}
