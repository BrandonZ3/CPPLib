#pragma once 
#include <Windows.h>
#include <chrono>

#include "Mouse.h"
#include "Keyboard.h"
#include "Dbuffer.h"

class Window
{
private:
	HWND handle = NULL;
	HWND* controls = NULL;
	UINT controlCount = 0;
	const wchar_t* className = L"Window 1";
	const wchar_t* title = L"Window 1";
	bool allowrunning = false;
	int width = 800;
	int height = 600;
	void (*callback)() = NULL;
	std::chrono::steady_clock::time_point before = std::chrono::high_resolution_clock::now();
	double delta = 0;
	bool focused = false;


public:
	bool centerMouse = false;
	Mouse mouse;
	Keyboard keyboard;
	DBuffer* typing = new DBuffer();;
	WNDPROC userWndProc = NULL;

	static LRESULT CALLBACK StdWindowProcedure(HWND, UINT, WPARAM, LPARAM);

	Window();

	void Init(HINSTANCE hinst, int width, int height, WNDPROC wndProc, void (*runcallback)());

	void Stop();

	void Run();

	HWND GetHandle();

	UINT GetControlCount();

	HWND GetControl(POINT point);

	HWND GetControl(int index);

	bool AddControl(HWND control);

	RECT GetControlRect(int index);

	bool SetControlPosition(int index, int x, int y);

	void HideControl(int index);

	void ShowControl(int index);

	int GetWidth();

	int GetHeight();

	float GetFrameDelta(float max);

	void SetFocused(bool focused);

	bool GetFocused();

	void EnableCenterMouse();

	void DisableCenterMouse();

	void UpdateSizeValues();

	~Window();
};