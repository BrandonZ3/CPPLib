#pragma once 
#include <Windows.h>

class MouseButton
{
public:
	int key = -1;
	bool set = false;
};

class Mouse
{
private:
	POINT lastPosition = { 0, 0 };
	POINT position = { 0, 0 };
	UINT buttonCount = 50;
	MouseButton buttons[50];
	float delta[2] = { 0, 0 };
	int scroll = 0;
public:
	POINT GetPosition();

	void SetPosition(POINT pos);

	void SetPosition(int x, int y);

	void SetMouseDelta(float x, float y);

	void SetButton(int key);

	void ResetButton(int key);

	void EnableRawMouseInput(HWND hwnd);

	void GetMouseDelta(float* delta, bool resetDelta = true);

	void ResetMouseDelta();

	bool IsSet(int key);

	void AddScroll(int scroll);

	void ClearScroll();

	int GetScroll();
};
