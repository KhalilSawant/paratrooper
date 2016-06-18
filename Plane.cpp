#include "Plane.h"
#include <graphics.h>
#include "common.h"
#include "Paratrooper.h"

const unsigned int Plane::PlaneHeight;
const unsigned int Plane::PlaneLength;

const unsigned int Plane::FlyHeightLeftPlane = 50;
const unsigned int Plane::FlyHeightRightPlane = 100;

const unsigned int Plane::PlaneStartOffMargin = 10;
const unsigned int Plane::InterPlaneGap = 150;

const unsigned int Plane::Advancement = 5;

Plane* Plane::head = NULL;
Plane* Plane::tail = NULL;

unsigned int Plane::planeBitMap[PlaneHeight][PlaneLength] = {
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

char* Plane::leftPlaneBufferedImage;
char* Plane::rightPlaneBufferedImage;

extern unsigned int score;

void Plane::initialize() {
	unsigned arbit_x = 50;
	unsigned arbit_y = 50;
	
	for (int i = 0; i < PlaneHeight; i++)
		for (int j = 0; j < PlaneLength; j++)
			putpixel(arbit_x + j, arbit_y + i, LIGHTGRAY*Plane::planeBitMap[i][j]);
			
	leftPlaneBufferedImage = new char[GETIMAGE_METADATA_SIZE + GETIMAGE_BYTES_PER_PIXEL*PlaneLength*PlaneHeight];
	getimage(arbit_x, arbit_y, arbit_x + PlaneLength -1, arbit_y + PlaneHeight - 1, leftPlaneBufferedImage);
	cleardevice();

	for (int i = 0; i < PlaneHeight; i++)
		for (int j = 0; j < PlaneLength; j++)
			putpixel(arbit_x + j, arbit_y + i, LIGHTGRAY*Plane::planeBitMap[i][PlaneLength-1-j]);

	rightPlaneBufferedImage = new char[GETIMAGE_METADATA_SIZE + GETIMAGE_BYTES_PER_PIXEL*PlaneLength*PlaneHeight];
	getimage(arbit_x, arbit_y, arbit_x + PlaneLength -1, arbit_y + PlaneHeight - 1, rightPlaneBufferedImage);
	cleardevice();
}

Plane::Plane(bool fromRight) {
	this->fromRight = fromRight;
	this->next = NULL;
	if (fromRight) {
		y = FlyHeightRightPlane;
		x = X_MAX - PlaneStartOffMargin - PlaneLength;
	} else {
		y = FlyHeightLeftPlane;
		x = X_MIN + PlaneStartOffMargin;
	}
}

void Plane::create(bool fromRight) {

	if (NULL == tail) {
		tail = new Plane(fromRight);
		head = tail;
		tail->xorDraw();
	} else {
		if (
			(!tail->fromRight && tail->x >= X_MIN + PlaneStartOffMargin + InterPlaneGap) ||
			(tail->fromRight && tail->x <= X_MAX - PlaneStartOffMargin - PlaneLength - InterPlaneGap)
		) {
			tail->next = new Plane(fromRight);
			tail = tail->next;
			tail->xorDraw();
		}
	}
}

void Plane::advance() {

	Plane* tmpPl = head;
	
	while (NULL != tmpPl) {
		if (!tmpPl->fromRight) {
			tmpPl->xorDraw();
			if ( !tmpPl->isHit() ) {
				if (tmpPl->x < X_MAX - PlaneStartOffMargin  - PlaneLength) {
					tmpPl->x += Advancement;
					tmpPl->xorDraw();

					if ( rand() % 5000 < 15)
						Paratrooper::create(tmpPl->x, tmpPl->y);

					tmpPl = tmpPl->next;
				} else {
					remove(&tmpPl);
				}
			} else {
				tmpPl->explode();
				remove(&tmpPl);
			}
		} else {
			tmpPl->xorDraw();
			if ( !tmpPl->isHit() ) {
				if (tmpPl->x > X_MIN + PlaneStartOffMargin) {
					tmpPl->x -= Advancement;
					tmpPl->xorDraw();

					if ( rand() % 5000 < 15)
						Paratrooper::create(tmpPl->x, tmpPl->y);

					tmpPl = tmpPl->next;
				} else {
					remove(&tmpPl);
				}
			} else {
				tmpPl->explode();
				remove(&tmpPl);
			}
		}
		
	
	}
}

void Plane::xorDraw() {
	if (fromRight)
		putimage(x, y, rightPlaneBufferedImage, XOR_PUT);
	else
		putimage(x, y, leftPlaneBufferedImage, XOR_PUT);	
}

bool Plane::isHit() {
	for (int j = 0; j < PlaneHeight; j++)
		for (int i = 0; i < PlaneLength; i++)
			if ( WHITE == getpixel(x+i, y+j) ) {
				score += 10;
				redrawScore();
				return true;
			}
	return false;
}


void Plane::remove(Plane** tmpPl) {
	if (head == *tmpPl) {
		// Delete the first plane
		head = head->next;
		if (tail == *tmpPl) tail = NULL;
		delete *tmpPl;
		*tmpPl = head;
	} else {
		Plane* tmpB4Pl = head;
		while (*tmpPl != tmpB4Pl->next) tmpB4Pl = tmpB4Pl->next;
		tmpB4Pl->next = (*tmpPl)->next;
		if (tail == *tmpPl) tail = tmpB4Pl;
		delete *tmpPl;
		*tmpPl = tmpB4Pl->next;
	}
}

void Plane::explode() {
	int oldColor = getcolor();
	setcolor(YELLOW);
	xorDraw();
	setcolor(RED);
	xorDraw();
	setcolor(LIGHTBLUE);
	xorDraw();
	delay(100);
	setcolor(LIGHTBLUE);
	xorDraw();
	setcolor(RED);
	xorDraw();
	setcolor(YELLOW);
	xorDraw();
	setcolor(oldColor);	
}
