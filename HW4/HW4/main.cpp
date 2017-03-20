#pragma once
#include <vector>
#include "pixel_image.h"
#include "pixel.h"
#include "Shape.h"
#include "camera.h"
#include "variables.h"
#include "readfile.h"

int main() {
    readfile("C:/Users/Darren/Desktop/CS-167-Ray-Tracer/testscenes/scene1.test");
	pixel_image myimage(width, height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixel p(0,0,0);
			myimage.calcPixel(i, j, mycamera.genRay(i, j, height,width), maxdepth);
		}
	}
	myimage.outputImage("testing2.png");
}