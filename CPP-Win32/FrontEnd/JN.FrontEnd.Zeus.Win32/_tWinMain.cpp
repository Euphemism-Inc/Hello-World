#include "stdafx.h"
#include "_tWinMain.h"
#include "MainWin.h"

using namespace JN::FrontEnd::Zeus::Win32::Windows;

int APIENTRY _tWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPTSTR    lpCmdLine,
    _In_ int       iCmdShow
) {
    MainWin *window = new MainWin(hInstance, iCmdShow);
    WPARAM destVal = window->Show();
    delete window;
    window = nullptr;

    return destVal;
}