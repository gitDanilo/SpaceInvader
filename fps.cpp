#include "fps.h"

FPS::FPS()
{
    ZeroMemory(&timer, sizeof(TIMER));
    ZeroMemory(&TimePerFrame, sizeof(8 * 10));
    fps = 0;
    fpsavr = 0;
    ms = 0;
    ms10 = 0;
    msTotal = 0;
    oldTime = 0;
    intermede_ms = 0;
    intermede = false;
    fpsTotal = 0;
    totalFrameCount = 0;
    if (QueryPerformanceFrequency((LARGE_INTEGER *) &timer.frequency))
    {
        QueryPerformanceCounter((LARGE_INTEGER *) &timer.performance_timer_start);
        timer.performance_timer = TRUE;
        timer.resolution = (double)(((double)1.0f)/((double)timer.frequency));
        timer.performance_timer_elapsed = timer.performance_timer_start;
    }
    else
    {
        timer.performance_timer = FALSE;
        timer.mm_timer_start = timeGetTime();
        timer.resolution = 1.0f / 1000.0f;
        timer.frequency = 1000;
        timer.mm_timer_elapsed = timer.mm_timer_start;
    }

}

FPS::~FPS()
{

}

void FPS::Reset()
{

}

double FPS::TimerGetTime()
{
    __int64 time;

    if (timer.performance_timer)
    {
        QueryPerformanceCounter((LARGE_INTEGER *) &time);

        // Return The Current Time Minus The Start Time Multiplied By The Resolution And 1000 (To Get MS)
        return ( (double) ( time - timer.performance_timer_start) * timer.resolution)*1000.0f;
    }
    else
        // Return The Current Time Minus The Start Time Multiplied By The Resolution And 1000 (To Get MS)
        return( (double) ( timeGetTime() - timer.mm_timer_start) * timer.resolution)*1000.0f;
}

void FPS::Update()
{
    // Calculate MS
    ms = (double)TimerGetTime() - oldTime;
    oldTime = (double)TimerGetTime();
    if (ms > 100) ms = 100;
    msTotal += ms;

    // Calculate FPS
    int loop;							// Used for FOR loop
    for (loop = 0; loop < 9; loop++) TimePerFrame[loop] = TimePerFrame[loop + 1];

    TimePerFrame[9] = ms;					// Store most recent ms per frame
    fps = 0;								// Reset fps variable
    for (loop = 0; loop < 10; loop++)			// Total past 10 records
    {
        fps += TimePerFrame[loop];
    }
    fps = fps / 10.0f;				// Find mean average ms per frame of last ten frames

    ms10 = fps;						// Average ms of the past 10 frames

    if (intermede == false)
        intermede_ms = fps;

    fps	= 1000.0f / fps;

    // Calculate Average FPS
    totalFrameCount++;
    fpsTotal += (DWORD)fps;
    fpsavr = (double)(fpsTotal / (double)totalFrameCount);
}


double FPS::GetFPS()
{
    return fps;
}

double FPS::getMS()
{
    return ms;
}
