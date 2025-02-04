#define POW2(x) x*x
#include "Renderer.h"

// ====================================
// Public
// ====================================

// --------------------------------
// Constructor
// --------------------------------
Renderer::Renderer()
{
}

// --------------------------------
// Functions
// --------------------------------

void Renderer::FillTriangle(Window* rp_window, Vertex r_v1, Vertex r_v2, Vertex r_v3, Texture* rp_texture) {
	
	SortVertices(&r_v1, &r_v2, &r_v3);	
	if (r_v2.Position[1] == r_v3.Position[1]) {
		FillTriangleBottomFlat(rp_window, r_v1, r_v2, r_v3, rp_texture);
	}
	else if (r_v2.Position[1] == r_v1.Position[1]) {
		FillTriangleTopFlat(rp_window, r_v1, r_v2, r_v3, rp_texture);
	}
	else {
		// Split in 2
		float m = (r_v3.Position[1] - r_v1.Position[1]) / abs(r_v3.Position[0]-r_v1.Position[0]);
		float x = 0;
		if (r_v3.Position[0] > r_v1.Position[0]) {
			x = r_v1.Position[0] + floor((r_v2.Position[1] - r_v1.Position[1]) / m);
		} else {
			x = r_v3.Position[0] + floor((r_v3.Position[1] - r_v2.Position[1]) / m);
		}
		float y = r_v2.Position[1];


		float xf = max(r_v3.Position[0], r_v1.Position[0]);
		float xi = min(r_v3.Position[0], r_v1.Position[0]);

		float yf = max(r_v3.Position[1], r_v1.Position[1]);
		float yi = min(r_v3.Position[1], r_v1.Position[1]);

		float yl = (float)(y - yi) / (yf - yi);
		float xl = (float)(x - xi) / (xf - xi);
		
		float z = Lerp(r_v1.Position[2], r_v3.Position[2], yl);
		gmtl::Vec3f intermediateCoord = gmtl::Vec3f(x, y, z);

		// Calculate intermediate uv coordinates
		float u = Lerp(r_v1.UV[0], r_v3.UV[0], xl);
 		float v = Lerp(r_v1.UV[1], r_v3.UV[1], yl);
		
		Vertex p{ intermediateCoord, gmtl::Vec3f(), gmtl::Vec2f(u, v) };

		FillTriangleBottomFlat(rp_window, r_v1, r_v2, p, rp_texture);
		FillTriangleTopFlat(rp_window, p, r_v2, r_v3, rp_texture);
	}
	
}


void Renderer::DrawWireframe(Window* rp_window, Vertex r_v1, Vertex r_v2, Vertex r_v3)
{
	DrawLine(rp_window, r_v1.Position, r_v2.Position, COLOR_RED, 1);
	DrawLine(rp_window, r_v2.Position, r_v3.Position, COLOR_RED, 1);
	DrawLine(rp_window, r_v3.Position, r_v1.Position, COLOR_RED, 1);
}

void Renderer::DrawLine(Window* rp_window, gmtl::Vec3f r_v1, gmtl::Vec3f r_v2, COLORREF r_color, float r_stroke_size)
{
	float m;
	bool invertAxis;
	if (r_v2[0] == r_v1[0]) {
		if (r_v2[1] == r_v1[1]) {
			// Invalid line?
			return;
		}		
		if (r_v1[1] > r_v2[1]) {
			gmtl::Vec3f aux = r_v2;
			r_v2 = r_v1;
			r_v1 = aux;
		}
		m = (r_v2[0] - r_v1[0]) / (r_v2[1] - r_v1[1]);
		invertAxis = true;
	}
	else {
		m = (r_v2[1] - r_v1[1]) / (r_v2[0] - r_v1[0]);
		if (r_v1[0] > r_v2[0]) {
			gmtl::Vec3f aux = r_v2;
			r_v2 = r_v1;
			r_v1 = aux;
		}
		invertAxis = false;
	}

	// Clip line
	if (!ClipLine(r_v1, r_v2))
	{
		return;
	}

	float y = 0;
	float error = 0;
	int axis = invertAxis ? 1 : 0;
	m *= r_stroke_size;
	for (int x = r_v1[axis]; x < r_v2[axis]; x+=r_stroke_size) {
		error = error + m - r_stroke_size;
		if (invertAxis) {
			if (r_stroke_size > 1) {
				FillRectangle(rp_window, r_v1[0] + y - r_stroke_size, x - r_stroke_size, r_v1[0] + y + r_stroke_size, x + r_stroke_size, r_color);
				if (error >= r_stroke_size) {
					for (int i = 1; i <= floor(error); i+= r_stroke_size) {
						FillRectangle(rp_window, r_v1[0] + y + i - r_stroke_size, x - r_stroke_size, r_v1[0] + y + i + r_stroke_size, x + r_stroke_size, r_color);
					}
					
					error -= floor(error);
				}
			}
			else {
				rp_window->SetPixelAt(r_v1[0] + y, x, r_color);
				
				if (error >= r_stroke_size) {
					for (int i = 1; i <= floor(error); i++) {
						rp_window->SetPixelAt(r_v1[0] + y + i, x, r_color);
					}
					
					error -= floor(error);
				}
			}
			
		}
		else {
			if (r_stroke_size > 1) {
				FillRectangle(rp_window, x - r_stroke_size, r_v1[1] + y - r_stroke_size, x + r_stroke_size, r_v1[1] + y + r_stroke_size, r_color);
				if (error >= r_stroke_size) {
					for (int i = 1; i <= floor(error); i+= r_stroke_size) {
						FillRectangle(rp_window, x - r_stroke_size, r_v1[1] + y + i - r_stroke_size, x + r_stroke_size, r_v1[1] + y +i + r_stroke_size, r_color);
					}
					
					error -= floor(error);
				}
			}
			else {
				rp_window->SetPixelAt(x, floor(r_v1[1] + y), r_color);

				if (error >= r_stroke_size) {
					
					for (int i = 1; i <= floor(error); i+= r_stroke_size) {
						rp_window->SetPixelAt(x, floor(r_v1[1] + y) + i, r_color);
					}					
					error -= floor(error);
				}
			}
		}
		
		y += m;
	}
}

void Renderer::FillRectangle(Window* rp_window, const int r_xl, const int r_yt, const int r_xr, const int r_yb, COLORREF r_color)
{
	for (int x = r_xl; x < r_xr; x++) {
		for (int y = r_yt; y < r_yb; y++) {
			rp_window->SetPixelAt(x, y, r_color);
		}
	}
}

// Using Mid-point algorithm
void Renderer::DrawCircle(Window* rp_window, const gmtl::Vec2i r_center, const int r_radius, COLORREF r_color)
{
	const int Xi = 0;
	const int Yi = r_radius;

	rp_window->SetPixelAt(Xi + r_center[0], Yi + r_center[1], r_color);
	rp_window->SetPixelAt(Xi + r_center[0], -Yi + r_center[1], r_color);
	rp_window->SetPixelAt(Yi + r_center[0], Xi + r_center[1], r_color);
	rp_window->SetPixelAt(-Yi + r_center[0], Xi + r_center[1], r_color);
	
	int x = Xi, y = Yi;

	float d = 1 - r_radius;
	float dE = 3;
	float dSE = -2 * r_radius + 5;

	while (abs(y) > abs(x))
	{
		if (d < 0)
		{
			d += dE;
			dE += 2;
			dSE += 2;
		}
		else
		{
			d += dSE;
			dE += 2;
			dSE += 4;
			y--;
		}
		x++;

		// Draw octant 1
		rp_window->SetPixelAt(x + r_center[0], r_center[1] - y, r_color);
		// Draw octant 2
		rp_window->SetPixelAt(y + r_center[0], -x + r_center[1], r_color);
		// Draw octant 3
		rp_window->SetPixelAt(y + r_center[0], x + r_center[1], r_color);
		// Draw octant 4
		rp_window->SetPixelAt(x + r_center[0], y + r_center[1], r_color);
		// Draw octant 5
		rp_window->SetPixelAt(-x + r_center[0], y + r_center[1], r_color);
		// Draw octant 6
		rp_window->SetPixelAt(-y + r_center[0], -x + r_center[1], r_color);
		// Draw octant 7
		rp_window->SetPixelAt(-y + r_center[0], x + r_center[1], r_color);
		// Draw octant 8
		rp_window->SetPixelAt(-x + r_center[0], -y + r_center[1], r_color);
	}
}

void Renderer::FillCircle(Window* rp_window, const gmtl::Vec2i r_center, const int r_radius, COLORREF r_color)
{
	const int Xi = 0;
	const int Yi = r_radius;

	DrawLine(rp_window, gmtl::Vec3f(-Yi + r_center[0], r_center[1], 0), gmtl::Vec3f(Yi + r_center[0], r_center[1], 0), r_color, 1);

	int x = Xi, y = Yi;

	float d = 1 - r_radius;
	float dE = 3;
	float dSE = -2 * r_radius + 5;

	while (abs(y) > abs(x))
	{
		if (d < 0)
		{
			d += dE;
			dE += 2;
			dSE += 2;
		}
		else
		{
			d += dSE;
			dE += 2;
			dSE += 4;
			y--;
		}
		x++;

		// Octant 1 to 8
		DrawLine(rp_window, gmtl::Vec3f(x + r_center[0], r_center[1] - y, 0), gmtl::Vec3f(-x + r_center[0], -y + r_center[1], 0), r_color, 1);
		// Octant 3 to 6
		DrawLine(rp_window, gmtl::Vec3f(y + r_center[0], x + r_center[1], 0), gmtl::Vec3f(-y + r_center[0], x + r_center[1], 0), r_color, 1);
		// Octant 2 to 7
		DrawLine(rp_window, gmtl::Vec3f(y + r_center[0], -x + r_center[1], 0), gmtl::Vec3f(-y + r_center[0], -x + r_center[1], 0), r_color, 1);
		// Octant 4 to 5
		DrawLine(rp_window, gmtl::Vec3f(x + r_center[0], y + r_center[1], 0), gmtl::Vec3f(-x + r_center[0], y + r_center[1], 0), r_color, 1);
	}
}

void Renderer::DrawRect(Window* rp_window, const Rect r_rect, COLORREF r_color)
{
	gmtl::Vec3f vTL = gmtl::Vec3f(r_rect.xi, r_rect.yi, 0);
	gmtl::Vec3f vTR = gmtl::Vec3f(r_rect.xi + r_rect.width, r_rect.yi, 0);
	gmtl::Vec3f vBL = gmtl::Vec3f(r_rect.xi, r_rect.yi + r_rect.height, 0);
	gmtl::Vec3f vBR = gmtl::Vec3f(r_rect.xi + r_rect.width, r_rect.yi + r_rect.height, 0);
	DrawLine(rp_window, vTL, vTR, r_color, 1);
	DrawLine(rp_window, vTL, vBL, r_color, 1);
	DrawLine(rp_window, vTR, vBR, r_color, 1);
	DrawLine(rp_window, vBL, vBR, r_color, 1);
}

void Renderer::SetClipRect(const Rect r_rect)
{
	m_clip_rect = r_rect;
}

void Renderer::SetClippingEnabled(const bool r_clip_enabled)
{
	m_geometry_clipping_enabled = r_clip_enabled;
}

// ====================================
// Private
// ====================================

// --------------------------------
// Functions
// --------------------------------

inline float Renderer::Lerp(const float r_a, const float r_b, const float r_t) {
	return ((r_b - r_a) * r_t) + r_a;
}

void Renderer::FillTriangleTopFlat(Window* rp_window, Vertex r_v1, Vertex r_v2, Vertex r_v3, Texture* rp_texture)
{
	// v2.y == v1.y
	float m23 = (r_v2.Position[1] - r_v3.Position[1]) / abs(r_v2.Position[0] - r_v3.Position[0]);
	float m13 = (r_v1.Position[1] - r_v3.Position[1]) / abs(r_v1.Position[0] - r_v3.Position[0]);
	float error = 0;
	for (int y = floor(r_v2.Position[1]); y < floor(r_v3.Position[1]); y++) {

		float xif = (r_v2.Position[0] > r_v3.Position[0] ? 1 : -1) * floor((y - floor(r_v2.Position[1])) / m23) + r_v2.Position[0];
		float xff = (r_v1.Position[0] > r_v3.Position[0] ? 1 : -1) * floor((y - floor(r_v2.Position[1])) / m13) + r_v1.Position[0];

		int xi = floor(xif);
		int xf = floor(xff);
		error += (xff - xf) + (xif - xi);
		if (xi > xf) {
			std::swap(xi, xf);
		}
		if (error >= 0.5f) {
			xf += 1;
			error -= 0.5f;
		}
		float yl = (float)(y - r_v2.Position[1]) / (r_v3.Position[1] - r_v2.Position[1]);

		for (int i = xi; i < xf; i++) {
			float xl = ((float)i - xi) / (float)(xf - xi);
			float xl23 = (float)(i - r_v2.Position[0]) / (float)(r_v3.Position[0] - r_v2.Position[0]);
			float xl13 = (float)(i - r_v1.Position[0]) / (float)(r_v3.Position[0] - r_v1.Position[0]);

			// Interpolate colors along the edges
			COLORREF colorLeft = RGB(
				Lerp(r_v2.Color[0], r_v3.Color[0], yl),
				Lerp(r_v2.Color[1], r_v3.Color[1], yl),
				Lerp(r_v2.Color[2], r_v3.Color[2], yl)
			);

			COLORREF colorRight = RGB(
				Lerp(r_v1.Color[0], r_v3.Color[0], yl),
				Lerp(r_v1.Color[1], r_v3.Color[1], yl),
				Lerp(r_v1.Color[2], r_v3.Color[2], yl)
			);

			// Interpolate colors between the left and right edges
			COLORREF color = RGB(
				Lerp(GetRValue(colorLeft), GetRValue(colorRight), xl),
				Lerp(GetGValue(colorLeft), GetGValue(colorRight), xl),
				Lerp(GetBValue(colorLeft), GetBValue(colorRight), xl)
			);

			float uRight = Lerp(r_v1.UV[0], r_v3.UV[0], yl);
			float uLeft = Lerp(r_v2.UV[0], r_v3.UV[0], yl);

			float vRight = Lerp(r_v1.UV[1], r_v3.UV[1], yl);
			float vLeft = Lerp(r_v2.UV[1], r_v3.UV[1], yl);

			if (rp_texture != nullptr)
			{
				color = rp_texture->GetColorAtUV(Lerp(uLeft, uRight, xl), Lerp(vLeft, vRight, xl));
			}
			rp_window->SetPixelAt(i, y, color);
		}
	}
}

void Renderer::FillTriangleBottomFlat(Window* window, Vertex r_v1, Vertex r_v2, Vertex r_v3, Texture* rp_texture)
{
	// v2.y == v3.y
	float m21 = (r_v2.Position[1] - r_v1.Position[1]) / (r_v2.Position[0] - r_v1.Position[0]);
	float m31 = (r_v3.Position[1] - r_v1.Position[1]) / (r_v3.Position[0] - r_v1.Position[0]);
	float error = 0;
	for (int y = floor(r_v2.Position[1]); y > floor(r_v1.Position[1]); y--) {

		float xif = (r_v2.Position[0] + (y - r_v2.Position[1]) / m21);
		float xff = (r_v3.Position[0] + (y - r_v3.Position[1]) / m31);

		int xi = floor(xif);
		int xf = floor(xff);
		error += (xff - xf) + (xif - xi);
		if (xi > xf) {
			std::swap(xi, xf);
		}
		if (error >= 0.5f) {
			xf += 1;
			error -= 0.5f;
		}
		float yl = (float)(y - r_v1.Position[1]) / (r_v2.Position[1] - r_v1.Position[1]);

		for (int i = xi; i < xf; i++) {
			float xl = (float)(i - xi) / (float)(xf - xi);

			float xl23 = (float)(i - r_v2.Position[0]) / (float)(r_v2.Position[0] - r_v1.Position[0]);
			float xl13 = (float)(i - r_v3.Position[0]) / (float)(r_v3.Position[0] - r_v1.Position[0]);

			// Interpolate colors along the edges
			COLORREF colorLeft = RGB(
				Lerp(r_v1.Color[0], r_v2.Color[0], yl),
				Lerp(r_v1.Color[1], r_v2.Color[1], yl),
				Lerp(r_v1.Color[2], r_v2.Color[2], yl)
			);

			COLORREF colorRight = RGB(
				Lerp(r_v1.Color[0], r_v3.Color[0], yl),
				Lerp(r_v1.Color[1], r_v3.Color[1], yl),
				Lerp(r_v1.Color[2], r_v3.Color[2], yl)
			);

			// Interpolate colors between the left and right edges
			COLORREF color = RGB(
				Lerp(GetRValue(colorLeft), GetRValue(colorRight), xl),
				Lerp(GetGValue(colorLeft), GetGValue(colorRight), xl),
				Lerp(GetBValue(colorLeft), GetBValue(colorRight), xl)
			);

			float uLeft = Lerp(r_v1.UV[0], r_v2.UV[0], yl);
			float uRight = Lerp(r_v1.UV[0], r_v3.UV[0], yl);

			float vLeft = Lerp(r_v1.UV[1], r_v2.UV[1], yl);
			float vRight = Lerp(r_v1.UV[1], r_v3.UV[1], yl);


			if (rp_texture != nullptr)
			{
				color = rp_texture->GetColorAtUV(Lerp(uLeft, uRight, xl), Lerp(vLeft, vRight, xl));
			}
			window->SetPixelAt(i, y, color);
		}
	}
}


void Renderer::SortVertices(Vertex * rp_v1, Vertex * rp_v2, Vertex * rp_v3)
{
	// Sort vertices so v1.y<=v2.y<=v3.y
	
	Vertex aux;
	if ((*rp_v1).Position[1] > (*rp_v2).Position[1] && (*rp_v1).Position[1] > (*rp_v3).Position[1]) {
		aux = *rp_v1;
		*rp_v1 = *rp_v3;
		*rp_v3 = aux;
		if ((*rp_v1).Position[1] > (*rp_v2).Position[1]) {
			aux = *rp_v1;
			*rp_v1 = *rp_v2;
			*rp_v2 = aux;
		}
	}
	else if ((*rp_v2).Position[1] > (*rp_v1).Position[1] && (*rp_v2).Position[1] > (*rp_v3).Position[1]) {
		aux = *rp_v2;
		*rp_v2 = *rp_v3;
		*rp_v3 = aux;
		if ((*rp_v1).Position[1] > (*rp_v2).Position[1]) {
			aux = *rp_v1;
			*rp_v1 = *rp_v2;
			*rp_v2 = aux;
		}
	}
	else if ((*rp_v1).Position[1] > (*rp_v2).Position[1]) {
		aux = *rp_v1;
		*rp_v1 = *rp_v2;
		*rp_v2 = aux;
	}
	
}


bool Renderer::ClipLine(gmtl::Vec3f& r_v1, gmtl::Vec3f& r_v2)
{
	if (!m_geometry_clipping_enabled)
	{
		return true;
	}
	uint8_t v1Flags = GetClippingFlags(r_v1[0], r_v1[1]);
	uint8_t v2Flags = GetClippingFlags(r_v2[0], r_v2[1]);

	if (v1Flags == v2Flags && v1Flags == 0b1111)
	{
		// Trivially accepted
		return true;
	}

	if (v1Flags == v2Flags && v1Flags != 0b1111 )
	{
		// Trivially rejected
		return false;
	}

	// Check if v1 is inside
	if (v1Flags != 0b1111)
	{
		switch (v1Flags)
		{
			case 0b0110:
			{
				int dy = r_v1[1] - (m_clip_rect.yi + m_clip_rect.height);

				r_v1[0] = r_v1[0] + GetXAt(r_v1, r_v2, dy);
				r_v1[1] = (m_clip_rect.yi + m_clip_rect.height);	
				break;
			}	
			case 0b1010:
			case 0b1110:
			{
				int dx = m_clip_rect.xi - r_v1[0];
				int y = GetYAt(r_v1, r_v2, dx);

				r_v1[0] = m_clip_rect.xi;
				r_v1[1] = -y + r_v1[1];
				break;
			}

			case 0b1011:
			{
				int dy = (m_clip_rect.yi) - r_v1[1];

				r_v1[0] = r_v1[0] + GetXAt(r_v1, r_v2, dy);
				r_v1[1] = m_clip_rect.yi;
				break;
			}
			case 0b0111:
			{
				int dy = r_v1[1] - (m_clip_rect.yi + m_clip_rect.height);

				r_v1[0] = r_v1[0] + GetXAt(r_v1, r_v2, dy);
				r_v1[1] = m_clip_rect.yi + m_clip_rect.height;
				break;
			}

		}
	}
	if (v2Flags != 0b1111)
	{
		switch (v2Flags)
		{
		case 0b1011:
		{
			int dy = m_clip_rect.yi - r_v2[1];

			r_v2[0] = r_v2[0] - GetXAt(r_v2, r_v1, dy);
			r_v2[1] = m_clip_rect.yi;
			break;
		}
		case 0b0111:
		{
			int dy = r_v2[1] - (m_clip_rect.yi + m_clip_rect.height);

			r_v2[0] = r_v2[0] - GetXAt(r_v2, r_v1, dy);
			r_v2[1] = m_clip_rect.yi + m_clip_rect.height;
			break;
		}
		case 0b1001:
		case 0b0101:
		case 0b1101:
		{
			int rectXf = m_clip_rect.xi + m_clip_rect.width;
			int dx = r_v2[0] - rectXf;
			int y = GetYAt(r_v2, r_v1, dx);
			r_v2[0] = r_v2[0] - dx;
			r_v2[1] = -y + r_v2[1];
			break;
		}
		}
	}
	
	return true;
}

float Renderer::GetYAt(const gmtl::Vec3f& r_v1, const gmtl::Vec3f& r_v2, const float r_x)
{
	float m = abs(r_v2[1] - r_v1[1]) / abs(r_v2[0] - r_v1[0]);
	// y = mx + yi
	float xi = min(r_v1[0], r_v2[0]);
	return m * r_x;
}

float Renderer::GetXAt(const gmtl::Vec3f& r_v1, const gmtl::Vec3f& r_v2, const float r_y)
{
	float m = abs(r_v2[1] - r_v1[1]) / abs(r_v2[0] - r_v1[0]);
	// y = mx + yi
	// x = (y - yi) / m
	return r_y / m;
}

uint8_t Renderer::GetClippingFlags(int x, int y)
{
	uint8_t flags = 0;
	
	if (x >= m_clip_rect.xi)
	{
		flags |= 0b1;
	}
	if (x <= (m_clip_rect.xi + m_clip_rect.width))
	{
		flags |= 0b10;
	}

	if (y >= (m_clip_rect.yi))
	{
		flags |= 0b100;
	}

	if (y <= (m_clip_rect.yi + m_clip_rect.height))
	{
		flags |= 0b1000;
	}

	return flags;
}


