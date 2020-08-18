#pragma once
class Point2D
{
public:
	Point2D();
	~Point2D();
	Point2D(int r, int c);
	Point2D(Point2D* p);

	int getRow();
	int getCol();

private:
	int row, col;
};

