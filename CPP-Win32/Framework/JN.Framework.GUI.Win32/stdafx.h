#pragma once

// Definitions
#define DllImport   __declspec( dllimport )
#define DllExport   __declspec( dllexport )


// Executable Specific
#include "targetver.h"


// Standard Library Header Files
#include <string>
#include <tchar.h>


// C RunTime Header Files
//#include <stdio.h>


// Windows Header Files:
#include <windows.h>


// Project Specific Header Files
#include "Framework\JN.Framework.GUI\API.h"
#include "Framework\JN.Framework.GUI\Window.h"
