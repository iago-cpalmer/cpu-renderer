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
    int x = u * width;
    int y = v * height;
    int index = (y * width + x) * channels;
    return RGB(Data[index + 0], Data[index + 1], Data[index + 2]);
}

