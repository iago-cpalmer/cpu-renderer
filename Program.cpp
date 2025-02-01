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
    Vertex v2{ gmtl::Vec3f(100, 300, 0),    gmtl::Vec3f(255,0,0), gmtl::Vec2f(0.25f,1.0f) };
    Vertex v3{ gmtl::Vec3f(500, 200, 0),    gmtl::Vec3f(0,255,0), gmtl::Vec2f(0.75f,1.0f) };

    Texture texture = Texture("res/test.jpg");
    texture.SetWrappingMode(WrappingMode::REPEAT);

    // --------------------------------
    // Main Loop
    // --------------------------------

    bool windowShouldClose = false;
    while (!windowShouldClose) {
        // Process messages
        if (!pWindow->ProcessMessages()) {
            windowShouldClose = true;
        }

        renderer.FillTriangle(pWindow, v1, v2, v3, &texture);        
    }

    // --------------------------------
    // End
    // --------------------------------

    delete pWindow;
}
