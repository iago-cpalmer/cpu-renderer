#pragma once
#ifndef RENDERER_H
#define RENDERER_H


#include "Window.h"

#include <gmtl/gmtl.h>
#include <gmtl/Matrix.h>
#include "Vertex.h"
#include "Texture.h"

class Renderer
{
public:
	// Constants
	const COLORREF COLOR_BLACK = RGB(0, 0, 255);
	const COLORREF COLOR_RED = RGB(0, 255, 0);
	const COLORREF WHITE = RGB(255, 0, 0);

	// Functions
	Renderer();
	float lerp(float a, float b, float t);
	void SortVertices(Vertex* v1, Vertex* v2, Vertex* v3);
	void FillTriangle(Window* window, Vertex v1, Vertex v2, Vertex v3, Texture* texture);
	void FillTriangleTopFlat(Window* window, Vertex v1, Vertex v2, Vertex v3, Texture* texture);
	void FillTriangleBottomFlat(Window* window, Vertex v1, Vertex v2, Vertex v3, Texture* texture);
	void DrawWireframe(Window* window, Vertex v1, Vertex v2, Vertex v3);
	void DrawLine(Window* window, gmtl::Vec3f v1, gmtl::Vec3f v2, COLORREF color, float strokeSize);
	void FillRectangle(Window* window, int xl, int yt, int xr, int yb, COLORREF color);
};


#endif // !RENDERER_H

