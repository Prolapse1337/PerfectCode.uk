#pragma once

template <class T>
static T GetFunction(void* instance, int index)
{
	const auto vtable = *static_cast<void***>(instance);
	return reinterpret_cast<T>(vtable[index]);
}