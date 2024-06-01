#include "Renderer.h"


Renderer::Renderer()
{
}

void Renderer::FillTriangleTopFlat(Window* window, Vertex v1, Vertex v2, Vertex v3, Texture* texture)
{
	// v2.y == v1.y
	float m23 = (v2.Position[1] - v3.Position[1]) / abs(v2.Position[0] - v3.Position[0]);
	float m13 = (v1.Position[1] - v3.Position[1]) / abs(v1.Position[0] - v3.Position[0]);
	std::cout << v1.Color << ", " << v2.Color << ", " << v3.Color << std::endl;
	float error = 0; 
	for (int y = floor(v2.Position[1]); y < floor(v3.Position[1]); y++) {

		float xif = (v2.Position[0] > v3.Position[0] ? 1 : -1) * floor((y - floor(v2.Position[1])) / m23) + v2.Position[0];
		float xff = (v1.Position[0] > v3.Position[0] ? 1 : -1) * floor((y - floor(v2.Position[1])) / m13) + v1.Position[0];

		int xi = floor(xif);
		int xf = floor(xff);
		error += (xff - xf) + (xif - xi);
		if (xi > xf) {
			int aux = xf;
			xf = xi;
			xi = xf;
		}
		if (error >= 0.5f) {
			xf += 1;
			error -= 0.5f;
		}
		float yl = (float)(y - v2.Position[1]) / (v3.Position[1] - v2.Position[1]);

		for (int i = xi; i < xf; i++) {
			float xl = ((float)i - xi) / (float)(xf - xi);
			float xl23 = (float)(i - v2.Position[0]) / (float)(v3.Position[0] - v2.Position[0]);
			float xl13 = (float)(i - v1.Position[0]) / (float)(v3.Position[0] - v1.Position[0]);

			// Interpolate colors along the edges
			COLORREF colorLeft = RGB(
				lerp(v2.Color[0], v3.Color[0], yl),
				lerp(v2.Color[1], v3.Color[1], yl),
				lerp(v2.Color[2], v3.Color[2], yl)
			);

			COLORREF colorRight = RGB(
				lerp(v1.Color[0], v3.Color[0], yl),
				lerp(v1.Color[1], v3.Color[1], yl),
				lerp(v1.Color[2], v3.Color[2], yl)
			);

			// Interpolate colors between the left and right edges
			COLORREF color = RGB(
				lerp(GetRValue(colorLeft), GetRValue(colorRight), xl),
				lerp(GetGValue(colorLeft), GetGValue(colorRight), xl),
				lerp(GetBValue(colorLeft), GetBValue(colorRight), xl)
			);

			float uRight = lerp(v1.UV[0], v3.UV[0], yl);
			float uLeft = lerp(v2.UV[0], v3.UV[0], yl);

			float vRight = lerp(v1.UV[1], v3.UV[1], yl);
			float vLeft = lerp(v2.UV[1], v3.UV[1], yl);

			COLORREF texColor = texture->GetColorAtUV(lerp(uLeft, uRight, xl), lerp(vLeft, vRight, xl));

			window->SetPixelAt(i, y, texColor);
		}

		/*
		float yl = (float)(y-v2.Position[1]) / (v3.Position[1] - v2.Position[1]);
		for (int i = xi; i < xf; i++) {
			float xl = ((float)i-xi) / (float)(xf - xi);
			float xl23 = abs(((float)i- v2.Position[0]) / (float)(v3.Position[0] - v2.Position[0]));
			float xl13 = abs(((float)i- v1.Position[0]) / (float)(v3.Position[0] - v1.Position[0]));
			COLORREF color1 = RGB(lerp(v1.Color[0], v2.Color[0], xl), lerp(v1.Color[1], v2.Color[1], xl), lerp(v1.Color[2], v2.Color[2], xl));
			COLORREF color2 = RGB(lerp(v1.Color[0], v3.Color[0], xl13 * yl), lerp(v1.Color[1], v3.Color[1], xl13 * yl), lerp(v1.Color[2], v3.Color[2], xl13 * yl));
			COLORREF color3 = RGB(lerp(v2.Color[0], v3.Color[0], xl23 * yl), lerp(v2.Color[1], v3.Color[1], xl23 * yl), lerp(v2.Color[2], v3.Color[2], xl23 * yl));
			window->SetPixelAt(i, y, color1 + color2 + color3);
		}*/
	}
}

float Renderer::lerp(float a, float b, float t) {
	
	return ((b - a) * t) + a;
	if (a < b) {
		return ((a - b) * t) + b;
	}
	else {
		return ((b - a) * t) + a;
	}
	
}

void Renderer::FillTriangleBottomFlat(Window* window, Vertex v1, Vertex v2, Vertex v3, Texture* texture)
{
	// v2.y == v3.y
	float m21 = (v2.Position[1] - v1.Position[1]) / abs(v2.Position[0] - v1.Position[0]);
	float m31 = (v3.Position[1] - v1.Position[1]) / abs(v3.Position[0] - v1.Position[0]);

	float error = 0;
	for (int y = floor(v2.Position[1]); y >= floor(v1.Position[1]); y--) {

		float xif = (v2.Position[0] > v1.Position[0] ? 1 : -1) * (y - (v2.Position[1])) / m21 + v2.Position[0];
		float xff = (v3.Position[0] > v1.Position[0] ? 1 : -1) * (y - (v2.Position[1])) / m31 + v3.Position[0];

		int xi = floor(xif);
		int xf = floor(xff);

		error += (xff - xf) + (xif-xi);
		
		if (xi > xf) {
			int aux = xf;
			xf = xi;
			xi = xf;
		}
		if (error >= 0.5f) {
			xf += 1;
			error -= 0.5f;
		}
		for (int i = xi; i <= xf; i++) {
			window->SetPixelAt(i, y, COLOR_BLACK);
		}
		
	}
}

void Renderer::FillTriangle(Window* window, Vertex v1, Vertex v2, Vertex v3, Texture* texture) {
	
	SortVertices(&v1, &v2, &v3);	
	if (v2.Position[1] == v3.Position[1]) {
		FillTriangleBottomFlat(window, v1, v2, v3, texture);
	}
	else if (v2.Position[1] == v1.Position[1]) {
		FillTriangleTopFlat(window, v1, v2, v3, texture);
	}
	else {
		// Split in 2
		
		float m = (v3.Position[1] - v1.Position[1]) / abs(v3.Position[0]-v1.Position[0]);
		//float x = (v3[0] > v1[0] ? v1[0] : v3[0]) + floor((v3[1]-v2[1]) / m);
		float x = 0;
		if (v3.Position[0] > v1.Position[0]) {
			x = v1.Position[0] + floor((v2.Position[1] - v1.Position[1]) / m);
		} else {
			x = v3.Position[0] + floor((v3.Position[1] - v2.Position[1]) / m);
		}
		Vertex p{ gmtl::Vec3f(x, v2.Position[1], v3.Position[2]),gmtl::Vec3f() }; // TODO: Compute x & z values from v1-v3 depending on height (v2.y)
		FillTriangleBottomFlat(window, v1, v2, p, texture);
		FillTriangleTopFlat(window, p, v2, v3, texture);
	}
	
}

void Renderer::SortVertices(Vertex* v1, Vertex* v2, Vertex* v3) {
	// Sort vertices so v1.y<=v2.y<=v3.y
	Vertex aux;
	if ((*v1).Position[1] > (*v2).Position[1] && (*v1).Position[1] > (*v3).Position[1]) {
		aux = *v1;
		*v1 = *v3;
		*v3 = aux;
		if ((*v1).Position[1] > (*v2).Position[1]) {
			aux = *v1;
			*v1 = *v2;
			*v2 = aux;
		}
	}
	else if ((*v2).Position[1] > (*v1).Position[1] && (*v2).Position[1] > (*v3).Position[1]) {
		aux = *v2;
		*v2 = *v3;
		*v3 = aux;
		if ((*v1).Position[1] > (*v2).Position[1]) {
			aux = *v1;
			*v1 = *v2;
			*v2 = aux;
		}
	}
	else if ((*v1).Position[1] > (*v2).Position[1]) {
		aux = *v1;
		*v1 = *v2;
		*v2 = aux;
	}

}

void Renderer::DrawWireframe(Window* window, Vertex v1, Vertex v2, Vertex v3)
{
	DrawLine(window, v1.Position, v2.Position, COLOR_RED, 1);
	DrawLine(window, v2.Position, v3.Position, COLOR_RED, 1);
	DrawLine(window, v3.Position, v1.Position, COLOR_RED, 1);
}

void Renderer::DrawLine(Window* window, gmtl::Vec3f v1, gmtl::Vec3f v2, COLORREF color, float strokeSize)
{
	float m;
	bool invertAxis;
	if (v2[0] == v1[0]) {
		if (v2[1] == v1[1]) {
			// Invalid line?
			return;
		}		
		if (v1[1] > v2[1]) {
			gmtl::Vec3f aux = v2;
			v2 = v1;
			v1 = aux;
		}
		m = (v2[0] - v1[0]) / (v2[1] - v1[1]);
		invertAxis = true;
	}
	else {
		m = (v2[1] - v1[1]) / (v2[0] - v1[0]);
		if (v1[0] > v2[0]) {
			gmtl::Vec3f aux = v2;
			v2 = v1;
			v1 = aux;
		}
		invertAxis = false;
	}
	float y = 0;
	float error = 0;
	int axis = invertAxis ? 1 : 0;
	m *= strokeSize;
	for (int x = v1[axis]; x < v2[axis]; x+=strokeSize) {
		error = error + m - strokeSize;
		if (invertAxis) {
			if (strokeSize > 1) {
				FillRectangle(window, v1[0] + y - strokeSize, x - strokeSize, v1[0] + y + strokeSize, x + strokeSize, color);
				if (error >= strokeSize) {
					for (int i = 1; i <= floor(error); i+= strokeSize) {
						FillRectangle(window, v1[0] + y + i - strokeSize, x - strokeSize, v1[0] + y + i + strokeSize, x + strokeSize, color);
					}
					
					error -= floor(error);
				}
			}
			else {
				window->SetPixelAt(v1[0] + y, x, color);
				
				if (error >= strokeSize) {
					for (int i = 1; i <= floor(error); i++) {
						window->SetPixelAt(v1[0] + y + i, x, color);
					}
					
					error -= floor(error);
				}
			}
			
		}
		else {
			if (strokeSize > 1) {
				FillRectangle(window, x - strokeSize, v1[1] + y - strokeSize, x + strokeSize, v1[1] + y + strokeSize, color);
				if (error >= strokeSize) {
					for (int i = 1; i <= floor(error); i+= strokeSize) {
						FillRectangle(window, x - strokeSize, v1[1] + y + i - strokeSize, x + strokeSize, v1[1] + y +i + strokeSize, color);
					}
					
					error -= floor(error);
				}
			}
			else {
				window->SetPixelAt(x, floor(v1[1] + y), color);

				if (error >= strokeSize) {
					
					for (int i = 1; i <= floor(error); i+= strokeSize) {
						window->SetPixelAt(x, floor(v1[1] + y) + i, color);
					}					
					error -= floor(error);
				}
			}
		}
		
		y += m;
	}
}


void Renderer::FillRectangle(Window* window, int xl, int yt, int xr, int yb, COLORREF color)
{
	for (int x = xl; x < xr; x++) {
		for (int y = yt; y < yb; y++) {
			window->SetPixelAt(x, y, color);
		}
	}
}
