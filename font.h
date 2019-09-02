#ifndef FONT_H
#define FONT_H

#include <windows.h>
#include <GL/gl.h>
#include <stdio.h>

class Font
{
private:
    HFONT hFont;
    unsigned int iBase;
public:
    void Print(float x, float y, const char *fmt, ...);
    Font(HDC hDC, int iSize, LPCTSTR sFontName);
    ~Font();
};

#endif // FONT_H
