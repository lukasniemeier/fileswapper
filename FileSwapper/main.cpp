// FileSwapper.cpp : Implementation of WinMain


#include "stdafx.h"
#include "resource.h"
#include "FileSwapper_i.h"
#include <iostream>


using namespace ATL;


class CFileSwapperModule : public ATL::CAtlExeModuleT< CFileSwapperModule >
{
public :
	DECLARE_LIBID(LIBID_FileSwapperLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FILESWAPPER_MODULE, "{C632E308-0E26-4FC8-8C64-CF11D9C95547}")

	void ShowHelp()
	{
		::MessageBox(nullptr, 
			L"You have to pass a command line switch to specify what you want.\n\nInstall (current user): '/RegServerPerUser'\nUninstall (current user): '/UnregServerPerUser'\nInstall (all users): '/RegServer'\nUninstall (all users): '/UnregServer'\n\nTo install/uninstall for all users please use an elevated prompt. To enable this shell extension in folders needing elevation you have to install it for all users.", 
			L"FileSwapper Shell Extension", MB_ICONINFORMATION);
	}

	int GetCommandLineCount(_In_z_ LPCTSTR lpCmdLine)
	{
		TCHAR tokens[] = _T(" ");
		int count = 0;
		LPCTSTR lpszToken = FindOneOf(lpCmdLine, tokens);
		while (lpszToken != NULL)
		{
			if (wcslen(lpszToken) != 0)
			{
				count++;
			}
			lpszToken = FindOneOf(lpszToken, tokens);
		}
		return count;
	}

	bool ParseCommandLine(
		_In_z_ LPCTSTR lpCmdLine,
		_Out_ HRESULT* pnRetCode) throw()
	{
		*pnRetCode = S_OK;

		int count = GetCommandLineCount(lpCmdLine);
		if (count == 0)
		{
			ShowHelp();
			return false;
		}

		TCHAR szTokens[] = _T("-/");
		LPCTSTR lpszToken = FindOneOf(lpCmdLine, szTokens);
		while (lpszToken != NULL)
		{
			if (WordCmpI(lpszToken, _T("UnregServer")) == 0)
			{
				int exitCode = (int) ::ShellExecute(NULL, L"open", L"regsvr32", L"/s /u /n /i:user FileSwapperState.dll", NULL, SW_HIDE);
				if (exitCode <= 32)
				{
					return false;
				}
				exitCode = (int) ::ShellExecute(NULL, L"open", L"regsvr32", L"/s /u FileSwapperPS.dll", NULL, SW_HIDE);
				if (exitCode <= 32)
				{
					return false;
				}

				*pnRetCode = this->UnregisterServer(TRUE);
				if (SUCCEEDED(*pnRetCode))
					*pnRetCode = this->UnregisterAppId();

				return false;
			}

			if (WordCmpI(lpszToken, _T("RegServer")) == 0)
			{
				*pnRetCode = this->RegisterAppId();
				if (SUCCEEDED(*pnRetCode))
					*pnRetCode = this->RegisterServer(TRUE);

				int exitCode = (int) ::ShellExecute(NULL, L"open", L"regsvr32", L"/s FileSwapperState.dll", NULL, SW_SHOW);
				if (exitCode <= 32)
				{
					return false;
				}
				exitCode = (int) ::ShellExecute(NULL, L"open", L"regsvr32", L"/s FileSwapperPS.dll", NULL, SW_SHOW);
				if (exitCode <= 32)
				{
					return false;
				}
				return false;
			}

			if (WordCmpI(lpszToken, _T("UnregServerPerUser")) == 0)
			{
				int exitCode = (int) ::ShellExecute(NULL, L"open", L"regsvr32", L"/s /u /n /i:user FileSwapperState.dll", NULL, SW_SHOW);
				if (exitCode <= 32)
				{
					return false;
				}

				*pnRetCode = AtlSetPerUserRegistration(true);
				if (FAILED(*pnRetCode))
				{
					return false;
				}

				*pnRetCode = this->UnregisterServer(TRUE);
				if (SUCCEEDED(*pnRetCode))
					*pnRetCode = this->UnregisterAppId();
				return false;
			}

			if (WordCmpI(lpszToken, _T("RegServerPerUser")) == 0)
			{
				*pnRetCode = AtlSetPerUserRegistration(true);
				if (FAILED(*pnRetCode))
				{
					return false;
				}

				*pnRetCode = this->RegisterAppId();
				if (SUCCEEDED(*pnRetCode))
					*pnRetCode = this->RegisterServer(TRUE);

				int exitCode = (int) ::ShellExecute(NULL, L"open", L"regsvr32", L"/s /n /i:user FileSwapperState.dll", NULL, SW_SHOW);
				if (exitCode <= 32)
				{
					return false;
				}
				return false;
			}

			lpszToken = FindOneOf(lpszToken, szTokens);
		}

		return true;
	}

};

CFileSwapperModule _AtlModule;



//
extern "C" int WINAPI _tWinMain(HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, 
								LPTSTR /*lpCmdLine*/, int nShowCmd)
{
	return _AtlModule.WinMain(nShowCmd);
}

