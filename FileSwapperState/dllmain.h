// dllmain.h : Declaration of module class.

class CFileSwapperStateModule : public ATL::CAtlDllModuleT< CFileSwapperStateModule >
{
public :
	DECLARE_LIBID(LIBID_FileSwapperStateLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FILESWAPPERSTATE, "{E3E3EEC8-3D51-4ACD-AC75-0A72ED15744C}")
};

extern class CFileSwapperStateModule _AtlModule;
