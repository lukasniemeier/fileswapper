// FileSwapperStateHandler.cpp : Implementation of CFileSwapperStateHandler

#include "stdafx.h"
#include "FileSwapperStateHandler.h"


// CFileSwapperStateHandler

IFACEMETHODIMP CFileSwapperStateHandler::GetState(IShellItemArray* psiItemArray, BOOL fOkToBeSlow, EXPCMDSTATE* pCmdState)
{
	if (psiItemArray == nullptr)
	{
		return E_FAIL;
	}

	psiItemArray->AddRef();
	DWORD count;
	psiItemArray->GetCount(&count);
	psiItemArray->Release();

	if (count == 2)
	{
		*pCmdState = ECS_ENABLED;
	}
	else
	{
		//REG_DWORD;
		*pCmdState = ECS_HIDDEN;
	}

	return S_OK;
}