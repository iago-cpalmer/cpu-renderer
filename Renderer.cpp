#include "Renderer.h"


Renderer::Renderer()
{
}

void Renderer::FillTriangleTopFlat(Window* window, gmtl::Vec3f v1, gmtl::Vec3f v2, gmtl::Vec3f v3)
{
	// v2.y == v1.y
	float m23 = (v2[1] - v3[1]) / abs(v2[0] - v3[0]);
	float m13 = (v1[1] - v3[1]) / abs(v1[0] - v3[0]);

	float error = 0;
	for (int y = floor(v2[1]); y <= floor(v3[1]); y++) {

		float xif = (v2[0] > v3[0] ? 1 : -1) * floor((y - floor(v2[1])) / m23) + v2[0];
		float xff = (v1[0] > v3[0] ? 1 : -1) * floor((y - floor(v2[1])) / m13) + v1[0];

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
		for (int i = xi; i <= xf; i++) {
			window->SetPixelAt(i, y, COLOR_BLACK);
		}
	}
}

void Renderer::FillTriangleBottomFlat(Window* window, gmtl::Vec3f v1, gmtl::Vec3f v2, gmtl::Vec3f v3)
{
	// v2.y == v3.y
	float m21 = (v2[1] - v1[1]) / abs(v2[0] - v1[0]);
	float m31 = (v3[1] - v1[1]) / abs(v3[0] - v1[0]);

	float error = 0;
	for (int y = floor(v2[1]); y >= floor(v1[1]); y--) {

		float xif = (v2[0] > v1[0] ? 1 : -1) * (y - (v2[1])) / m21 + v2[0];
		float xff = (v3[0] > v1[0] ? 1 : -1) * (y - (v2[1])) / m31 + v3[0];

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

void Renderer::FillTriangle(Window* window, gmtl::Vec3f v1, gmtl::Vec3f v2, gmtl::Vec3f v3) {
	
	SortVertices(&v1, &v2, &v3);	
	std::cout << v1 << ", " << v2 << ", " << v3 << std::endl;
	if (v2[1] == v3[1]) {
		FillTriangleBottomFlat(window, v1, v2, v3);
	}
	else if (v2[1] == v1[1]) {
		FillTriangleTopFlat(window, v1, v2, v3);
	}
	else {
		// Split in 2
		
		float m = (v3[1] - v1[1]) / abs(v3[0]-v1[0]);
		//float x = (v3[0] > v1[0] ? v1[0] : v3[0]) + floor((v3[1]-v2[1]) / m);
		float x = 0;
		if (v3[0] > v1[0]) {
			x = v1[0] + floor((v2[1] - v1[1]) / m);
		} else {
			x = v3[0] + floor((v3[1] - v2[1]) / m);
		}
		gmtl::Vec3f p(x, v2[1], v3[2]); // TODO: Compute x & z values from v1-v3 depending on height (v2.y)
		FillTriangleBottomFlat(window, v1, v2, p);
		FillTriangleTopFlat(window, p, v2, v3);
	}
	
}

void Renderer::SortVertices(gmtl::Vec3f* v1, gmtl::Vec3f* v2, gmtl::Vec3f* v3) {
	// Sort vertices so v1.y<=v2.y<=v3.y
	gmtl::Vec3f aux;
	if ((*v1)[1] > (*v2)[1] && (*v1)[1] > (*v3)[1]) {
		aux = *v1;
		*v1 = *v3;
		*v3 = aux;
		if ((*v1)[1] > (*v2)[1]) {
			aux = *v1;
			*v1 = *v2;
			*v2 = aux;
		}
	}
	else if ((*v2)[1] > (*v1)[1] && (*v2)[1] > (*v3)[1]) {
		aux = *v2;
		*v2 = *v3;
		*v3 = aux;
		if ((*v1)[1] > (*v2)[1]) {
			aux = *v1;
			*v1 = *v2;
			*v2 = aux;
		}
	}
	else if ((*v1)[1] > (*v2)[1]) {
		aux = *v1;
		*v1 = *v2;
		*v2 = aux;
	}

}

void Renderer::DrawWireframe(Window* window, gmtl::Vec3f v1, gmtl::Vec3f v2, gmtl::Vec3f v3)
{
	DrawLine(window, v1, v2, COLOR_RED, 1);
	DrawLine(window, v2, v3, COLOR_RED, 1);
	DrawLine(window, v3, v1, COLOR_RED, 1);
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
