#pragma once

#include "stdafx.h"

using namespace JN::Framework::GUI::Win32;

namespace JN::FrontEnd::Zeus::Win32::Windows {

	class MainWin : public BaseWindow {
	public:
		MainWin(HINSTANCE hInstance, int iCmdShow);

	private:
		LPARAM WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam) override;
		LPARAM OnPaint(HWND hwnd) override;
		LPARAM OnUser(HWND hwnd, WPARAM wParam, LPARAM lparam);
	};

}
