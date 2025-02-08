// CPURenderer.cpp 
#include <iostream>

#include <chrono>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Window.h"
#include "Texture.h"
#include "Renderer.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 800

int main()
{
    // --------------------------------
    // Window & Renderer initialization
    // --------------------------------

    Window* pWindow = new Window(WINDOW_WIDTH, WINDOW_HEIGHT);
    GraphicBuffers graphicBuffers = GraphicBuffers(WINDOW_WIDTH, WINDOW_HEIGHT);
    pWindow->SetGraphicBuffers(&graphicBuffers);

    Renderer renderer = Renderer();
    renderer.SetGraphicBuffers(&graphicBuffers);

    // --------------------------------
    // Other Initializations
    // --------------------------------

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

    /*
    renderer.SetClippingEnabled(false);
    renderer.DrawRect(rect, RGB(0, 0, 255));
    renderer.SetClippingEnabled(true);*/

   // renderer.DrawLine(pWindow, v6.Position, v7.Position, RGB(255, 0, 0), 1);

    Mesh mesh = Mesh(3, 3);
    mesh.AddVertex(v1);
    mesh.AddVertex(v2);
    mesh.AddVertex(v3);
    mesh.AddIndex(0);
    mesh.AddIndex(1);
    mesh.AddIndex(2);

    Mesh mesh2 = Mesh(3, 3);
    mesh2.AddVertex(v4);
    mesh2.AddVertex(v5);
    mesh2.AddVertex(v6);
    mesh2.AddIndex(0);
    mesh2.AddIndex(1);
    mesh2.AddIndex(2);

    // --------------------------------
    // Main Loop
    // --------------------------------

    auto prevTime = std::chrono::high_resolution_clock::now();
    double deltaTime = 0.0;
    int frameCounter = 0;

    bool windowShouldClose = false;
    while (!windowShouldClose) {

        // FPS Handling
        auto currentTime = std::chrono::high_resolution_clock::now();
        deltaTime = std::chrono::duration<double>(currentTime - prevTime).count(); // Convert to seconds
        prevTime = currentTime;
        frameCounter = (frameCounter + 1) % 10;
        if (frameCounter == 0)
        {
            printf("FPS: %f \n", (1.0f / deltaTime));
        }

        // Process messages
        if (!pWindow->ProcessMessages()) {
            windowShouldClose = true;
        }

        // Update
        

        // Render
        graphicBuffers.Clear(RGB(255, 0, 255));

        renderer.RenderMesh(&mesh);
        renderer.RenderMesh(&mesh2);
        renderer.Render();

        graphicBuffers.Swap();
        pWindow->FinishRendering();
        /*
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
        renderer.DrawLine(pWindow, v6.Position, v7.Position, RGB(0, 255, 0), 1);*/
    }

    // --------------------------------
    // End
    // --------------------------------

    delete pWindow;
}
