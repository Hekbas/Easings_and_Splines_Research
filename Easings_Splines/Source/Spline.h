#pragma once

#include "Point.h"
#include "List.h"

class Spline
{
public:
	Spline();
	~Spline();

public:

	List<iPoint> points;
	int selectedPoint = 0;

private:

};