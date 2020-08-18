#include "HomeObject.h"



HomeObject::HomeObject()
{
}


HomeObject::~HomeObject()
{
}

HomeObject::HomeObject(Point2D* p, string str)
{
	location = *p;
	name = str;
}

Point2D HomeObject::getLocation()
{
	return location;
}

string HomeObject::getName()
{
	return name;
}
