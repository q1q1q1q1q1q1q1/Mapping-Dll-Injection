#pragma once
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <TlHelp32.h>

using f_LoadLibraryA	 = HINSTANCE (__stdcall*)(const char* lpLibFilename);
using f_GetProcAddress	 = UINT_PTR  (__stdcall*)(HINSTANCE hModule, const char* lpProcName);
using f_DLL_ENTYRY_POINT = BOOL	     (__stdcall*)(void* hDll, DWORD dwReason, void* pReserved);

struct MANUAL_MAPPING_DATA
{
	f_LoadLibraryA		pLoadLibraryA;
	f_GetProcAddress	pGetProcAddress;
	HINSTANCE			hMod;
};

bool ManualMap(HANDLE hProc, const char* szDllFile);