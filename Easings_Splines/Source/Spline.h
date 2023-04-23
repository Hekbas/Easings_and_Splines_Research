#pragma once

#include "Point.h"
#include "List.h"

class Spline
{
public:
	Spline();
	~Spline();

	iPoint GetSplinePoint(double t, bool looped = false);

	List<iPoint> points;
	int selectedPoint = 0;

private:

};