#pragma once
#include "Point2D.h"
#include <string>
#include <vector>

using namespace std;


class HomeObject
{
public:
	HomeObject();
	~HomeObject();
	HomeObject(Point2D* p, string str);
	Point2D getLocation();
	string getName();
private:
	Point2D location;
	string name;
	vector<string> precondition; // to use it, for example to use a plate it must be on "table" and it must be "clean"
	vector<double> effect; // it is possible to use it to adjust peron state(hunger, energy, social needs, fun)


};

