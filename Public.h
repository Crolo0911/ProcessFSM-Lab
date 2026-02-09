#pragma once
#include <windows.h>
#include <TlHelp32.h>
#include <iostream>
#define TARGET_NAME L"target.exe"
#define TEST_RVA 0x1000
enum class MyState
{
	MatchPid,
	ApplyForMem,
	VerifySome,
	Work,
	Exit
};
struct context {
	DWORD Pid;
	HANDLE Hprocess;
	LPVOID ModuleBase;
	LPVOID RemoteBase;
	SIZE_T RemoteSize;
};

extern context g_ctx;
BOOL GetPid();
BOOL GetMem();
BOOL CheckState();
BOOL DoWork();
