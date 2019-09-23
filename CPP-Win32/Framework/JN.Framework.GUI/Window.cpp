#include "stdafx.h"
#include "Window.h"

using namespace JN::Framework::GUI;

Window::Window() :
	WindowInfo(new JN::Framework::GUI::WindowInfo())
{
}

Window::~Window() {
	if (this->WindowInfo) {
		delete this->WindowInfo;
		this->WindowInfo = nullptr;
	}
}