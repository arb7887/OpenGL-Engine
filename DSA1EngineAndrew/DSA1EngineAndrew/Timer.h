#pragma once
#include <ctime>

class Timer
{
private:
	clock_t cur, prev;
public:
	float t, dt, fps;
	Timer();
	~Timer();
	void Update();
};

