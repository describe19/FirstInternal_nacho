#pragma once
#include "pch.h"
#include <Windows.h>
class Hack
{
public:
	Hack();
	Hack(int aToggleKey);
	Hack(uintptr_t aTargetAddress, int aToggleKey);
	bool enabled();

	virtual void toggleHack();
	bool toggleKeyPressed();

	~Hack();

protected:
	bool bEnabled;
	uintptr_t targetAddr;

private:

	int toggleKey;
};

