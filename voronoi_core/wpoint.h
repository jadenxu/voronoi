#ifndef WPOINT_H
#define WPOINT_H

class wpoint
{
public:
	wpoint(int x, int y, double w = 0.0)
	{
		this->x = x;
		this->y = y;
		this->w = w;
	}
	int x;
	int y;
	double w;
};

#endif