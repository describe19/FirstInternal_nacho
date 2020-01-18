#pragma once
#include "pch.h"
#include "Hack.h"
class FreezeHack : public Hack
{
public:
	FreezeHack();
	FreezeHack(uintptr_t aBasePtrAddr, std::vector<unsigned int> offsets, int aNewVal, int aToggleKey );
	bool freeze();
	~FreezeHack();

private:
	int newVal;
	uintptr_t FindDMAAddy(uintptr_t basePtrAddr, std::vector<unsigned int> offsets);

};

