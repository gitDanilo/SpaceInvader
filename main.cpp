#define WIN32_LEAN_AND_MEAN

#include "glwindow.h"
#include "fps.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    MSG msg;

    OutputDebugStringA("Starting CG-N4\n");

    GLWindow mWnd(L"CG:N4", hInstance); // Full Screen Window
    if (mWnd.Init() == FALSE) return 1;

    do
    {
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else mWnd.Display();

    } while (msg.message != WM_QUIT);

    return 0;
}
