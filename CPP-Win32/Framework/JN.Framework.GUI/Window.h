#pragma once

#include "stdafx.h"

namespace JN::Framework::GUI {

	struct DllExport WindowInfo {
	public:
		bool IsVisible;
		long XPosition;
		long YPosition;
		long Width;
		long Height;
		long ClientWidth;
		long ClientHeight;
		bool IsQuitting;
	};

	class DllExport Window {
	public:
		// Constructor / Destructor
		Window(void);
		virtual ~Window(void);

		Window& operator=(Window& baseWindow) = delete;

		// Window Methods
		virtual UINT_PTR Show(void) const = 0;

	protected:
		WindowInfo* WindowInfo;
	};

}
