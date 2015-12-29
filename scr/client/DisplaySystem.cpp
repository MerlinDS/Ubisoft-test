#include "stdafx.h"
#include "DisplaySystem.h"


DisplaySystem::DisplaySystem(LPCWSTR wcn, LPCWSTR tn, WorldManager& tm, 
	int w, int h, int _x, int _y):
	className(wcn), title(tn), threadManager(tm), 
	width(w), height(h), x(_x), y(_y) {}

DisplaySystem::~DisplaySystem()
{
	DebugOut("destroy");
	UnregisterClass(wndclass.lpszClassName, wndclass.hInstance);
	entities = nullptr;
}


void DisplaySystem::init(vector<Entity>* collection) {
	DebugOut("initialize");
	entities = collection;
	//create window class setup
	wndclass = {
		sizeof(WNDCLASSEX), CS_CLASSDC, DisplaySystem::WndProc, 0, 0,
		GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),
		LoadCursor(0,IDC_ARROW), HBRUSH(COLOR_WINDOW + 1),
		0, className, LoadIcon(0,IDI_APPLICATION)
	};
	createWindow();
}

int DisplaySystem::createWindow()
{
	if (window)
	{
		DebugOut("Window already exist");
		return -1;
	}

	if (RegisterClassEx(&wndclass))
	{
		window = CreateWindowEx(0,
			className, title,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			width,
			height,
			(HWND)NULL,
			(HMENU)NULL,
			GetModuleHandle(0),
			this);
	}
	//windows created successfully
	if (window)
	{
		DebugOut("New window created");
		ShowWindow(window, SW_SHOWDEFAULT);
		return 0;
	}
	return -1;
}

void DisplaySystem::tick(float delatTime)
{
	//track window procedures
	MSG msg;
	BOOL bRet = GetMessage(&msg, 0, 0, 0);
	if (bRet != 0)
	{
		if (bRet == -1)
		{
			// handle the error and possibly exit
		}
		else
			DispatchMessage(&msg);
	}
	//redraw on nex
	InvalidateRect(window, NULL, TRUE);
}
/*
Private region
*/
LRESULT CALLBACK DisplaySystem::_WndProc(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
{
	HDC hDC;
	PAINTSTRUCT Ps;
	switch (msg)
	{
	case WM_MOUSEMOVE:
		//To avoid blocking of WM_PAINT by mouse event, call window update to force redrawing
		UpdateWindow(window);
		break;
	case WM_PAINT:
		int x, y;
		hDC = BeginPaint(window, &Ps);
		//draw greed
		HPEN linePen;
		COLORREF lineColor;
		lineColor = RGB(255, 0, 0);
		linePen = CreatePen(PS_SOLID, 2, lineColor);
		SelectObject(hDC, linePen);
		//darw verticla line
		MoveToEx(hDC, this->x, 0, NULL);
		LineTo(hDC, this->x, this->y);
		//draw horisontal line
		MoveToEx(hDC, 0, this->y, NULL);
		LineTo(hDC, width, this->y);
		//draw entities
		lineColor = RGB(0, 0, 0);
		linePen = CreatePen(PS_SOLID, 1, lineColor);
		SelectObject(hDC, linePen);
		for (auto it = entities->begin(); it != entities->end(); it++)
		{
			x = (int)it->viewPosition.x;
			y = (int)it->viewPosition.y;
			Ellipse(hDC, x - 10, y - 10, x + 10, y + 10);
		}

		//end drawing
		EndPaint(window, &Ps);
		break;
	case WM_NCDESTROY:
		//terminate threads with simulation and close window
		threadManager.terminate();
		PostQuitMessage(0);
		window = NULL;
		return 0;
	}
	return DefWindowProc(window, msg, wp, lp);
}

/*
Static region
*/
LRESULT CALLBACK DisplaySystem::WndProc(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)
{
	//detect window creation
	if (msg == WM_NCCREATE)
	{
		SetWindowLongPtr(window, GWLP_USERDATA, (LONG_PTR)((CREATESTRUCT*)lp)->lpCreateParams);
		return TRUE;
	}
	//execute callback in class
	return ((DisplaySystem*)GetWindowLongPtr(window, GWLP_USERDATA))->_WndProc(window, msg, wp, lp);
}
