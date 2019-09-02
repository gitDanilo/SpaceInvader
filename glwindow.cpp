#include "glwindow.h"

GLWindow::GLWindow(LPCWSTR wsWndName, HINSTANCE hInst)
{
    sWndName = wsWndName;
    hInstance = hInst;

    // Get current resolution
    HWND hDesktop = GetDesktopWindow();
    HDC hdcTmp = GetDC(hDesktop);
    iHeight = GetDeviceCaps(hdcTmp, PLANES) * GetDeviceCaps(hdcTmp, VERTRES);
    iWidth = GetDeviceCaps(hdcTmp, PLANES) * GetDeviceCaps(hdcTmp, HORZRES);
    OrthoW = iWidth / 2.0f;
    OrthoH = iHeight / 2.0f;
    ReleaseDC(hDesktop, hdcTmp);
}

GLWindow::~GLWindow()
{
    OutputDebugStringA("GLWindow::~WindwGL()\n");
    delete font;
    UnregisterClass(WC.lpszClassName, hInstance);
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
    DeleteDC(hDC);
}

bool GLWindow::Init()
{
    OutputDebugStringA("GLWindow::Init()\n");

    DWORD dwWndStyle = WS_POPUP;
    DWORD dwWndExStyle = WS_EX_APPWINDOW; // | WS_EX_TOPMOST

    // Register a window class
    ZeroMemory(&WC, sizeof(WNDCLASS));
    WC.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    WC.lpfnWndProc = sWndProc;
    WC.cbClsExtra = 0;
    WC.cbWndExtra = 0;
    WC.hInstance = hInstance;
    WC.hIcon = NULL;
    WC.hCursor = LoadCursor(NULL, IDC_ARROW);
    WC.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    WC.lpszMenuName = NULL;
    WC.lpszClassName = sWndName;
    if (RegisterClass(&WC) == 0)
    {
        MessageBox(HWND_DESKTOP, L"RegisterClass Failed!", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    // Create window
    hWnd = CreateWindowEx(dwWndExStyle, sWndName, sWndName, dwWndStyle, 0, 0, iWidth, iHeight, HWND_DESKTOP, NULL, hInstance, NULL);
    if (hWnd == 0)
    {
        MessageBox(HWND_DESKTOP, L"CreateWindowEx Failed!", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }
    SetWindowLong(hWnd, GWLP_USERDATA, (long)this);

    // Set pixel format
    PIXELFORMATDESCRIPTOR pfd;
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    //Enable OpenGL
    hDC = GetDC(hWnd);

    SetPixelFormat(hDC, ChoosePixelFormat(hDC, &pfd), &pfd);

    hRC = wglCreateContext(hDC);

    wglMakeCurrent(hDC, hRC);

    Reshape();

    font = new Font(hDC, 16, L"Courier New");
    gameover_font = new Font(hDC, 72, L"Courier New");
    oldTicks = fps.TimerGetTime();

    GamePaused = false;

    scene.Init();

    ShowWindow(hWnd, SW_NORMAL);
    return TRUE;
}

void GLWindow::Reshape()
{
    glViewport(0, 0, (GLsizei)iWidth, (GLsizei)iHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, ((GLdouble)iWidth / (GLdouble)iHeight), 0.1, 200);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

LRESULT CALLBACK GLWindow::sWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    GLWindow *tmp = (GLWindow*)GetWindowLong(hWnd, GWLP_USERDATA);
    if (tmp == NULL) return DefWindowProc(hWnd, uMsg, wParam, lParam);
    return tmp->WndProc(hWnd, uMsg, wParam, lParam);
}

int GLWindow::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    static bool bBlocking;
    static double old_x;
    static double old_y;
    switch (uMsg)
    {
        case WM_CREATE:
            old_x = 0;
            old_y = 0;
            return 0;
        case WM_SIZE:
            iWidth = LOWORD(lParam);
            iHeight = HIWORD(lParam);
            Reshape();
            return 0;
        case WM_LBUTTONDOWN:
            SetCapture(hWnd);
            bBlocking = true;
            old_x = LOWORD(lParam);
            old_y = - HIWORD(lParam);
            return 0;
        case WM_LBUTTONUP:
            if (bBlocking)
            {
                old_x = 0;
                old_y = 0;
                ReleaseCapture();
                bBlocking = false;
                InvalidateRect(hWnd, NULL, TRUE);
            }
            return 0;
        case WM_MOUSEMOVE:
            if (bBlocking)
            {
                scene._DebugCamera(25.0, (LOWORD(lParam) - old_x) * 0.1f, ((- HIWORD(lParam)) - old_y) * 0.1f);
                old_x = LOWORD(lParam);
                old_y = - HIWORD(lParam);
            }
            return 0;
        case WM_CLOSE:
            DestroyWindow(hWnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_KEYDOWN:
            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                    return 0;
                case 0x41: // A
                    if (GamePaused == false) scene.SetKeyDown(41, TRUE);

                    return 0;
                case 0x44: // D
                    if (GamePaused == false) scene.SetKeyDown(44, TRUE);

                    return 0;
                case 0x50: // P
                    GamePaused = !GamePaused;
                    return 0;
                case VK_SPACE:
                    if (GamePaused == false) scene.SetKeyDown(20, TRUE);
                    return 0;
                case VK_RETURN:
                    if (scene.GetLives() <= 0) scene.Init();
                    return 0;
                default:
                    return 0;
            }
    case WM_KEYUP:
        switch (wParam)
        {
            case 0x41: // A
                if (GamePaused == false) scene.SetKeyDown(41, FALSE);
                return 0;
            case 0x44: // D
                if (GamePaused == false)scene.SetKeyDown(44, FALSE);
                return 0;
            case VK_SPACE:
                if (GamePaused == false) scene.SetKeyDown(20, FALSE);
                return 0;
            default:
                return 0;
        }

        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
}

void GLWindow::Display()
{
    if (GamePaused == FALSE)
    {
        // SEMIFIXED timestep
        double newTicks = fps.TimerGetTime();
        double frameTime = newTicks - oldTicks;
        oldTicks = newTicks;
        double totalDeltaTime = frameTime / DESIRED_FRAMETIME;
        for (int i = 0; totalDeltaTime > 0.0f && i < MAX_PHYSICS_STEPS; i++)
        {
            double deltaTime = (totalDeltaTime < MAX_DELTA_TIME ? totalDeltaTime : MAX_DELTA_TIME);
            // UPDATE PHYSICS
            scene.StepAnimation(newTicks, deltaTime);
            totalDeltaTime -= deltaTime;
        }
    }

    // UPDATE FPS
    fps.Update();

    // DRAW
    scene.Draw();

    // Draw debug info in ortho 2D mode
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, (double)iWidth, 0.0, (double)iHeight, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    if (scene.GetLives() <= 0)
    {
        glColor3f(0.0f, 1.0f, 1.0f);
        gameover_font->Print((iWidth / 2) - 180, iHeight / 2, "GAME OVER");
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    font->Print(10, 130, "lives    : %d", scene.GetLives());
    font->Print(10, 115, "score    : %d", scene.GetScore());
    if (GamePaused == false) font->Print(10,  85, "status   : running");
    else font->Print(10,  85, "status   : paused");
    font->Print(10,  70, "width    : %d", iWidth);
    font->Print(10,  55, "height   : %d", iHeight);
    font->Print(10,  40, "fps      : %3.2f", fps.GetFPS());
    font->Print(10,  25, "ang_alpha: %4.2f", scene._GetAlpha());
    font->Print(10,  10, "ang_beta : %4.2f", scene._GetBeta());

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    // SWAP BUFFERS
    SwapBuffers(hDC);
}
