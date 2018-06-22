#pragma once

typedef void* (*CreateInterfaceFn)(const char* pName, int* pReturnCode);

template<typename T>
T* CaptureInterface(const char* szModuleName, const char* szInterfaceVersion)
{
	HMODULE moduleHandle = GetModuleHandleA(szModuleName);

	if (moduleHandle)
	{
		CreateInterfaceFn pfnFactory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(moduleHandle, "CreateInterface"));
		return reinterpret_cast<T*>(pfnFactory(szInterfaceVersion, nullptr));
	}

	return nullptr;
}