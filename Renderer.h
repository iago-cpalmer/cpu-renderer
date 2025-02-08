#ifndef RENDERER_H
#define RENDERER_H

#include <gmtl/gmtl.h>
#include <gmtl/Matrix.h>
#include <cmath>

#include "Window.h"
#include "Vertex.h"
#include "Texture.h"
#include "Rect.h"
#include "Mesh.h"


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

	void Render();

	void RenderMesh(Mesh* rp_mesh);

	void SetGraphicBuffers(GraphicBuffers* rp_graphic_buffers);
	
	void DrawLine(gmtl::Vec3f r_v1, gmtl::Vec3f r_v2, COLORREF r_color, float r_stroke_size);
	
	void DrawWireframe( Vertex r_v1, Vertex r_v2, Vertex r_v3);

	void FillTriangle(Vertex r_v1, Vertex r_v2, Vertex r_v3, Texture* rp_texture);
	void FillRectangle(const int r_xl, const int r_yt, const int r_xr, const int r_yb, COLORREF r_color);
	void FillCircle(const gmtl::Vec2i r_center, const int r_radius, COLORREF r_color);
	void DrawCircle(const gmtl::Vec2i r_center, const int r_radius, COLORREF r_color);

	void DrawRect(const Rect r_rect, COLORREF r_color);

	void SetClipRect(const Rect r_rect);

	void SetClippingEnabled(const bool r_clip_enabled);

private:
	// --------------------------------
	// Constants
	// --------------------------------
	
	static constexpr COLORREF COLOR_RED = RGB(255, 0, 0);
	static constexpr std::size_t INITIAL_RENDER_QUEUE_CAPACITY = 100;
	static constexpr std::size_t INITIAL_GEOM_VERTEX_CAPACITY = 1000;
	static constexpr std::size_t INITIAL_GEOM_INDEX_CAPACITY = 3000;

	// --------------------------------
	// Variables
	// --------------------------------
	
	GraphicBuffers* mp_graphic_buffers;

	Rect m_clip_rect;

	bool m_geometry_clipping_enabled = false;

	std::vector<Mesh*> m_render_queue;
	std::size_t m_mesh_count;

	Mesh m_geom_output;

	// --------------------------------
	// Functions
	// --------------------------------

	void GeometryPass();
	void RasterizationPass();

	void FillTriangleTopFlat(Vertex r_v1, Vertex r_v2, Vertex r_v3, Texture* rp_texture);
	void FillTriangleBottomFlat(Vertex r_v1, Vertex r_v2, Vertex r_v3, Texture* rp_texture);

	inline float Lerp(const float r_a, const float r_b, const float r_t);
	void SortVertices(Vertex* rp_v1, Vertex* rp_v2, Vertex* rp_v3);

	bool ClipLine(gmtl::Vec3f& r_v1, gmtl::Vec3f& r_v2);
	bool ClipTriangle(const gmtl::Vec3f& r_v1, const gmtl::Vec3f& r_v2, const gmtl::Vec3f& r_v3);

	uint8_t GetClippingFlags(int x, int y);

	float GetYAt(const gmtl::Vec3f& r_v1, const gmtl::Vec3f& r_v2, const float r_x);
	float GetXAt(const gmtl::Vec3f& r_v1, const gmtl::Vec3f& r_v2, const float r_y);

	inline void SetPixelAt(int r_x, int r_y, COLORREF r_color)
	{
		mp_graphic_buffers->SetPixel(r_x, r_y, r_color);
	}
};


#endif // !RENDERER_H

