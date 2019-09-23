#include "stdafx.h"
#include "API.h"

using namespace JN::Framework::GUI;

int API::_ncalls = 0;

API::API()
{
    _ncalls++;
}

std::wstring API::GetDefaultString()
{
    std::wstring defaultString(TEXT("Hello World!"));
    return defaultString;
};