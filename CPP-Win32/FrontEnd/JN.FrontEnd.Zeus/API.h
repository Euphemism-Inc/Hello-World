#pragma once

#include "stdafx.h"

namespace JN::FrontEnd::Zeus {

    class DllExport API {
    public:
        API(void);
        static std::wstring GetDefaultString();

    private:
        static int _ncalls;
    };

}
