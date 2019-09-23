#include "stdafx.h"
#include "MainWin.h"

using namespace JN::FrontEnd::Zeus::Win32::Windows;
using namespace JN::Framework::GUI::Win32;

int colorIndex;
void timer_start(HWND *hwnd, bool *isQuitting, bool *isVisible, unsigned int interval);
void PaintSquare(HDC hdc, RECT *rect);

MainWin::MainWin(HINSTANCE hInstance, int iCmdShow) :
	BaseWindow(hInstance, iCmdShow)
{
	timer_start(&(this->Win32WindowInfo->hwnd), &(this->WindowInfo->IsQuitting), &(this->WindowInfo->IsVisible), 1000);
}


LPARAM MainWin::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam) {
	switch (message)
	{
	case WM_USER:
		this->OnUser(hwnd, wParam, lparam);
	}
	return BaseWindow::WndProc(hwnd, message, wParam, lparam);
}

LPARAM MainWin::OnPaint(HWND hwnd) {
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	rect.top = rect.left = 0;
	rect.right = this->WindowInfo->ClientWidth;
	rect.bottom = this->WindowInfo->ClientHeight;

	hdc = BeginPaint(hwnd, &ps);

	PaintSquare(hdc, &rect);

	EndPaint(hwnd, &ps);
	return 0;
};

LPARAM MainWin::OnUser(HWND hwnd, WPARAM wParam, LPARAM lparam) {
	InvalidateRect(hwnd, NULL, FALSE);
	return 0;
}


void PaintSquare(HDC hdc, RECT *rect)
{
	//SelectObject(hdc, GetStockObject(HOLLOW_BRUSH));
	//SelectObject(hdc, GetStockObject(DC_BRUSH));
	SelectObject(hdc, GetStockObject(colorIndex % 4));
	//SetDCBrushColor(hdc, RGB(255, 0, 0));

	Rectangle(
		hdc,
		rect->left + 10, // left
		rect->top + 10, // top
		rect->right - 10, // right
		rect->bottom - 10 // bottom
	);

	//rect = ps.rcPaint; // is the invalidated area
	RECT square = {
		rect->left + 25, // left
		rect->top + 25, // top
		rect->right - 25, // right
		rect->bottom - 25 // bottom
	};

	HBRUSH brush = static_cast<HBRUSH>(GetStockObject(LTGRAY_BRUSH));
	FillRect(hdc, &square, brush);

	HGDIOBJ originalPen = SelectObject(hdc, GetStockObject(DC_PEN));
	HGDIOBJ originalBrush = SelectObject(hdc, GetStockObject(DC_PEN));

	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB(0, 0, 255));

	SelectObject(hdc, GetStockObject(DC_PEN));
	SetDCPenColor(hdc, RGB(0, 255, 255));

	MoveToEx(hdc, 0, 0, nullptr);
	LineTo(hdc, 50, 50);

	SelectObject(hdc, originalBrush);
	SelectObject(hdc, originalPen);

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0, 255, 0));

	DrawText(
		hdc,
		TEXT("Hello, Windows 10.0!"),
		-1,
		rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER
	);
}


void timer_start(HWND *hwnd, bool *isQuitting, bool *isVisible, unsigned int interval)
{
	std::thread([hwnd, isQuitting, isVisible, interval]() {
		while (!*isQuitting)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
			if (*hwnd && *isVisible) {
				colorIndex++;
				PostMessage(*hwnd, WM_USER, 0, 0);
				//PostMessage(*hwnd, WM_SYSCOMMAND, SC_TASKLIST, 0);
				//PostMessage(*hwnd, WM_SYSCOMMAND, SC_SCREENSAVE, 0);
				//PostMessage(*hwnd, WM_SYSCOMMAND, SC_CONTEXTHELP, 0);
				//PostMessage(*hwnd, WM_SYSCOMMAND, SC_MONITORPOWER, 1); // low power | 2 off | -1 on
				//PostMessage(*hwnd, WM_SYSCOMMAND, SC_MOUSEMENU, 0);
			}
		}
	}).detach();
}