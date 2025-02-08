#include "GraphicsBuffer.h"

GraphicsBuffer CreateGraphicsBuffer(int r_width, int r_height)
{
    HDC hdcScreen = GetDC(NULL);

    BITMAPINFO bmi = {};
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = r_width;
    bmi.bmiHeader.biHeight = -r_height; // top-down
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = 32;
    bmi.bmiHeader.biCompression = BI_RGB;

    GraphicsBuffer gb;
    gb.Hbm = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, reinterpret_cast<void**>(&gb.Data), NULL, NULL);

    ReleaseDC(NULL, hdcScreen);
    return gb;
}

GraphicBuffers::GraphicBuffers(int r_width, int r_height)
    : m_width(r_width)
    , m_height(r_height)
    , m_current_buffer_at_front{0}
{
    
    for (size_t i = 0; i < TOTAL_BUFFERS; i++)
    {
        m_buffers[i] = CreateGraphicsBuffer(r_width, r_height);
    }
}

GraphicBuffers::~GraphicBuffers()
{
    for (size_t i = 0; i < TOTAL_BUFFERS; i++)
    {
        DeleteObject(m_buffers[i].Hbm);
    }
}
