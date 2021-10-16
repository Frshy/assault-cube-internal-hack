#include <windows.h>
#include <cstdio>

#include "cheat/memory.h"
#include "cheat/hooks/hooks.h"

void HackInit() {
	hooks::InitWglSwapBuffers();
}

void HackUnInit() {
	hooks::UnInitWglSwapBuffers();
}

DWORD WINAPI HackThread(HMODULE hModule) {
	FILE* pFile = nullptr;
	AllocConsole();
	freopen_s(&pFile, "CONOUT$", "w", stdout);

	HackInit();

	while (!GetAsyncKeyState(VK_END)) {
		Sleep(10);
	}

	HackUnInit();

	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpr) {
	if (reason == DLL_PROCESS_ATTACH) {
		CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, 0));
	}
	return TRUE;
}