#ifndef RENDERER_H
#define RENDERER_H

#include <gmtl/gmtl.h>
#include <gmtl/Matrix.h>
#include <cmath>

#include "Window.h"
#include "Vertex.h"
#include "Texture.h"
#include "Rect.h"


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
	void FillCircle(Window* rp_window, const gmtl::Vec2i r_center, const int r_radius, COLORREF r_color);
	void DrawCircle(Window* rp_window, const gmtl::Vec2i r_center, const int r_radius, COLORREF r_color);

	void DrawRect(Window* rp_window, const Rect r_rect, COLORREF r_color);

	void SetClipRect(const Rect r_rect);

	void SetClippingEnabled(const bool r_clip_enabled);

private:
	// --------------------------------
	// Constants
	// --------------------------------
	
	static constexpr COLORREF COLOR_RED = RGB(255, 0, 0);

	const Rect CLIPPING_RECT = { 200, 200, 300, 300 };

	// --------------------------------
	// Variables
	// --------------------------------

	Rect m_clip_rect;

	bool m_geometry_clipping_enabled = false;

	// --------------------------------
	// Functions
	// --------------------------------

	void FillTriangleTopFlat(Window* rp_window, Vertex r_v1, Vertex r_v2, Vertex r_v3, Texture* rp_texture);
	void FillTriangleBottomFlat(Window* rp_window, Vertex r_v1, Vertex r_v2, Vertex r_v3, Texture* rp_texture);

	inline float Lerp(const float r_a, const float r_b, const float r_t);
	void SortVertices(Vertex* rp_v1, Vertex* rp_v2, Vertex* rp_v3);

	bool ClipLine(gmtl::Vec3f& r_v1, gmtl::Vec3f& r_v2);

	uint8_t GetClippingFlags(int x, int y);

	float GetYAt(const gmtl::Vec3f& r_v1, const gmtl::Vec3f& r_v2, const float r_x);
	float GetXAt(const gmtl::Vec3f& r_v1, const gmtl::Vec3f& r_v2, const float r_y);
};


#endif // !RENDERER_H

