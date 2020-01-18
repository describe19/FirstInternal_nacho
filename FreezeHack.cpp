#include "pch.h"
#include "FreezeHack.h"

FreezeHack::FreezeHack() {
	newVal = 0;
}

FreezeHack::FreezeHack(uintptr_t aBasePtrAddr, std::vector<unsigned int> offsets, int aNewVal, int aToggleKey) : Hack(aToggleKey) {
	newVal = aNewVal;
	targetAddr = FindDMAAddy(aBasePtrAddr, offsets);
}

bool FreezeHack::freeze() {
	if (bEnabled) {
		*(int*)targetAddr = newVal;
		return 1;
	}
	else {
		return 0;
	}
}

uintptr_t FreezeHack::FindDMAAddy(uintptr_t basePtrAddr, std::vector<unsigned int> offsets)
{
	targetAddr = basePtrAddr;
	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		targetAddr = *(uintptr_t*)targetAddr;
		targetAddr += offsets[i];
	}
	return targetAddr;
}

FreezeHack::~FreezeHack() {

}
