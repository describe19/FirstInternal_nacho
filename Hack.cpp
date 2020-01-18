#include "pch.h"
#include "Hack.h"
Hack::Hack() {
	bEnabled = 0;
	targetAddr = NULL;
	toggleKey = 0;

}

Hack::Hack(int aToggleKey) {
	bEnabled = 0;
	targetAddr = NULL;
	toggleKey = aToggleKey;
}

Hack::Hack(uintptr_t aTargetAddress, int aToggleKey) {
	bEnabled = 0;
	targetAddr = aTargetAddress;
	toggleKey = aToggleKey;
}


bool Hack::enabled() {
	return bEnabled;
}

void Hack::toggleHack() {
	bEnabled = !bEnabled;
}

bool Hack::toggleKeyPressed() {
	if (GetAsyncKeyState(toggleKey) & 1) {
		return 1;
	}
	else {
		return 0;
	}
}

Hack::~Hack(){}