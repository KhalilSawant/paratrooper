#include "Bullet.h"
#include "common.h"
#include <math.h>
#include <graphics.h>

const unsigned int Bullet::SideMargin = 5;
const unsigned int Bullet::UpMargin = 10;
const unsigned int Bullet::Advancement = 10;

Bullet* Bullet::head = NULL;
Bullet* Bullet::tail = NULL;

Bullet::Bullet(int x0, int y0, unsigned int angle) {
	x = x0;
	y = y0;
	this->x_Advancement = (int)(Advancement * cos(angle*PI/180));
	this->y_Advancement = (int)(Advancement * sin(angle*PI/180));
	next = NULL;
}

void Bullet::create(int x0, int y0, unsigned int angle) {
	if (NULL == tail) {
		tail = new Bullet(x0, y0, angle);
		head = tail;
	} else {
		tail->next = new Bullet(x0, y0, angle);
		tail = tail->next;
	}
}

void Bullet::advance() {

	Bullet* tmpBu = head;
	
	while (NULL != tmpBu) {
		tmpBu->erase();
		if (
			tmpBu->x > (X_MIN+SideMargin) &&
			tmpBu->x < (X_MAX-SideMargin) &&
			tmpBu->y > (HEADER_HEIGHT+UpMargin)
		) {
			tmpBu->x += tmpBu->x_Advancement;
			tmpBu->y += tmpBu->y_Advancement;
			tmpBu->draw();
			tmpBu = tmpBu->next;
		} else {
			// Delete the bullet
			if (head == tmpBu) {
				// Delete the first bullet
				head = head->next;
				if (tail == tmpBu) tail = NULL;
				delete tmpBu;
				tmpBu = head;
			} else {
				Bullet* tmpB4Bu = head;
				while (tmpBu != tmpB4Bu->next) tmpB4Bu = tmpB4Bu->next;
				tmpB4Bu->next = tmpBu->next;
				if (tail == tmpBu) tail = tmpB4Bu;
				delete tmpBu;
				tmpBu = tmpB4Bu->next;
			}
		}
	}
}

void Bullet::draw() {
	if (
		x > (X_MIN+SideMargin) &&
		x < (X_MAX-SideMargin) &&
		y > (HEADER_HEIGHT+UpMargin)
	) {
		putpixel(x, y, WHITE);
		putpixel(x, y+1, WHITE);
		putpixel(x, y-1, WHITE);
		putpixel(x+1, y, WHITE);
		putpixel(x-1, y, WHITE);
	}
}

void Bullet::erase() {
	putpixel(x, y, BLACK);
	putpixel(x, y+1, BLACK);
	putpixel(x, y-1, BLACK);
	putpixel(x+1, y, BLACK);
	putpixel(x-1, y, BLACK);
}
