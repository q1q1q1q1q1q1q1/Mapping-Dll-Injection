#include "inject.h"


unsigned __stdcall findProc(char *procTarget)
{
	PROCESSENTRY32 pe32{ 0 };
	pe32.dwSize = sizeof(pe32);

	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		DWORD err = GetLastError();
		printf("CreateToolhelp32Snaphot failed: 0x%X\n", err);
		return 0;
	}
	unsigned pid = 0;
	BOOL bRet = Process32First(hSnap, &pe32);
	while (bRet)
	{
		if (!strcmp(pe32.szExeFile, procTarget))
		{
			pid = pe32.th32ProcessID;
			break;
		}
		bRet = Process32Next(hSnap, &pe32);
	}
	CloseHandle(hSnap);
	return pid;
}



int main()
{
	char procTarget	[255]{ 0 };
	char dllName[255]{ 0 };

	std::cout << "Enter the game: " << '\n';
	std::cin >> procTarget;
	std::cout << "Enter the dll name" << '\n';
	std::cin >> dllName;

	if (!GetFileAttributesA(dllName))
	{
		printf("dll doesn't exist\n");
		system("pause");
		return EXIT_FAILURE;
	}


	unsigned pid = findProc(procTarget);
	if (pid == 0)
	{
		system("pause");
		return EXIT_FAILURE;
	}

	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (!hProc)
	{
		DWORD err = GetLastError();
		printf("OpenProcess failed: 0x%X\n", err);
		system("pause");
	}
	ManualMap(hProc, dllName);

}