#ifndef TEXTURE_H
#define TEXTURE_H

#include "stb_image.h"
#include <iostream>
#include <Windows.h>

enum class WrappingMode
{
    CLAMP_TO_EDGE = 0,
    REPEAT
};

class Texture
{
public:
    // --------------------------------
    //  Constructors
    // --------------------------------
    
    Texture(const char* filename);

    // --------------------------------
    //  Constants
    // --------------------------------

    // --------------------------------
    //  Functions
    // --------------------------------
    
    void SetWrappingMode(const WrappingMode r_wrapping_mode) noexcept;
    WrappingMode GetWrappingMode() noexcept;

    COLORREF GetColorAtUV(float r_u, float r_v) noexcept;

private:
    // --------------------------------
    //  Constants
    // --------------------------------
    
    // --------------------------------
    //  Variables
    // --------------------------------

    unsigned char* mp_data;

    int m_width;
    int m_height;
    int m_channels;

    WrappingMode m_wrapping_mode;

    // --------------------------------
    //  Functions
    // --------------------------------
};

#endif // !TEXTURE_H



