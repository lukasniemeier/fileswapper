// FileSwapper.h : Declaration of the CFileSwapper

#pragma once
#include "resource.h"       // main symbols

#include "FileSwapper_i.h"

#include <shlobj.h> 
#include <string>

using namespace ATL;


// CFileSwapper

class ATL_NO_VTABLE CFileSwapper :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CFileSwapper, &CLSID_FileSwapper>,
	public IObjectWithSiteImpl<CFileSwapper>,
	public IObjectWithSelection,
	public IExecuteCommand,
	public IFileSwapper
{
public:
	CFileSwapper();

DECLARE_REGISTRY_RESOURCEID(IDR_FILESWAPPER)

DECLARE_NOT_AGGREGATABLE(CFileSwapper)

BEGIN_COM_MAP(CFileSwapper)
	COM_INTERFACE_ENTRY(IObjectWithSite)
	COM_INTERFACE_ENTRY(IObjectWithSelection)
	COM_INTERFACE_ENTRY(IExecuteCommand)
	COM_INTERFACE_ENTRY(IFileSwapper)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease();

public:

	// IObjectWithSelection
	IFACEMETHODIMP SetSelection(IShellItemArray *psia);

	IFACEMETHODIMP GetSelection(REFIID riid, void** ppv);

	// IExecuteCommand
	IFACEMETHODIMP SetKeyState(DWORD grfKeyState);

	IFACEMETHODIMP SetParameters(PCWSTR pszParameters);

	IFACEMETHODIMP SetPosition(POINT pt);

	IFACEMETHODIMP SetShowWindow(int nShow);

	IFACEMETHODIMP SetNoShowUI(BOOL fNoShowUI);

	IFACEMETHODIMP SetDirectory(PCWSTR pszDirectory);

	IFACEMETHODIMP Execute();

	HRESULT Swap(const std::wstring left, const std::wstring right) const;

protected:
	template <class T> void ReleaseObject(T** object)
	{
		if (*object)
		{
			(*object)->Release();
			*object = nullptr;
		}
	}

private:
	IShellItemArray* selectedItems;

};

OBJECT_ENTRY_AUTO(__uuidof(FileSwapper), CFileSwapper)
