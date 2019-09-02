#ifndef FPS_H
#define FPS_H

#include <windows.h>

typedef struct _TIMER
{
    __int64			frequency;
    double			resolution;
    unsigned long	mm_timer_start;
    unsigned long	mm_timer_elapsed;
    bool			performance_timer;
    __int64			performance_timer_start;
    __int64			performance_timer_elapsed;
} TIMER, *PTIMER;

class FPS
{
private:
    TIMER timer;
    double fps;
    double fpsavr;
    double ms;
    double ms10;
    double msTotal;
    double oldTime;
    double TimePerFrame[10];
    double intermede_ms;
    bool intermede;
    DWORD fpsTotal;
    int totalFrameCount;
public:
    //double GetOldTick();
    double TimerGetTime();
    void Reset();
    void Update();
    double GetFPS();
    double getMS();
    FPS();
    ~FPS();
};

#endif // FPS_H
