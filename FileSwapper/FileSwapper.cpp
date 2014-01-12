// FileSwapper.cpp : Implementation of CFileSwapper

#include "stdafx.h"

#include <vector>
#include <Strsafe.h>

#include "FileSwapper.h"
#include "Error.h"


HRESULT CoCreateInstanceAsAdmin(HWND hwnd, REFCLSID rclsid, REFIID riid, __out void ** ppv)
{
	BIND_OPTS3 bo;
	WCHAR wszCLSID[50];
	WCHAR wszMonikerName[300];

	::StringFromGUID2(rclsid, wszCLSID, sizeof(wszCLSID) / sizeof(wszCLSID[0]));
	HRESULT hr = ::StringCchPrintf(wszMonikerName, sizeof(wszMonikerName) / sizeof(wszMonikerName[0]),
		L"Elevation:Administrator!new:%s", wszCLSID);
	if (FAILED(hr))
	{
		return hr;
	}
	memset(&bo, 0, sizeof(bo));
	bo.cbStruct = sizeof(bo);
	bo.hwnd = hwnd;
	bo.dwClassContext = CLSCTX_LOCAL_SERVER;
	return ::CoGetObject(wszMonikerName, &bo, riid, ppv);
}


// CFileSwapper
CFileSwapper::CFileSwapper() : isElevated(false), selectedItems(nullptr)
{

}

void CFileSwapper::FinalRelease()
{
	ReleaseObject(&selectedItems);
}

HRESULT CFileSwapper::GetElevatedFileSwapper(IFileSwapper** outSwapper)
{
	HWND siteWindow = nullptr;
	if (FAILED(IUnknown_GetWindow(m_spUnkSite, &siteWindow)))
	{
		siteWindow = nullptr;
	}
	return CoCreateInstanceAsAdmin(siteWindow, CLSID_FileSwapper, __uuidof(IFileSwapper), (void**)outSwapper);
}

HRESULT CFileSwapper::Execute(LPWSTR leftItemName, LPWSTR rightItemName)
{
	HRESULT hr = S_OK;
	CComPtr<IFileSwapper> swapper;
	if (isElevated)
	{
		hr = GetElevatedFileSwapper(&swapper);
	}
	else
	{
		swapper = this;
	}

	if (SUCCEEDED(hr))
	{
		hr = swapper->Swap(leftItemName, rightItemName);
	}

	return hr;
}

// IObjectWithSelection
IFACEMETHODIMP CFileSwapper::SetSelection(IShellItemArray *psia)
{
	ReleaseObject(&selectedItems);
	selectedItems = psia;
	if (selectedItems != nullptr)
	{
		selectedItems->AddRef();
	}
	return S_OK; 
}

IFACEMETHODIMP CFileSwapper::GetSelection(REFIID riid, void** ppv)
{ 
	*ppv = nullptr;
	if (selectedItems != nullptr)
	{
		return selectedItems->QueryInterface(riid, ppv);
	}
	else
	{
		return E_FAIL;
	}
}

// IInitializeCommand
IFACEMETHODIMP CFileSwapper::Initialize(PCWSTR pszCommandName, IPropertyBag *ppb)
{
	if (::StrStr(pszCommandName, L"Elevated") != nullptr)
	{
		isElevated = true;
	}
	return S_OK;
}

// IExecuteCommand
IFACEMETHODIMP CFileSwapper::SetKeyState(DWORD grfKeyState)
{ 
	return S_OK; 
}

IFACEMETHODIMP CFileSwapper::SetParameters(PCWSTR pszParameters)
{ 
	return S_OK; 
}

IFACEMETHODIMP CFileSwapper::SetPosition(POINT pt)
{ 
	return S_OK; 
}

IFACEMETHODIMP CFileSwapper::SetShowWindow(int nShow)
{ 
	return S_OK; 
}

IFACEMETHODIMP CFileSwapper::SetNoShowUI(BOOL fNoShowUI)
{ 
	return S_OK; 
}

IFACEMETHODIMP CFileSwapper::SetDirectory(PCWSTR pszDirectory)
{
	return S_OK; 
}

IFACEMETHODIMP CFileSwapper::Execute()
{ 
	if (selectedItems == nullptr)
	{
		return E_UNEXPECTED;
	}

	DWORD count;
	HRESULT hr = selectedItems->GetCount(&count);
	if (FAILED(hr) || count != 2)
	{
		return E_UNEXPECTED;
	}

	CComPtr<IShellItem> firstItem;
	hr = selectedItems->GetItemAt(0, &firstItem);
	if (FAILED(hr))
	{
		return hr;
	}
		
	CComHeapPtr<WCHAR> firstItemName;
	hr = firstItem->GetDisplayName(SIGDN_FILESYSPATH, &firstItemName);
	if (FAILED(hr))
	{
		return hr;
	}

	CComPtr<IShellItem> secondItem;
	hr = selectedItems->GetItemAt(1, &secondItem);
	if (FAILED(hr))
	{
		return hr;
	}

	CComHeapPtr<WCHAR> secondItemName;
	hr = secondItem->GetDisplayName(SIGDN_FILESYSPATH, &secondItemName);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = Execute(firstItemName, secondItemName);

	if (FAILED(hr))
	{
		OUTPUT_DEBUG_STRING(hr);
	}

	return hr; 
}

// IFileSwapper
IFACEMETHODIMP CFileSwapper::Swap(BSTR leftFile, BSTR rightFile)
{
	std::wstring leftString(leftFile);
	std::wstring path;
	const size_t last_slash_idx = leftString.rfind('\\');
	if (std::string::npos == last_slash_idx)
	{
		return E_FAIL;
	}
	path = leftString.substr(0, last_slash_idx);

	wchar_t tempFile[MAX_PATH];
	if (::GetTempFileName(path.c_str(), L"swap", 0, tempFile) == 0)
	{
		HRESULT result = HRESULT_FROM_WIN32(GetLastError());
		OUTPUT_DEBUG_STRING(L"Error creating temporary file", result);
		return result;
	}

	if (::MoveFileEx(leftFile, tempFile, MOVEFILE_REPLACE_EXISTING) == FALSE)
	{
		HRESULT result = HRESULT_FROM_WIN32(GetLastError());
		OUTPUT_DEBUG_STRING(L"Error moving left file to temporary file", result);
		return result;
	}

	if (::MoveFileEx(rightFile, leftFile, MOVEFILE_REPLACE_EXISTING) == FALSE)
	{
		HRESULT result = HRESULT_FROM_WIN32(GetLastError());
		OUTPUT_DEBUG_STRING(L"Error moving right file to left file", result);
		return result;
	}

	if (::MoveFileEx(tempFile, rightFile, MOVEFILE_REPLACE_EXISTING) == FALSE)
	{
		HRESULT result = HRESULT_FROM_WIN32(GetLastError());
		OUTPUT_DEBUG_STRING(L"Error moving temporary file to left file", result);
		return result;
	}

	return S_OK;
}