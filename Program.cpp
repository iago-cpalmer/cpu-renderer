// CPURenderer.cpp 
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Window.h"
#include "Texture.h"
#include "Renderer.h"

int main()
{
    // --------------------------------
    // Window initialization
    // --------------------------------

    Window* pWindow = new Window();

    // --------------------------------
    // Other Initializations
    // --------------------------------

    Renderer renderer = Renderer();
    
    Vertex v1{ gmtl::Vec3f(300, 50, 0),     gmtl::Vec3f(0,0,255), gmtl::Vec2f(0.5f,0.0f) };
    Vertex v2{ gmtl::Vec3f(100, 400, 0),    gmtl::Vec3f(255,0,0), gmtl::Vec2f(0.25f,1.0f) };
    Vertex v3{ gmtl::Vec3f(600, 400, 0),    gmtl::Vec3f(0,255,0), gmtl::Vec2f(0.75f,3.0f) };

    Vertex v4{ gmtl::Vec3f(100, 400, 0),    gmtl::Vec3f(0,255,0), gmtl::Vec2f(0.75f,3.0f) };
    Vertex v5{ gmtl::Vec3f(300, 300, 0),    gmtl::Vec3f(0,255,0), gmtl::Vec2f(0.75f,3.0f) };

    Vertex v6{ gmtl::Vec3f(600, 300, 0),    gmtl::Vec3f(0,255,0), gmtl::Vec2f(0.75f,3.0f) };
    Vertex v7{ gmtl::Vec3f(100, 600, 0),    gmtl::Vec3f(0,255,0), gmtl::Vec2f(0.75f,3.0f) };
    
    Texture texture = Texture("res/test.jpg");
    texture.SetWrappingMode(WrappingMode::REPEAT);

    const Rect rect = { 200, 200, 300, 300 };
    renderer.SetClipRect(rect);

    renderer.SetClippingEnabled(false);
    renderer.DrawRect(pWindow, rect, RGB(0, 0, 255));
    renderer.SetClippingEnabled(true);

   // renderer.DrawLine(pWindow, v6.Position, v7.Position, RGB(255, 0, 0), 1);



    // --------------------------------
    // Main Loop
    // --------------------------------

    bool windowShouldClose = false;
    while (!windowShouldClose) {
        // Process messages
        if (!pWindow->ProcessMessages()) {
            windowShouldClose = true;
        }

        renderer.SetClippingEnabled(true);

        renderer.DrawLine(pWindow, v1.Position, v2.Position, RGB(255, 0, 0), 1);
        renderer.DrawLine(pWindow, v2.Position, v3.Position, RGB(255, 0, 0), 1);
        renderer.DrawLine(pWindow, v3.Position, v1.Position, RGB(255, 0, 0), 1);
        renderer.DrawLine(pWindow, v5.Position, v4.Position, RGB(255, 0, 0), 1);
        renderer.DrawLine(pWindow, v6.Position, v7.Position, RGB(255, 0, 0), 1);
        
        renderer.SetClippingEnabled(false);
        
        renderer.DrawLine(pWindow, v1.Position, v2.Position,    RGB(0, 255, 0), 1);
        renderer.DrawLine(pWindow, v2.Position, v3.Position,    RGB(0, 255, 0), 1);
        renderer.DrawLine(pWindow, v3.Position, v1.Position,    RGB(0, 255, 0), 1);
        renderer.DrawLine(pWindow, v5.Position, v4.Position,    RGB(0, 255, 0), 1);
        renderer.DrawLine(pWindow, v6.Position, v7.Position, RGB(0, 255, 0), 1);
    }

    // --------------------------------
    // End
    // --------------------------------

    delete pWindow;
}
