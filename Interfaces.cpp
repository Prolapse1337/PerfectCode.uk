#include "Classes.h"
#include "Interfaces.h"

IPanel* m_fPanel = nullptr;
IClientMode* m_fClientMode = nullptr;
IBaseClientDLL* m_fClientDll = nullptr;

auto Init() -> void
{
	m_fClientDll = CaptureInterface<IBaseClientDLL>("client.dll", "VClient018");
	m_fClientMode = **reinterpret_cast<IClientMode***>((*reinterpret_cast<uintptr_t**>(m_fClientDll))[10] + 0x5u);
	m_fPanel = CaptureInterface<IPanel>("vgui2.dll", "VGUI_Panel009");
}