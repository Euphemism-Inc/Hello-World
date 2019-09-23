#include "stdafx.h"
#include "BaseWindow.h"

using namespace JN::Framework::GUI;
using namespace JN::Framework::GUI::Win32;

// Constructor / Desctrucor
BaseWindow::BaseWindow(HINSTANCE hInstance, int iCmdShow) :
	Window::Window(),
	Win32WindowInfo(new JN::Framework::GUI::Win32::Win32WindowInfo())
{
	this->Win32WindowInfo->hInstance = hInstance;
	this->Win32WindowInfo->iCmdShow = iCmdShow;

	TCHAR* szAppName = new TCHAR[128];
	_tcscpy_s(szAppName, 127, TEXT("someName")); // TODO: returns errno_t 

	this->Win32WindowInfo->wndClass = createWndClass(hInstance, szAppName); // TODO: can be null -> GetLastError()
	this->Win32WindowInfo->isWinNT = this->initialize(this->Win32WindowInfo->wndClass);
}

BaseWindow::~BaseWindow() {
	if (this->Win32WindowInfo) {
		if (this->Win32WindowInfo->wndClass) {
			UnregisterClass(
				this->Win32WindowInfo->wndClass->lpszClassName,
				this->Win32WindowInfo->wndClass->hInstance
			);
			delete this->Win32WindowInfo->wndClass->lpszClassName;
			this->Win32WindowInfo->wndClass->lpszClassName = nullptr;

			delete this->Win32WindowInfo->wndClass;
			this->Win32WindowInfo->wndClass = nullptr;
		}
		delete this->Win32WindowInfo;
		this->Win32WindowInfo = nullptr;
	}
}

// BaseWindow Methods
WPARAM BaseWindow::Show(void) const {
	MSG msg;

	if (!this->Win32WindowInfo->isWinNT) {
		return 0;
	}

	this->WindowInfo->IsVisible = true;
	ShowWindow(this->Win32WindowInfo->hwnd, this->Win32WindowInfo->iCmdShow);
	UpdateWindow(this->Win32WindowInfo->hwnd);  // TODO: 0 -> fail (GetLastError()?)

	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


// Private Methods
WNDCLASS* BaseWindow::createWndClass(HINSTANCE hInstance, TCHAR szAppName[]) {
	WNDCLASS* wndclass = new WNDCLASS();

	wndclass->style = CS_HREDRAW | CS_VREDRAW; // Horizontal and Vertical size change? Redraw!
	wndclass->lpfnWndProc = wndProcInternal;
	wndclass->cbClsExtra = 0;
	wndclass->cbWndExtra = 0;
	wndclass->hInstance = hInstance;
	wndclass->hIcon = LoadIcon(nullptr, IDI_SHIELD);
	wndclass->hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndclass->hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)); // can be null (-> GetLastError()?)
	wndclass->lpszMenuName = nullptr;
	wndclass->lpszClassName = szAppName;

	return wndclass;
}

bool BaseWindow::initialize(WNDCLASS* wndclass) {
	if (!RegisterClass(wndclass)) // can be null -> GetLastError()
	{
		// If failed, szAppName could already be registered.
		MessageBox(nullptr, TEXT("This program requires Windows NT!"), wndclass->lpszClassName, MB_ICONERROR); // can be 0 -> GetLastError()
		return false;
	}

	this->Win32WindowInfo->hwnd = CreateWindow(	// can be null -> GetLastError()
		wndclass->lpszClassName,		  // window class name  
		TEXT("The Hello World Program"),  // window caption
		WS_OVERLAPPEDWINDOW,			  // window style
		CW_USEDEFAULT,					  // initial x position
		CW_USEDEFAULT,					  // initial y position
		CW_USEDEFAULT,					  // initial x size
		CW_USEDEFAULT,					  // initial y size
		NULL,							  // parent window handle
		NULL,							  // window menu handle
		this->Win32WindowInfo->hInstance, // program instance handle
		NULL);							  // creation parameters

	SetWindowLongPtr(this->Win32WindowInfo->hwnd, GWLP_USERDATA, reinterpret_cast<long>(this)); // can be 0 -> GetLastError()

	return true;
}


// Private (static) window functions

LPARAM CALLBACK BaseWindow::wndProcInternal(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	BaseWindow *baseWindowPtr = reinterpret_cast<BaseWindow *>(GetWindowLong(hwnd, GWLP_USERDATA)); // can be 0 -> GetLastError()

	if (baseWindowPtr == nullptr) {
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return baseWindowPtr->wndProc(hwnd, message, wParam, lParam);
}

LPARAM BaseWindow::WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	return DefWindowProc(hwnd, message, wParam, lParam);
}

LPARAM BaseWindow::wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message)
	{
		// https://autohotkey.com/docs/misc/SendMessageList.htm
	case WM_DESTROY: return this->onDestroy(hwnd, wParam, lParam);
	case WM_PAINT: return this->onPaint(hwnd, wParam, lParam);
	case WM_SHOWWINDOW: return this->onShow(hwnd, wParam, lParam);
	case WM_SIZE: return this->onSize(hwnd, wParam, lParam);
	case WM_SYSCOMMAND: return this->onSysCommand(hwnd, wParam, lParam);
	case WM_WINDOWPOSCHANGED: return this->onMoved(hwnd, wParam, lParam);

	case WM_GETFONT:
	case WM_SETFONT:
		return DefWindowProc(hwnd, message, wParam, lParam);

	case WM_GETTEXT:
	case WM_SETTEXT:
		return DefWindowProc(hwnd, message, wParam, lParam);

	case WM_SETFOCUS:
	case WM_KILLFOCUS:
		return DefWindowProc(hwnd, message, wParam, lParam);

	case WM_CHAR:
	case WM_DEADCHAR:
	case WM_HOTKEY:
	case WM_KEYDOWN:
	case WM_KEYUP:
		return DefWindowProc(hwnd, message, wParam, lParam);

	case WM_SYSDEADCHAR:
	case WM_SYSKEYDOWN:
	case WM_SYSKEYUP:
		return DefWindowProc(hwnd, message, wParam, lParam);

	case MN_GETHMENU:
	case WM_ERASEBKGND:
	case WM_GETTEXTLENGTH:
	case WM_SETICON:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return this->WndProc(hwnd, message, wParam, lParam);
}


LPARAM BaseWindow::OnClose(HWND hwnd) {
	return DefWindowProc(hwnd, WM_SYSCOMMAND, SC_CLOSE, 0);
}

LPARAM BaseWindow::onClose(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	this->WindowInfo->IsVisible = false;

	return this->OnClose(hwnd);
}


LPARAM BaseWindow::OnDestroy(HWND hwnd) {
	return DefWindowProc(hwnd, WM_DESTROY, 0, 0);
}

LPARAM BaseWindow::onDestroy(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	this->WindowInfo->IsQuitting = true;
	PostQuitMessage(0);

	return this->OnDestroy(hwnd);
}


LPARAM BaseWindow::OnMaximize(HWND hwnd) {
	return DefWindowProc(hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
}

LPARAM BaseWindow::onMaximize(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	this->WindowInfo->IsVisible = true;

	return this->OnMaximize(hwnd);
};


LPARAM BaseWindow::OnMinimize(HWND hwnd) {
	return DefWindowProc(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

LPARAM BaseWindow::onMinimize(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	this->WindowInfo->IsVisible = false;

	return this->OnMinimize(hwnd);
};


LPARAM BaseWindow::OnMove(HWND hwnd, int cursorX, int cursorY) {
	int usedMouse = cursorY > 0 ? 0x02 : 0x00;
	return DefWindowProc(hwnd, WM_SYSCOMMAND, SC_MOVE | usedMouse, MAKELONG(cursorX, cursorY));
}

LPARAM BaseWindow::onMove(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	this->updateWindowPosition();
	return this->OnMove(hwnd, LOWORD(lParam), HIWORD(lParam));
};


LPARAM BaseWindow::OnMoved(HWND hwnd, WINDOWPOS* windowPosition) {
	return DefWindowProc(hwnd, WM_WINDOWPOSCHANGED, 0, (LPARAM)windowPosition);
}

LPARAM BaseWindow::onMoved(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	auto windowpos = (WINDOWPOS*)lParam;

	if (this->WindowInfo->XPosition != windowpos->x || this->WindowInfo->YPosition != windowpos->y) {
		this->updateWindowPosition();
		return this->OnMoved(hwnd, windowpos);
	}
	else {
		return DefWindowProc(hwnd, WM_WINDOWPOSCHANGED, 0, lParam);
	}
};


LPARAM BaseWindow::OnPaint(HWND hwnd) {
	return DefWindowProc(hwnd, WM_PAINT, 0, 0);
}

LPARAM BaseWindow::onPaint(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	return this->OnPaint(hwnd);
}


LPARAM BaseWindow::OnRestore(HWND hwnd) {
	return DefWindowProc(hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
}

LPARAM BaseWindow::onRestore(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	this->WindowInfo->IsVisible = true;

	return this->OnRestore(hwnd);
};


LPARAM BaseWindow::OnShow(HWND hwnd, bool show, int type){
	return DefWindowProc(hwnd, WM_SHOWWINDOW, show, type);
}

LPARAM BaseWindow::onShow(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	return this->OnShow(hwnd, (bool)wParam, (int)lParam);
}


LPARAM BaseWindow::OnSize(HWND hwnd, int type, int newClientAreaWidth, int newClientAreaHeight) {
	return DefWindowProc(hwnd, WM_SIZE, type, MAKELONG(newClientAreaWidth, newClientAreaHeight));
}

LPARAM BaseWindow::onSize(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	this->updateWindowSize();
	this->updateWindowClientSize();

	return this->OnSize(hwnd, (int)wParam, LOWORD(lParam), HIWORD(lParam));
}


LPARAM BaseWindow::onSysCommand(HWND hwnd, WPARAM wParam, LPARAM lParam) {
	switch (wParam >> 4 << 4) {
	case SC_MAXIMIZE: return this->onMaximize(hwnd, wParam, lParam);
	case SC_MINIMIZE: return this->onMinimize(hwnd, wParam, lParam);
	case SC_MOVE: return this->onMove(hwnd, wParam, lParam);
	case SC_RESTORE: return this->onRestore(hwnd, wParam, lParam);
	case SC_CLOSE: return this->onClose(hwnd, wParam, lParam);
	}

	return DefWindowProc(hwnd, WM_SYSCOMMAND, wParam, lParam);
}

// Private helpers

void BaseWindow::updateWindowSize() {
	RECT rect;
	if (GetWindowRect(this->Win32WindowInfo->hwnd, &rect)) {
		this->WindowInfo->XPosition = rect.left;
		this->WindowInfo->YPosition = rect.top;
		this->WindowInfo->Width = rect.right - rect.left;
		this->WindowInfo->Height = rect.bottom - rect.top;
	}
}

void BaseWindow::updateWindowPosition() {
	RECT rect;
	if (GetWindowRect(this->Win32WindowInfo->hwnd, &rect)) {
		this->WindowInfo->XPosition = rect.left;
		this->WindowInfo->YPosition = rect.top;
	}
}

void BaseWindow::updateWindowClientSize() {
	RECT rect;
	if (GetClientRect(this->Win32WindowInfo->hwnd, &rect)) {
		this->WindowInfo->ClientWidth = rect.right - rect.left;
		this->WindowInfo->ClientHeight = rect.bottom - rect.top;
	}
}
