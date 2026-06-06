#include "Mouse.h"  

POINT Mouse::GetPosition()
{
	return position;
}

void Mouse::SetPosition(POINT pos)
{
	this->lastPosition.x = this->position.x;
	this->lastPosition.y = this->position.y;
	this->position.x = pos.x;
	this->position.y = pos.y;
}

void Mouse::SetPosition(int x, int y)
{
	this->lastPosition.x = this->position.x;
	this->lastPosition.y = this->position.y;
	this->position.x = x;
	this->position.y = y;
}

void Mouse::SetMouseDelta(float x, float y)
{
	this->delta[0] += x;
	this->delta[1] += y;
}

void Mouse::SetButton(int key)
{
	for (int i = 0; i < this->buttonCount; i++)
	{
		if (this->buttons[i].key == key)
		{
			this->buttons[i].set = true;
			return;
		}
	}

	for (int i = 0; i < this->buttonCount; i++)
	{
		if (this->buttons[i].key == -1)
		{
			this->buttons[i].key = key;
			this->buttons[i].set = true;
			return;
		}
	}
}

void Mouse::ResetButton(int key)
{
	for (int i = 0; i < this->buttonCount; i++)
	{
		if (this->buttons[i].key == key)
		{
			this->buttons[i].set = false;
			return;
		}
	}
}

void Mouse::EnableRawMouseInput(HWND hwnd)
{
	RAWINPUTDEVICE rid;
	rid.usUsagePage = 0x01; // HID_USAGE_PAGE_GENERIC
	rid.usUsage = 0x02;     // HID_USAGE_GENERIC_MOUSE
	rid.dwFlags = 0; // Receive input even when not in focus
	rid.hwndTarget = hwnd; // Handle to window

	RegisterRawInputDevices(&rid, 1, sizeof(rid));
}

void Mouse::GetMouseDelta(float* delta, bool resetDelta)
{
	delta[0] = this->delta[0];
	delta[1] = this->delta[1];
	if (resetDelta)
		ResetMouseDelta();
}

void Mouse::ResetMouseDelta()
{
	this->delta[0] = 0;
	this->delta[1] = 0;
}

bool Mouse::IsSet(int key)
{
	for (int i = 0; i < this->buttonCount; i++)
	{
		if (this->buttons[i].key == key)
		{
			return this->buttons[i].set;
		}
	}
	return false;
}

void Mouse::AddScroll(int scroll)
{
	this->scroll += scroll;
}

void Mouse::ClearScroll()
{
	this->scroll = 0;
}

int Mouse::GetScroll()
{
	return this->scroll;
}