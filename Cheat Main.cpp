#include "Cheat Main.h"
#include "Interfaces.h"

bool CheatActive = true;

DWORD WINAPI OnDllAttach(PVOID base)
{
	Init();

	while (CheatActive)
	{
		using namespace std::literals::chrono_literals;
		std::this_thread::sleep_for(1s);
	}

	FreeLibraryAndExitThread(static_cast<HMODULE>(base), 1);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(nullptr, NULL, OnDllAttach, hModule, NULL, nullptr);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		if (!lpReserved)
		{
			using namespace std::literals::chrono_literals;
			std::this_thread::sleep_for(1s);
		}
	}

	return TRUE;
}