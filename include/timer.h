#ifndef DEF_TIMER
#define DEF_TIMER

#include "img.h"

class Timer
{
public:
    Timer();
    ~Timer();

    Uint32 getTick();
    bool isStart();
    bool isPause();

    void start();
    void stop();
    void pause();
    void unPause();

private:
    Uint32 startTime, pauseTime;
    bool started;
    bool paused;
};

#endif