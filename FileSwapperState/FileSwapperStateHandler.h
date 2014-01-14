// FileSwapperStateHandler.h : Declaration of the CFileSwapperStateHandler

#pragma once
#include "resource.h"       // main symbols
#include "FileSwapperState_i.h"
#include <shlobj.h>

using namespace ATL;

// CFileSwapperStateHandler
class ATL_NO_VTABLE CFileSwapperStateHandler :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFileSwapperStateHandler, &CLSID_FileSwapperStateHandler>,
	public IInitializeCommand,
	public IExplorerCommandState,
	public IFileSwapperStateHandler
{
public:
	CFileSwapperStateHandler();

DECLARE_REGISTRY_RESOURCEID(IDR_FILESWAPPERSTATEHANDLER)

DECLARE_NOT_AGGREGATABLE(CFileSwapperStateHandler)

BEGIN_COM_MAP(CFileSwapperStateHandler)
	COM_INTERFACE_ENTRY(IInitializeCommand)
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
	// IInitializeCommand
	IFACEMETHODIMP Initialize(PCWSTR pszCommandName, IPropertyBag *ppb);

	// IExplorerCommandState
	IFACEMETHODIMP GetState(IShellItemArray* psiItemArray, BOOL fOkToBeSlow, EXPCMDSTATE* pCmdState);

private:
	bool isElevated;

};

OBJECT_ENTRY_AUTO(__uuidof(FileSwapperStateHandler), CFileSwapperStateHandler)
