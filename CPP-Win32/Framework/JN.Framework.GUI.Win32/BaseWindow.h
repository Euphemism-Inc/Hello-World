#pragma once

#include "stdafx.h"

namespace JN::Framework::GUI::Win32 {

	struct DllExport Win32WindowInfo {
	public:
		HINSTANCE hInstance;
		WNDCLASS* wndClass;
		HWND hwnd;
		int iCmdShow;
		bool isWinNT;
	};

	class DllExport BaseWindow : public Window {
	public:
		// Constructor / Destructor
		BaseWindow(HINSTANCE hInstance, int iCmdShow);
		BaseWindow(BaseWindow& baseWindow) = delete;
		virtual ~BaseWindow();

		BaseWindow& operator=(BaseWindow& baseWindow) = delete;

		// Window Methods
		WPARAM Show(void) const override;

	protected:
		// Variables
		Win32WindowInfo *Win32WindowInfo;

		// Protected static window functions
		virtual LPARAM WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam) ;
		virtual LPARAM OnClose(HWND hwnd);
		virtual LPARAM OnDestroy(HWND hwnd);
		virtual LPARAM OnMaximize(HWND hwnd);
		virtual LPARAM OnMinimize(HWND hwnd);
		virtual LPARAM OnMove(HWND hwnd, int cursorX, int cursorY);
		virtual LPARAM OnMoved(HWND hwnd, WINDOWPOS* windowPosition);
		virtual LPARAM OnPaint(HWND hwnd);
		virtual LPARAM OnRestore(HWND hwnd);
		virtual LPARAM OnShow(HWND hwnd, bool show, int type);
		virtual LPARAM OnSize(HWND hwnd, int type, int newClientAreaWidth, int newClientAreaHeight);

	private:
		// Private Methods
		static WNDCLASS* createWndClass(HINSTANCE hInstance, TCHAR szAppName[]);
		bool initialize(WNDCLASS* wndclass);

		// Private (static) window functions
		static LPARAM CALLBACK wndProcInternal(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam);
		LPARAM wndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lparam);
		LPARAM onClose(HWND hwnd, WPARAM wParam, LPARAM lparam);
		LPARAM onDestroy(HWND hwnd, WPARAM wParam, LPARAM lparam);
		LPARAM onMaximize(HWND hwnd, WPARAM wParam, LPARAM lparam);
		LPARAM onMinimize(HWND hwnd, WPARAM wParam, LPARAM lparam);
		LPARAM onMove(HWND hwnd, WPARAM wParam, LPARAM lparam);
		LPARAM onMoved(HWND hwnd, WPARAM wParam, LPARAM lparam);
		LPARAM onPaint(HWND hwnd, WPARAM wParam, LPARAM lparam);
		LPARAM onRestore(HWND hwnd, WPARAM wParam, LPARAM lparam);
		LPARAM onShow(HWND hwnd, WPARAM wParam, LPARAM lparam);
		LPARAM onSize(HWND hwnd, WPARAM wParam, LPARAM lparam);
		LPARAM onSysCommand(HWND hwnd, WPARAM wParam, LPARAM lparam);

		// Private helpers
		void updateWindowSize();
		void updateWindowPosition();
		void updateWindowClientSize();
	};

}
