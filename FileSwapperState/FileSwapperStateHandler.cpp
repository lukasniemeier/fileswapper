// FileSwapperStateHandler.cpp : Implementation of CFileSwapperStateHandler

#include "stdafx.h"
#include "FileSwapperStateHandler.h"
#include <Aclapi.h>
#include <atlsecurity.h>

bool IsWriteableByCurrentUser(const LPWSTR path)
{
	bool isWriteable = false;
	DWORD result;
	SECURITY_INFORMATION secInfo = OWNER_SECURITY_INFORMATION | GROUP_SECURITY_INFORMATION | DACL_SECURITY_INFORMATION;
	PSECURITY_DESCRIPTOR secDesc;
	PSID owner;
	result = GetNamedSecurityInfo(path, SE_FILE_OBJECT, secInfo,
		&owner, NULL, NULL, NULL, &secDesc);
	if (result == ERROR_SUCCESS)
	{
		HANDLE hToken;
		DWORD dwAccessDesired = GENERIC_WRITE;
		PRIVILEGE_SET PrivilegeSet;
		DWORD dwPrivSetSize = sizeof(PRIVILEGE_SET);
		DWORD dwAccessAllowed;
		BOOL fAccessGranted = FALSE;

		GENERIC_MAPPING mapping = { 0xFFFFFFFF };
		mapping.GenericRead = FILE_GENERIC_READ;
		mapping.GenericWrite = FILE_GENERIC_WRITE;
		mapping.GenericExecute = FILE_GENERIC_EXECUTE;
		mapping.GenericAll = FILE_ALL_ACCESS;

		::MapGenericMask(&dwAccessDesired, &mapping);

		if (::OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken))
		{
			HANDLE hImpersonatedToken = NULL;
			if (::DuplicateToken(hToken, SecurityImpersonation, &hImpersonatedToken)) {
				if (AccessCheck(secDesc, hImpersonatedToken, dwAccessDesired, &mapping,
					&PrivilegeSet, &dwPrivSetSize, &dwAccessAllowed, &fAccessGranted))
				{
					isWriteable = (dwAccessAllowed & FILE_GENERIC_WRITE) != 0;
				}
				::CloseHandle(hImpersonatedToken);
			}
			::CloseHandle(hToken);
		}
		::LocalFree(secDesc);
	}

	return isWriteable;
}

CFileSwapperStateHandler::CFileSwapperStateHandler() : isElevated(false)
{

}

// IInitializeCommand
IFACEMETHODIMP CFileSwapperStateHandler::Initialize(PCWSTR pszCommandName, IPropertyBag *ppb)
{
	if (::StrStr(pszCommandName, L"Elevated") != nullptr)
	{
		isElevated = true;
	}
	return S_OK;
}

bool IsRegisteredForElevation()
{
	HKEY key;
	LSTATUS status = ::RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Classes\\CLSID\\{9EEBD123-D499-47C1-AA58-F1C5FF795BB8}\\Elevation", 0, KEY_ENUMERATE_SUB_KEYS, &key);
	if (status == ERROR_SUCCESS)
	{
		::RegCloseKey(key);
		return true;
	}
	return false;
}

// IExplorerCommandState
IFACEMETHODIMP CFileSwapperStateHandler::GetState(IShellItemArray* psiItemArray, BOOL fOkToBeSlow, EXPCMDSTATE* pCmdState)
{
	if (psiItemArray == nullptr)
	{
		return E_FAIL;
	}

	EXPCMDSTATE state = ECS_HIDDEN;
	DWORD count;

	psiItemArray->AddRef();
	psiItemArray->GetCount(&count);
	if (count == 2)
	{
		if (isElevated && !IsRegisteredForElevation())
		{
			state = ECS_HIDDEN;;
		}
		else
		{
			CComPtr<IShellItem> item;
			if (psiItemArray->GetItemAt(0, &item) == S_OK)
			{
				CComPtr<IShellItem> parent;
				if (item->GetParent(&parent) == S_OK)
				{
					LPWSTR directoryName;
					if (parent->GetDisplayName(SIGDN_FILESYSPATH, &directoryName) == S_OK)
					{
						if (IsWriteableByCurrentUser(directoryName))
						{
							state = isElevated ? ECS_HIDDEN : ECS_ENABLED;
						}
						::CoTaskMemFree(directoryName);
					}
				}
			}
		}
	}
	psiItemArray->Release();

	*pCmdState = state;

	return S_OK;
}