#include "font.h"

Font::Font(HDC hDC, int iSize, LPCTSTR sFontName)
{
    iBase = glGenLists(96);
    hFont = CreateFont( -iSize,
                        0,
                        0,
                        0,
                        FW_BOLD,
                        FALSE,
                        FALSE,
                        FALSE,
                        ANSI_CHARSET,
                        OUT_TT_PRECIS,
                        CLIP_DEFAULT_PRECIS,
                        ANTIALIASED_QUALITY,
                        FF_DONTCARE | DEFAULT_PITCH,
                        sFontName);
    HFONT hOldFont = (HFONT)SelectObject(hDC, hFont);
    wglUseFontBitmaps(hDC, 32, 96, iBase);
    SelectObject(hDC, hOldFont);
    DeleteObject(hFont);
}

void Font::Print(float x, float y, const char *fmt, ...)
{
    char text[256];
    va_list	ap;

    if (fmt == NULL)
        return;

    va_start(ap, fmt);
        vsprintf(text, fmt, ap);
    va_end(ap);

    glRasterPos2f(x, y);
    glPushAttrib(GL_LIST_BIT);
        glListBase(iBase - 32);
        glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);
    glPopAttrib();
}

Font::~Font()
{
    glDeleteLists(iBase, 96);
}

