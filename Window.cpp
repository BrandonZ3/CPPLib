#include "Window.h"  

Window::Window()
{

}

LRESULT CALLBACK Window::StdWindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{

	Window* window = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);

	switch (msg)
	{
	case(WM_CREATE):
	{
		CREATESTRUCT* cr = (CREATESTRUCT*)lParam;
		Window* w = (Window*)cr->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)w);
		break;
	}
	case(WM_KEYDOWN):
	{
		window->keyboard.SetKey(wParam);
		break;
	}
	case(WM_CHAR):
	{
		uint32_t val = (uint32_t)wParam;
		if (val < 128)
			window->typing->Add((uint8_t)val);
		break;
	}
	case(WM_ACTIVATE):
	{
		switch (wParam)
		{
		case(WA_ACTIVE):
		{
			window->SetFocused(true);
			break;
		}
		case(WA_INACTIVE):
		{
			window->SetFocused(false);
			break;
		}
		}

		return 0;
	}
	case(WM_KEYUP):
	{
		window->keyboard.ResetKey(wParam);
		break;
	}
	case(WM_MOUSEMOVE):
	{
		int x = lParam & 0xFFFF;
		int y = (lParam & 0xFFFF0000) >> 16;
		window->mouse.SetPosition(x, y);
		RECT pos;
		GetClientRect(window->GetHandle(), &pos);
		POINT topLeft = { pos.left, pos.top };
		if (ClientToScreen(window->GetHandle(), &topLeft) && window->centerMouse)
		{
			SetCursorPos(topLeft.x + window->GetWidth() / 2, topLeft.y + window->GetHeight() / 2);
			//window->mouse.SetMouseDelta((window->GetWidth() / 2) - x, (window->GetHeight() / 2) - y);
		}
		break;
	}
	case(WM_INPUT):
	{
		UINT dwSize;
		GetRawInputData((HRAWINPUT)lParam, RID_INPUT, nullptr, &dwSize, sizeof(RAWINPUTHEADER));
		BYTE* lpb = new BYTE[dwSize];
		if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) == dwSize) {
			RAWINPUT* raw = (RAWINPUT*)lpb;
			if (raw->header.dwType == RIM_TYPEMOUSE) {
				window->mouse.SetMouseDelta(raw->data.mouse.lLastX * -1, raw->data.mouse.lLastY * -1);
				/*int dx = raw->data.mouse.lLastX;
				int dy = raw->data.mouse.lLastY;*/
			}
		}
		delete[] lpb;

		return 0;
	}
	case(WM_LBUTTONDOWN):
	{
		int x = lParam & 0xFFFF;
		int y = (lParam & 0xFFFF0000) >> 16;
		window->mouse.SetPosition(x, y);
		window->mouse.SetButton(0);
		break;
	}
	case(WM_LBUTTONUP):
	{
		int x = lParam & 0xFFFF;
		int y = (lParam & 0xFFFF0000) >> 16;
		window->mouse.SetPosition(x, y);
		window->mouse.ResetButton(0);
		break;
	}
	case(WM_RBUTTONDOWN):
	{
		int x = lParam & 0xFFFF;
		int y = (lParam & 0xFFFF0000) >> 16;
		window->mouse.SetPosition(x, y);
		window->mouse.SetButton(1);
		break;
	}
	case(WM_RBUTTONUP):
	{
		int x = lParam & 0xFFFF;
		int y = (lParam & 0xFFFF0000) >> 16;
		window->mouse.SetPosition(x, y);
		window->mouse.ResetButton(1);
		break;
	}
	case(WM_MBUTTONDOWN):
	{
		int x = lParam & 0xFFFF;
		int y = (lParam & 0xFFFF0000) >> 16;
		window->mouse.SetPosition(x, y);
		window->mouse.SetButton(2);
		break;
	}
	case(WM_MBUTTONUP):
	{
		int x = lParam & 0xFFFF;
		int y = (lParam & 0xFFFF0000) >> 16;
		window->mouse.SetPosition(x, y);
		window->mouse.ResetButton(2);
		break;
	}
	case(WM_XBUTTONDOWN):
	{
		int key = (wParam & 0xFFFF0000) >> 16;
		int x = lParam & 0xFFFF;
		int y = (lParam & 0xFFFF0000) >> 16;
		window->mouse.SetPosition(x, y);
		window->mouse.SetButton(key);
		break;
	}
	case(WM_XBUTTONUP):
	{
		int key = (wParam & 0xFFFF0000) >> 16;
		int x = lParam & 0xFFFF;
		int y = (lParam & 0xFFFF0000) >> 16;
		window->mouse.SetPosition(x, y);
		window->mouse.ResetButton(key);
		break;
	}
	case(WM_MOUSEWHEEL):
	{
		int16_t wd = ((wParam >> 0x10) & 0xFFFF);
		int scrolls = wd / WHEEL_DELTA;
		window->mouse.AddScroll(scrolls);
		break;
	}
	case(WM_PAINT):
	{
		break;
	}
	case(WM_DESTROY):
	{
		window->Stop();
		PostQuitMessage(0);
		return 0;
	}
	case(WM_SIZE):
	{
		RECT* windowBounds = (RECT*)lParam;
		window->UpdateSizeValues();
		return 0;
	}
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void Window::Init(HINSTANCE hinst, int width, int height, WNDPROC wndProc, void (*runcallback)())
{
	this->userWndProc = wndProc;
	WNDCLASSEXW windowClass = {};
	windowClass.cbSize = sizeof(WNDCLASSEXW);
	windowClass.hInstance = hinst;
	windowClass.lpszClassName = this->className;
	windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.lpfnWndProc = Window::StdWindowProcedure;

	RegisterClassExW(&windowClass);

	this->width = width;
	this->height = height;
	this->handle = CreateWindow(this->className, this->title, WS_OVERLAPPEDWINDOW, 0, 0, width, height, NULL, NULL, hinst, this);

	if (handle)
	{
		this->controls = (HWND*)malloc(sizeof(HWND*) * 200);
		ShowWindow(this->handle, SW_SHOW);
		this->allowrunning = true;
		this->callback = runcallback;
	}
	else
		throw "Failed To Create Window";
}

void Window::Stop()
{
	this->allowrunning = false;
}

void Window::Run()
{
	MSG msg = {};

	while (this->allowrunning)
	{
		while (true)
		{
			msg = {};
			PeekMessageW(&msg, this->handle, NULL, NULL, PM_REMOVE);

			if (msg.message == NULL)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (this->callback)
			this->callback();
		std::chrono::steady_clock::time_point now = std::chrono::high_resolution_clock::now();
		delta = std::chrono::duration_cast<std::chrono::microseconds>(now - before).count() / 1000000.0f;
		this->before = now;
	}
}

HWND Window::GetHandle()
{
	return this->handle;
}

UINT Window::GetControlCount()
{
	return this->controlCount;
}

HWND Window::GetControl(POINT point)
{
	for (int i = 0; i < this->controlCount; i++)
	{
		RECT cRect = this->GetControlRect(i);

		if (point.x >= cRect.left && point.x <= cRect.right)
			if (point.y >= cRect.top && point.y <= cRect.bottom)
				return this->controls[i];
	}
	return NULL;
}

HWND Window::GetControl(int index)
{
	if (index >= 0 && index <= this->controlCount - 1)
	{
		return this->controls[index];
	}
	return NULL;
}

bool Window::AddControl(HWND control)
{
	if (control)
	{
		this->controls[this->controlCount] = control;
		ShowWindow(control, SW_SHOW);
		this->controlCount++;
		return true;
	}
	return false;
}

RECT Window::GetControlRect(int index)
{
	RECT controlRect = {};
	if (index >= 0 && index <= this->controlCount - 1)
	{
		GetWindowRect(this->controls[index], &controlRect);
		MapWindowPoints(NULL, this->handle, (LPPOINT)&controlRect, 2);
		return controlRect;
	}
	return controlRect;
}

bool Window::SetControlPosition(int index, int x, int y)
{
	if (index >= 0 && index <= this->controlCount - 1)
	{
		SetWindowPos(this->controls[index], NULL, x, y, 0, 0, SWP_NOSIZE);
		return true;
	}
	return false;
}

void Window::HideControl(int index)
{
	if (index >= 0 && index <= this->controlCount - 1)
	{
		ShowWindow(this->controls[index], SW_HIDE);
	}
}

void Window::ShowControl(int index)
{
	if (index >= 0 && index <= this->controlCount - 1)
	{
		ShowWindow(this->controls[index], SW_SHOW);
	}
}

int Window::GetWidth()
{
	return this->width;
}

int Window::GetHeight()
{
	return this->height;
}

float Window::GetFrameDelta(float max)
{
	if (delta > max)
		return max;
	return this->delta;
}

void Window::SetFocused(bool focused)
{
	this->focused = focused;
}

bool Window::GetFocused()
{
	return this->focused;
}

void Window::EnableCenterMouse()
{
	this->centerMouse = true;
}

void Window::DisableCenterMouse()
{
	this->centerMouse = false;
}

void Window::UpdateSizeValues()
{
	RECT rect;
	GetClientRect(this->GetHandle(), &rect);
	this->width = rect.right - rect.left;
	this->height = rect.bottom - rect.top;
}

Window::~Window()
{
	for (int i = 0; i < this->controlCount; i++)
	{
		DestroyWindow(this->controls[i]);
	}
	DestroyWindow(this->handle);
	free(this->controls);
	delete typing;
}
