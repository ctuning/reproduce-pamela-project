#ifdef WINDOWS
#include <windows.h>

#include <time.h>

void win_usleep(__int64 usec) 
{ 
    HANDLE timer; 
    LARGE_INTEGER ft; 

    ft.QuadPart = -(10*usec); // Convert to 100 nanosecond interval, negative value indicates relative time

    timer = CreateWaitableTimer(NULL, TRUE, NULL); 
    SetWaitableTimer(timer, &ft, 0, NULL, NULL, 0); 
    WaitForSingleObject(timer, INFINITE); 
    CloseHandle(timer); 
}

double win_tock(void)
{ 

    LARGE_INTEGER xfrequency;
    LARGE_INTEGER xtime;

    if ((::QueryPerformanceFrequency(&xfrequency) != FALSE) && (::QueryPerformanceCounter(&xtime) != FALSE))
      return static_cast<double> (xtime.QuadPart)/xfrequency.QuadPart;
    else
      return (double)(clock()) / CLOCKS_PER_SEC;
}

#endif
