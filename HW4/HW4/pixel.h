#pragma once
#include "FreeImage.h"
class pixel {

public:
	BYTE r;
	BYTE g;
	BYTE b;
	pixel(BYTE r, BYTE g, BYTE b) {
		this->r = r;
		this->g = g;
		this->b = b;
	};
	pixel() {
		this->r = 0;
		this->g = 0;
		this->b = 0;
	};
};