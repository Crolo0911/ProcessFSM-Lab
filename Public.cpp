#pragma once
#include "Public.h"
context g_ctx = {};
BOOL GetPid()
{
	HANDLE hSnap=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	PROCESSENTRY32 pe32 = { 0 };
	pe32.dwSize = sizeof(pe32);
	if (Process32First(hSnap, &pe32))
	{

		do
		{
			if (wcscmp(pe32.szExeFile,L"123.exe")==0)
			{
				g_ctx.Pid = pe32.th32ProcessID;
				CloseHandle(hSnap);
				return TRUE;
			}


		} while (Process32Next(hSnap, &pe32));
	}
	CloseHandle(hSnap);
	return FALSE;
}

BOOL GetMem()
{
	HANDLE hproce=OpenProcess(PROCESS_ALL_ACCESS, FALSE, g_ctx.Pid);
	if (hproce==NULL)
	{
		return FALSE;
	}
	g_ctx.Hprocess = hproce;
	return TRUE;
}

BOOL CheckState()
{
	DWORD Pid = g_ctx.Pid;
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, Pid);
	if (hSnap == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	MODULEENTRY32 me32;
	bool Flag = false;
	me32.dwSize = sizeof(me32);
	if (Module32First(hSnap, &me32))//取反就是失败了
	{ 
		do
		{
		if (wcscmp(me32.szModule, TARGET_NAME)==0)
		{
			g_ctx.Modubase = (LPVOID)me32.modBaseAddr;
			Flag = true;
			break;
		}
		} while (Module32Next(hSnap, &me32));
	}
	DWORD nSize = 0;
	
	if (Flag == true)
	{
		if (ReadProcessMemory(g_ctx.Hprocess, g_ctx.Modubase, &nSize, sizeof(DWORD), NULL))
		{
			CloseHandle(hSnap);
			return TRUE;
		}
		CloseHandle(hSnap);
		return FALSE;
	}
	CloseHandle(hSnap);
	return FALSE;
}

BOOL DoWork()
{
	int Value = 0;
	SIZE_T RVA = TEST_RVA;
	uintptr_t addr = (uintptr_t)g_ctx.Modubase + RVA;
	LPVOID realAddr = (LPVOID)addr;
	
	if (!ReadProcessMemory(g_ctx.Hprocess, realAddr, &Value, sizeof(Value), NULL))
	{
		return FALSE;
	}
	std::cout << "DoWork demo executed\n";
	return true;
	
	LPVOID lpBase = VirtualAllocEx(g_ctx.Hprocess, NULL, 0XFF, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		if (lpBase==NULL)
		{
			std::cout << "在内存的申请中失败了" << GetLastError() << std::endl;
			return FALSE;
		}

	return TRUE;
}

