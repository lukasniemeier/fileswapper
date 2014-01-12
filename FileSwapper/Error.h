#pragma once

#include <Windows.h>
#include <wchar.h>
#include <sstream>
typedef std::basic_stringstream<WCHAR> tstringstream;
template<typename T> tstringstream& operator,(tstringstream& tss, T t) { tss << _T(" ") << t; return tss; }
template<typename T> tstringstream& operator| (tstringstream& tss, const T t) { tss << t; return tss; }

#ifdef _DEBUG
#define OUTPUT_DEBUG_STRING(...) ::OutputDebugString((tstringstream() | L"[" | __FILE__ | L":" | __LINE__ | L"]" , __VA_ARGS__, L"\n").str().c_str()); 
#else
#define OUTPUT_DEBUG_STRING(...)
#endif