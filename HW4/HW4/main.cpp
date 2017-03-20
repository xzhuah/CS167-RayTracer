#pragma once
#include <vector>
#include "pixel_image.h"
#include "pixel.h"
#include "Shape.h"
#include "camera.h"
#include "variables.h"

int main() {
	pixel_image myimage(width, height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixel p(0,0,0);
			myimage.calcPixel(i, j, mycamera.genRay(i, j, width, height), maxdepth);
		}
	}
	myimage.outputImage("testing2.png");
}