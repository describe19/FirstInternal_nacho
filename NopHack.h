#pragma once
#include "Hack.h"
class NopHack :
	public Hack
{
public:
	NopHack(uintptr_t aTargetAddress, BYTE* bytes, unsigned int size, int aToggleKey);
	
	virtual void toggleHack();

	~NopHack();

private:
	unsigned int size;
	BYTE* oldBytes;
	void patch(BYTE* dst, BYTE* src, unsigned int size);
	void nop(BYTE* dst, unsigned int size);

};

