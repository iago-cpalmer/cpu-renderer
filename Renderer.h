#ifndef RENDERER_H
#define RENDERER_H

#include <gmtl/gmtl.h>
#include <gmtl/Matrix.h>
#include <cmath>

#include "Window.h"
#include "Vertex.h"
#include "Texture.h"

class Renderer
{
public:
	// --------------------------------
	// Constructor
	// --------------------------------

	Renderer();

	// --------------------------------
	// Functions
	// --------------------------------
	
	void DrawLine(Window* rp_window, gmtl::Vec3f r_v1, gmtl::Vec3f r_v2, COLORREF r_color, float r_stroke_size);
	
	void DrawWireframe(Window* rp_window, Vertex r_v1, Vertex r_v2, Vertex r_v3);

	void FillTriangle(Window* rp_window, Vertex r_v1, Vertex r_v2, Vertex r_v3, Texture* rp_texture);
	void FillRectangle(Window* rp_window, const int r_xl, const int r_yt, const int r_xr, const int r_yb, COLORREF r_color);

private:
	// --------------------------------
	// Constants
	// --------------------------------
	
	static constexpr COLORREF COLOR_RED = RGB(255, 0, 0);

	// --------------------------------
	// Functions
	// --------------------------------

	void FillTriangleTopFlat(Window* rp_window, Vertex r_v1, Vertex r_v2, Vertex r_v3, Texture* rp_texture);
	void FillTriangleBottomFlat(Window* rp_window, Vertex r_v1, Vertex r_v2, Vertex r_v3, Texture* rp_texture);

	inline float Lerp(const float r_a, const float r_b, const float r_t);
	void SortVertices(Vertex* rp_v1, Vertex* rp_v2, Vertex* rp_v3);
};


#endif // !RENDERER_H

