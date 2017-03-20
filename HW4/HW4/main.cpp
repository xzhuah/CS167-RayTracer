#pragma once
#include <vector>
#include "pixel_image.h"
#include "pixel.h"
#include "Shape.h"
#include "camera.h"
#include "variables.h"

using std::vector;

int main() {
	pixel_image myimage(width, height);
    camera mycamera(posi, lookat, up, fovy);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixel p(0,0,0);
			myimage.calcPixel(mycamera.genRay(i, j, width, height, max_depth), objects);
		}
	}
	myimage.outputImage("testing2.png");
}