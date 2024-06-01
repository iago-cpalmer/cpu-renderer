// CPURenderer.cpp 
#include <iostream>
#include "Window.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Texture.h"
#include "Renderer.h"
int main()
{
    Window* pWindow = new Window();

    Renderer* renderer = new Renderer();

    bool windowShouldClose = false;

    
    Vertex v1{ gmtl::Vec3f(300, 400, 0), gmtl::Vec3f(0,0,255), gmtl::Vec2f(0.5f,1.0f)};
    Vertex v2{ gmtl::Vec3f(100, 50, 0), gmtl::Vec3f(255,0,0), gmtl::Vec2f(0.0f,0.0f) };
    Vertex v3{ gmtl::Vec3f(500, 50, 0), gmtl::Vec3f(0,255,0), gmtl::Vec2f(1.0f,0.0f) };

    // load texture
    int width, height, channels;
    //unsigned char* texture = nullptr;
    
    Texture* texture = new Texture("res/test.jpg");


    renderer->FillTriangle(pWindow, v1, v2, v3, texture);

    while (!windowShouldClose) {
        // Process messages
        if (!pWindow->ProcessMessages()) {
            windowShouldClose = true;
        }

        renderer->FillTriangle(pWindow, v1, v2, v3, texture);        
    }

    delete pWindow;
}
