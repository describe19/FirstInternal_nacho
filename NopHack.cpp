#include "pch.h"
#include "NopHack.h"

NopHack::NopHack(uintptr_t aTargetAddress, BYTE* bytes, unsigned int nopSize, int aToggleKey) : Hack(aTargetAddress, aToggleKey) {
	size = nopSize;
	oldBytes = bytes;

}

void NopHack::toggleHack() {
	bEnabled = !bEnabled;
	if (bEnabled) {
		nop((BYTE*)targetAddr, 10);

	}
	else {
		patch((BYTE*)targetAddr, oldBytes, size);
	}
}

void NopHack::nop(BYTE* dst, unsigned int size) {
	DWORD oldprotect;
	VirtualProtect((BYTE*)targetAddr, size, PAGE_EXECUTE_READWRITE, &oldprotect);
	memset((BYTE*)targetAddr, 0x90, size);
	VirtualProtect((BYTE*)targetAddr, size, oldprotect, &oldprotect);
}

void NopHack::patch(BYTE* dst, BYTE* src, unsigned int size)
{
	DWORD oldprotect;
	VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &oldprotect);

	memcpy(dst, src, size);
	VirtualProtect(dst, size, oldprotect, &oldprotect);
}

NopHack::~NopHack() {}
