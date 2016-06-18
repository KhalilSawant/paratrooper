#include "Turret.h"
#include "common.h"
#include <math.h>
#include <graphics.h>

const unsigned int Turret::PlatformHeight = 40;
const unsigned int Turret::PlatformWidth = 40;
const unsigned int Turret::LeftEdge = X_MAX/2 - PlatformWidth/2;
const unsigned int Turret::RightEdge = X_MAX/2 + PlatformWidth/2;

const unsigned int Turret::BrickLayers = 8;
const unsigned int Turret::BricksPerLayer = 4;
const unsigned int Turret::BrickHeight = PlatformHeight/BrickLayers;
const unsigned int Turret::BrickWidth = PlatformWidth/BricksPerLayer;

const unsigned int Turret::MinAngle = 180;
const unsigned int Turret::MaxAngle = 360;
const unsigned int Turret::AngleIncrement = 15;
const unsigned int Turret::Length = 30;
const unsigned int Turret::Girth = 15;

Turret::Turret() {
	pivot_x = X_MAX/2;
	pivot_y = Y_MAX-PlatformHeight;
	
	angle = (MaxAngle+MinAngle)/2;
	drawPlatform();
	draw();
}

unsigned int Turret::getAngle() { return angle; }

void Turret::getTip(unsigned int& x, unsigned int& y) {
	x = (unsigned int)( pivot_x + Length*cos(rad(angle)) );
	y = (unsigned int)( pivot_y + Length*sin(rad(angle)) );
}

void Turret::moveRight() {
	if (angle <= MaxAngle - AngleIncrement) {
		erase();
		angle += AngleIncrement;
		draw();
	}
}

void Turret::moveLeft() {
	if (angle >= MinAngle + AngleIncrement) {
		erase();
		angle -= AngleIncrement;
		draw();
	}
}

void Turret::draw() {
	setcolor(WHITE);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	line(
			pivot_x,
			pivot_y,
			(int)( pivot_x + Length*cos(rad(angle)) ),
			(int)( pivot_y + Length*sin(rad(angle)) )
		);
	setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
	arc(pivot_x, pivot_y, (int)rad(MinAngle), (int)rad(MaxAngle), Girth);

	setfillstyle(1, DARKGRAY);
	bar(
		LeftEdge,
		pivot_y,
		RightEdge,
		pivot_y + BrickHeight);

	setcolor(LIGHTGRAY);
	line(LeftEdge, pivot_y, RightEdge, pivot_y);
	for (int j = 0; j < BricksPerLayer-1; j++) {
		line(
			LeftEdge + (j+1)*BrickWidth,
			pivot_y,
			LeftEdge + (j+1)*BrickWidth,
			pivot_y + BrickHeight);
	}
	line(LeftEdge, pivot_y, LeftEdge, Y_MAX);
	line(RightEdge, pivot_y, RightEdge, Y_MAX);
}
		
void Turret::erase() {
	setcolor(BLACK);
	setlinestyle(0,0,3);
	line(
		pivot_x,
		pivot_y,
		(int)( pivot_x + Length*cos(rad(angle)) ),
		(int)( pivot_y + Length*sin(rad(angle)) )
	);
}

void Turret::drawPlatform() {
	setfillstyle(1,0);
	fillellipse(X_MAX/2, Y_MAX-Turret::PlatformHeight, Girth, Girth);

	setfillstyle(1, DARKGRAY);
	bar(
		LeftEdge,
		pivot_y,
		RightEdge,
		Y_MAX-1);

	setcolor(LIGHTGRAY);
	
	for (int i = 0; i < BrickLayers; i++) {
		line(
			LeftEdge,
			pivot_y + i*BrickHeight,
			RightEdge,
			pivot_y + i*BrickHeight);
		for (int j = 0; j < ((0 == i%2) ? BricksPerLayer-1:BricksPerLayer); j++) {
			line(
				LeftEdge + (j+1)*BrickWidth - ((0 == i%2)?0:BrickWidth/2),
				pivot_y + i*BrickHeight,
				LeftEdge + (j+1)*BrickWidth - ((0 == i%2)?0:BrickWidth/2),
				pivot_y + (i+1)*BrickHeight);
		}
	}
	line(LeftEdge, pivot_y, LeftEdge, Y_MAX);
	line(RightEdge, pivot_y, RightEdge, Y_MAX);
}

void Turret::bigblast() {

	setcolor(BLACK);
	setfillstyle(1,BLACK);
	floodfill(X_MAX/2, Y_MAX-Turret::PlatformHeight/2, BLACK);

	setlinestyle(0,0,1);
	arc(pivot_x, pivot_y, (int)rad(MinAngle), (int)rad(MaxAngle), Girth);
	rectangle(LeftEdge, 240, RightEdge, Y_MAX-1);

}
