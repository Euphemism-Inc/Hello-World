#include "stdafx.h"

using namespace JN::FrontEnd;

int _tmain(int argc, wchar_t* argv[])
{
    Zeus::API api;

    std::wcout << api.GetDefaultString() << std::endl;

    if (argc == 2) {
        std::wcout << argv[1] << std::endl;
    }

    return 0;
}

//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
//{
//	return 0;
//}
//
//LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
//{
//	return 0;
//}