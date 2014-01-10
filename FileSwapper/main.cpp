// FileSwapper.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "FileSwapper_i.h"


using namespace ATL;


class CFileSwapperModule : public ATL::CAtlExeModuleT< CFileSwapperModule >
{
public :
	DECLARE_LIBID(LIBID_FileSwapperLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FILESWAPPER_MODULE, "{C632E308-0E26-4FC8-8C64-CF11D9C95547}")

};

CFileSwapperModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

