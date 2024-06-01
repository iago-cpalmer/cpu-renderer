#include "Texture.h"


Texture::Texture(const char* filename) {
    // Load image using stb_image
    Data = stbi_load(filename, &width, &height, &channels, 0);
    if (!Data) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        
    }
}

COLORREF Texture::GetColorAtUV(float u, float v)
{
    if (u > 1 ) {
        u = 1;
    }
    if (v > 1) {
        v = 1;
    }
    if (u < 0) {
        u = 0;
    }
    if (v < 0 ) {
        v = 0;
    }
    int x = u * (width-1);
    int y = v * (height-1);
    int index = (y * width + x) * channels;
    return RGB(Data[index + 0], Data[index + 1], Data[index + 2]);
}

