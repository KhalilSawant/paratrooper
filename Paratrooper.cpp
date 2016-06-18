#include "Paratrooper.h"
#include <graphics.h>
#include "common.h"
#include "Turret.h"

const unsigned int Paratrooper::SoldierHeight;
const unsigned int Paratrooper::SoldierWidth;
const unsigned int Paratrooper::TrooperHeight;
const unsigned int Paratrooper::TrooperWidth;

const unsigned int Paratrooper::OffTurretMargin = 20;
const unsigned int Paratrooper::Advancement = 5;

Paratrooper* Paratrooper::head = NULL;
Paratrooper* Paratrooper::tail = NULL;

unsigned int Paratrooper::soldierBitMap[SoldierHeight][SoldierWidth] = {
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,1,0,0,1,0,0,0},
	{0,0,1,0,1,1,0,1,0,0},
	{0,0,1,0,0,0,0,1,0,0},
	{0,0,1,0,0,0,0,1,0,0},
	{0,0,0,1,1,1,1,0,0,0},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,1,1,1,1,0,0,0},
	{0,0,1,1,1,1,1,1,0,0},
	{0,1,1,0,1,1,0,1,1,0},
	{1,1,0,0,1,1,0,0,1,1},
	{0,0,0,0,1,1,0,0,0,0},
	{0,0,0,1,1,1,1,0,0,0},
	{0,0,0,1,1,1,1,0,0,0},
	{0,0,0,1,0,0,1,0,0,0},
	{0,0,0,1,0,0,1,0,0,0},
	{0,0,0,1,0,0,1,0,0,0},
	{0,0,0,1,0,0,1,0,0,0},
	{0,0,0,1,0,0,1,0,0,0},
	{0,0,1,1,0,0,1,1,0,0},
};
			
unsigned int Paratrooper::trooperBitMap[TrooperHeight][TrooperWidth] =	{
	{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
	{0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0},
	{0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0},
	{0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0},
	{0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0},
	{0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0},
	{0,0,1,1,0,0,0,0,0,0,0,0,1,1,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0},
	{0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0},
	{0,0,0,0,1,0,0,1,1,0,0,1,0,0,0,0},
	{0,0,0,0,1,0,1,0,0,1,0,1,0,0,0,0},
	{0,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0},
	{0,0,0,0,1,1,0,1,1,0,1,1,0,0,0,0},
	{0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0},
	{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0},
	{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}
};

char* Paratrooper::soldierBufferedImage;
char* Paratrooper::trooperBufferedImage;

extern unsigned int soldiersOnGround;
extern unsigned int score;

void Paratrooper::initialize() {
	unsigned arbit_x = 50;
	unsigned arbit_y = 50;

	for (int i = 0; i < SoldierHeight; i++)
		for (int j = 0; j < SoldierWidth; j++)
			putpixel(arbit_x + j, arbit_y + i, YELLOW*soldierBitMap[i][j]);

	soldierBufferedImage = new char[GETIMAGE_METADATA_SIZE + GETIMAGE_BYTES_PER_PIXEL*SoldierWidth*SoldierHeight];
	getimage(arbit_x, arbit_y, arbit_x + SoldierWidth -1, arbit_y + SoldierHeight - 1, soldierBufferedImage);
	cleardevice();
	
	for (int i = 0; i < TrooperHeight; i++)
		for (int j = 0; j < TrooperWidth; j++)
			putpixel(arbit_x + j, arbit_y + i, YELLOW*trooperBitMap[i][j]);
		
	trooperBufferedImage = new char[GETIMAGE_METADATA_SIZE + GETIMAGE_BYTES_PER_PIXEL*TrooperWidth*TrooperHeight];
	getimage(arbit_x, arbit_y, arbit_x + TrooperWidth -1, arbit_y + TrooperHeight - 1, trooperBufferedImage);
	cleardevice();
}

Paratrooper::Paratrooper(int x0, int y0) {
	x = x0;
	y = y0;
	next = NULL;
}

void Paratrooper::create(int x0, int y0) {
	if (
		x0 < ( Turret::LeftEdge - OffTurretMargin) ||
		x0 > ( Turret::RightEdge + OffTurretMargin)
	) {
		if (NULL == tail) {
			tail = new Paratrooper(x0, y0);
			head = tail;
		} else {
			tail->next = new Paratrooper(x0, y0);
			tail = tail->next;
		}
		tail->xorDraw();
	}
}

void Paratrooper::advance() {

	Paratrooper* tmpPara = head;
	
	while (NULL != tmpPara) {
		tmpPara->xorDraw();
		delay(8);
		if ( !tmpPara->isHit() ) {
				tmpPara->y += Advancement;
			if (tmpPara->y + Advancement <= Y_MAX - TrooperHeight) {
				tmpPara->xorDraw();
				tmpPara = tmpPara->next;
			} else {
				tmpPara->y = Y_MAX - SoldierHeight;
				soldiersOnGround++;
				putimage(tmpPara->x, tmpPara->y, soldierBufferedImage, COPY_PUT);
				// Delete the trooper
				remove(&tmpPara);
			}
		} else {
			remove(&tmpPara);
		}		
	}
}

void Paratrooper::xorDraw() {
	putimage(x, y, trooperBufferedImage, XOR_PUT);
}
		
bool Paratrooper::isHit() {
	for (int j = 0; j < TrooperHeight; j++)
		for (int i = 0; i < TrooperWidth; i++)
			if ( WHITE == getpixel(x+i, y+j) ) {
				score += 10;
				redrawScore();
				return true;
			}
	return false;
}

void Paratrooper::remove(Paratrooper** tmpPara) {
	if (head == *tmpPara) {
		// Delete the first trooper
		head = head->next;
		if (tail == *tmpPara) tail = NULL;
		delete *tmpPara;
		*tmpPara = head;
	} else {
		Paratrooper* tmpB4Para = head;
		while (*tmpPara != tmpB4Para->next) tmpB4Para = tmpB4Para->next;
		tmpB4Para->next = (*tmpPara)->next;
		if (tail == *tmpPara) tail = tmpB4Para;
		delete *tmpPara;
		*tmpPara = tmpB4Para->next;
	}
}
