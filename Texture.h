#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb_image.h"
#include <iostream>
#include "Window.h"

class Texture
{
public:
    unsigned char* Data;
    int width, height, channels;
    Texture(const char* filename);
    COLORREF GetColorAtUV(float u, float v);
};

#endif // !TEXTURE_H



