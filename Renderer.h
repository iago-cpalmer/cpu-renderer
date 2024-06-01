#pragma once
#include "Window.h"

#include <gmtl/gmtl.h>
#include <gmtl/Matrix.h>
#include "Vertex.h"

class Renderer
{
public:
	// Constants
	const COLORREF COLOR_BLACK = RGB(0, 0, 0);
	const COLORREF COLOR_RED = RGB(255, 0, 0);
	const COLORREF WHITE = RGB(255, 255, 255);

	// Functions
	Renderer();
	void SortVertices(gmtl::Vec3f* v1, gmtl::Vec3f* v2, gmtl::Vec3f* v3);
	void FillTriangle(Window* window, gmtl::Vec3f v1, gmtl::Vec3f v2, gmtl::Vec3f v3);
	void FillTriangleTopFlat(Window* window, gmtl::Vec3f v1, gmtl::Vec3f v2, gmtl::Vec3f v3);
	void FillTriangleBottomFlat(Window* window, gmtl::Vec3f v1, gmtl::Vec3f v2, gmtl::Vec3f v3);
	void DrawWireframe(Window* window, gmtl::Vec3f v1, gmtl::Vec3f v2, gmtl::Vec3f v3);
	void DrawLine(Window* window, gmtl::Vec3f v1, gmtl::Vec3f v2, COLORREF color, float strokeSize);
	void FillRectangle(Window* window, int xl, int yt, int xr, int yb, COLORREF color);
};

