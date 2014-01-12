// FileSwapperStateHandler.cpp : Implementation of CFileSwapperStateHandler

#include "stdafx.h"
#include "FileSwapperStateHandler.h"

#include <Aclapi.h>

#include <atlsecurity.h>

bool isOwnedByCurrentUser(const LPWSTR path)
{
	bool isOwnedByCurrentUser = false;
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
				if (AccessCheck(
					secDesc,                 // security descriptor to check
					hImpersonatedToken,              // impersonation token
					dwAccessDesired,     // requested access rights
					&mapping,            // pointer to GENERIC_MAPPING
					&PrivilegeSet,       // receives privileges used in check
					&dwPrivSetSize,      // size of PrivilegeSet buffer
					&dwAccessAllowed,    // receives mask of allowed access rights
					&fAccessGranted))   // receives results of access check
				{
					isOwnedByCurrentUser = dwAccessAllowed & FILE_GENERIC_WRITE;
				}
				::CloseHandle(hImpersonatedToken);
			}
			::CloseHandle(hToken);
		}
		::LocalFree(secDesc);
	}

	return isOwnedByCurrentUser;
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

// IExplorerCommandState
IFACEMETHODIMP CFileSwapperStateHandler::GetState(IShellItemArray* psiItemArray, BOOL fOkToBeSlow, EXPCMDSTATE* pCmdState)
{
	if (psiItemArray == nullptr)
	{
		return E_FAIL;
	}

	EXPCMDSTATE state = ECS_HIDDEN;

	psiItemArray->AddRef();
	DWORD count;
	psiItemArray->GetCount(&count);
	if (count == 2)
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
					if (isOwnedByCurrentUser(directoryName))
					{
						state = ECS_ENABLED;
					}
					::CoTaskMemFree(directoryName);
				}
			}
		}

		
	}
	psiItemArray->Release();

	if (isElevated)
	{
		state = state == ECS_ENABLED ? ECS_HIDDEN : ECS_ENABLED;
	}

	*pCmdState = state;

	return S_OK;
}