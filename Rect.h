#ifndef RECT_H
#define RECT_H

struct Rect
{
	int xi;
	int yi;
	int width;
	int height;

	bool IsInsideRect(const int r_x, const int r_y)
	{
		return r_x >= xi && r_x <= (xi + width) && r_y >= yi && r_x <= (yi + height);
	}
};

#endif // RECT_H

