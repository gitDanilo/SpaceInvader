#ifndef GLWindow_H
#define GLWindow_H

#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "font.h"
#include "fps.h"
#include "scene.h"

#define DESIRED_FRAMETIME 16.666666666666666666666666666667 // MS_PER_SECOND / DESIRED_FPS -> 1000 / 60
#define MAX_PHYSICS_STEPS 5
#define MAX_DELTA_TIME    1.0f

class GLWindow
{
private:
    WNDCLASS WC;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    HINSTANCE hInstance;
    LPCWSTR sWndName;
    Font *font;
    Font *gameover_font;
    int iHeight;
    int iWidth;
    float OrthoW;
    float OrthoH;
    Scene scene;
    FPS fps;
    double oldTicks;
    bool GamePaused;
    void Reshape();
    static LRESULT CALLBACK sWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    int WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
public:
    bool Init();
    void Display();
    GLWindow(LPCWSTR wsWndName, HINSTANCE hInst);
    ~GLWindow();
};

#endif // GLWindow_H
