#include"Frame.h"

double GetFrameTime()
{
	static LARGE_INTEGER frequency;
	static BOOL initialized = FALSE;
	static LARGE_INTEGER prevTime;

	if (!initialized)
	{
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&prevTime);
		initialized = TRUE;
	}

	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	double frameTime = static_cast<double>(currentTime.QuadPart - prevTime.QuadPart) / frequency.QuadPart;
	prevTime = currentTime;

	return frameTime;
}