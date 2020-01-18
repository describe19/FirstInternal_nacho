// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "FreezeHack.h"
#include "NopHack.h"

DWORD WINAPI HackThread(HMODULE hModule) {
	//Create Console
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	std::cout << "HackThread is running\n";

	//calling GetModuleHandle with NULL gives you the address of the calling .exe module
	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);
	uintptr_t localPlayerPtrAddr = (uintptr_t)(moduleBase + 0x10F4F4);

	FreezeHack healthFreeze(localPlayerPtrAddr, { 0xF8 }, 1337, VK_F1);
	FreezeHack ammoFreeze(localPlayerPtrAddr, { 0x374, 0x14, 0x0 }, 1337, VK_F2);
	NopHack noRecoil(moduleBase + 0x63786, (BYTE*)"\x50\x8D\x4C\x24\x1C\x51\x8B\xCE\xFF\xD2", 10, VK_F3);
	while (true)
	{
		//Keypress listening
		if (GetAsyncKeyState(VK_END) & 1) {
			break;
		}
		
		if (healthFreeze.toggleKeyPressed())
		{
			healthFreeze.toggleHack();		
		}

		if (ammoFreeze.toggleKeyPressed())
		{
			ammoFreeze.toggleHack();		
		}

		if (noRecoil.toggleKeyPressed())
		{
			noRecoil.toggleHack();
		}
		
		//Continuous writes / freeze
		if (localPlayerPtrAddr) {
			if (healthFreeze.enabled())
			{
				healthFreeze.freeze();
			}

			if (ammoFreeze.enabled())
			{
				ammoFreeze.freeze();
			}
		}
		
	}
	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule, 0, nullptr));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

