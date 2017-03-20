#pragma once
#include <vector>
#include <iostream>
#include "pixel_image.h"
#include "pixel.h"
#include "Shape.h"
#include "camera.h"
#include "variables.h"
#include "readfile.h"
using namespace std;

int main() {
    readfile("D:/GoogleDownload/homework_hw3-submissionscenes/hw3-submissionscenes/scene3.test");
	
	float progress = 0;
	pixel_image myimage(width, height);
	//#pragma omp parallel for
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			pixel p(0,0,0);
			myimage.calcPixel(i, j, mycamera.genRay(i, j, height,width), maxdepth);
		}
		progress = (float)i / height*100;
		cout << i <<"/"<<height<<" "<<progress<<"%"<<endl;//prograss
	}

	myimage.outputImage("D:/GoogleDownload/homework_hw3-submissionscenes/hw3-submissionscenes/scene3.png");
	cout << "finish" << endl;
	/*float aa;
	cin >> aa;*/
	
}