#include "stdafx.h"
#include "API.h"

using namespace JN::FrontEnd::Zeus;

int API::_ncalls = 0;

API::API()
{
    _ncalls++;
}

std::wstring API::GetDefaultString()
{
    std::wstring defaultString(L"Hello World!");
    return defaultString;
};