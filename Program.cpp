// CPURenderer.cpp 
#include <iostream>
#include "Window.h"
#include "Renderer.h"

int main()
{
    COLORREF blackColor = RGB(0, 0, 0);

    Window* pWindow = new Window();

    Renderer* renderer = new Renderer();

    bool windowShouldClose = false;

    

    gmtl::Vec3f v1(150, 150, 0);
    gmtl::Vec3f v2(100, 300, 0);
    gmtl::Vec3f v3(500, 360, 0);

    renderer->FillTriangle(pWindow, v1, v2, v3);

    while (!windowShouldClose) {
        // Process messages
        if (!pWindow->ProcessMessages()) {
            windowShouldClose = true;
        }

        renderer->FillTriangle(pWindow, v1, v2, v3);
        // Render commands
        /*
        for (int i = 0; i < 50; i++) {
            for (int j = 0; j < 50; j++) {
                pWindow->SetPixelAt(100+i, 100+j, blackColor);
            }
        }*/
        
    }

    delete pWindow;
}
