#include "Room.h"
#include <stdlib.h>



Room::Room()
{
}


Room::~Room()
{
}

Room::Room(Point2D* plt, int w, int h)
{
	LeftTop = new Point2D(plt);
	width = w;
	height = h;
}

int Room::getWidth()
{
	return width;
}

int Room::getHeight()
{
	return height;
}

Point2D* Room::getLeftTop()
{
	return LeftTop;
}

void Room::setLeftTop(Point2D* p)
{
	LeftTop = new Point2D(p);
}

void Room::setWidth(int w)
{
	width = w;
}

void Room::setHeight(int h)
{
	height = h;
}

Point2D Room::ChoosePoint()
{
	int r, c;

	r = LeftTop->getRow() + rand() % height;
	c = LeftTop->getCol() + rand() % width;
	return new Point2D(r, c);
}

Point2D Room::getCenter()
{
	Point2D* center = new Point2D(LeftTop->getRow() + height / 2, LeftTop->getCol() + width / 2);

	return *center;
}
