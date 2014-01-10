// FileSwapperStateHandler.h : Declaration of the CFileSwapperStateHandler

#pragma once
#include "resource.h"       // main symbols



#include "FileSwapperState_i.h"
#include <shlobj.h> 


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;


// CFileSwapperStateHandler

class ATL_NO_VTABLE CFileSwapperStateHandler :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFileSwapperStateHandler, &CLSID_FileSwapperStateHandler>,
	public IExplorerCommandState,
	public IFileSwapperStateHandler
{
public:
	CFileSwapperStateHandler()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_FILESWAPPERSTATEHANDLER)

DECLARE_NOT_AGGREGATABLE(CFileSwapperStateHandler)

BEGIN_COM_MAP(CFileSwapperStateHandler)
	COM_INTERFACE_ENTRY(IExplorerCommandState)
	COM_INTERFACE_ENTRY(IFileSwapperStateHandler)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	IFACEMETHODIMP GetState(IShellItemArray* psiItemArray, BOOL fOkToBeSlow, EXPCMDSTATE* pCmdState);

};

OBJECT_ENTRY_AUTO(__uuidof(FileSwapperStateHandler), CFileSwapperStateHandler)
