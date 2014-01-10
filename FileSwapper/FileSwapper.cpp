// FileSwapper.cpp : Implementation of CFileSwapper

#include "stdafx.h"
#include "FileSwapper.h"

#include <vector>



// CFileSwapper

CFileSwapper::CFileSwapper() : selectedItems(nullptr)
{

}

void CFileSwapper::FinalRelease()
{
	ReleaseObject(&selectedItems);
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
	HRESULT hr = S_OK;
	if (selectedItems != nullptr) 
	{
		DWORD count;
		HRESULT hr = selectedItems->GetCount(&count);
		if (SUCCEEDED(hr))
		{
			if (count == 2)
			{
				IEnumShellItems* item;
				if (SUCCEEDED(hr = selectedItems->EnumItems(&item)))
				{
					std::vector<std::wstring> fileNames;
					IShellItem *psi;
					while (item->Next(1, &psi, NULL) == S_OK)
					{
						LPWSTR pszName;
						if (SUCCEEDED(psi->GetDisplayName(SIGDN_FILESYSPATH, &pszName)))
						{
							fileNames.push_back(pszName);
							::CoTaskMemFree(pszName);
						}
						psi->Release();
					}
					item->Release();

					hr = Swap(fileNames.at(0), fileNames.at(1));
				}
			}
			else
			{
				::MessageBox(nullptr, L"Nichts da.", L"Fehler", MB_ICONERROR);
				hr = E_FAIL;
			}
		}
	}
	else 
	{
		hr = E_UNEXPECTED;
	}

	return hr; 
}

HRESULT CFileSwapper::Swap(const std::wstring left, const std::wstring right) const
{
	std::wstring path;
	const size_t last_slash_idx = left.rfind('\\');
	if (std::string::npos == last_slash_idx)
	{
		return E_FAIL;
	}
	path = left.substr(0, last_slash_idx);

	wchar_t tempFile[MAX_PATH];
	if (::GetTempFileName(path.c_str(), L"swap", 0, tempFile) == 0)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	LPCWSTR leftFile = left.c_str();
	LPCWSTR rightFile = right.c_str();

	if (::MoveFileEx(leftFile, tempFile, MOVEFILE_REPLACE_EXISTING) == FALSE)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (::MoveFileEx(rightFile, leftFile, MOVEFILE_REPLACE_EXISTING) == FALSE)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (::MoveFileEx(tempFile, rightFile, MOVEFILE_REPLACE_EXISTING) == FALSE)
	{
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}