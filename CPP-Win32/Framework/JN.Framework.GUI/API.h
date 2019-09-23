#pragma once

#include "stdafx.h"

namespace JN::Framework::GUI {

    class DllExport API {
    public:
        API(void);
        static std::wstring GetDefaultString();

    private:
        static int _ncalls;
    };

}
