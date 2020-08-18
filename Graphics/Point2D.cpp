#include "Point2D.h"



Point2D::Point2D()
{
}


Point2D::~Point2D()
{
}

Point2D::Point2D(int r, int c)
{
	row = r;
	col = c;
}

Point2D::Point2D(Point2D* p)
{
	row = p->row;
	col = p->col;
}

int Point2D::getRow()
{
	return row;
}

int Point2D::getCol()
{
	return col;
}
