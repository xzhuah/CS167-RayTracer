#pragma once
#include <vector>
#include "pixel.h"
#include "FreeImage.h"
#include "color.h"

class pixel_image {
public:
	int width;
	int height;
	pixel *image;

	pixel_image(int width, int height) {
		this->width = width;
		this->height = height;
		image = new pixel[width*height];
	}
    
    void calcPixel(int i, int j, ray myray, vector<Shape>& objects, int max_depth) {
        pixel[i][j] = myCalcPixel(myray, objects, max_depth);
    }

    color myCalcPixel(ray myray, vector<Shape>& objects, int max_depth) {
        if (max_depth <= 0) return color();

        color res(0,0,0);
        vertexnormal vn;
        int idx = -1;
        getIntersection(myray, objects, vn, idx);
        if (idx == -1) return res;
        ray newray(vn.vertex, glm::normalize(myray.dir - vn.mynormal * 2 * (vn.mynormal.dot(myray.dir))) );
        newray.source = newray.source + newray.dir*EPS;
        res = res + objects[idx].ambient + myCalcPixel(newray, objects, max_depth - 1);
        return res;
    }

	void outputImage(const char* filename) {
		FreeImage_Initialise();
		
		int pix = width * height;
		BYTE *pixels = new BYTE[3 * pix];
		for (int i = 0,j=0; i <  pix,j<pix*3; i++,j+=3) {
			pixels[j] = image[i].b;
			pixels[j + 1] = image[i].g;
			pixels[j + 2] = image[i].r;
		}
		FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
		FreeImage_Save(FIF_PNG, img, filename, 0);
		FreeImage_DeInitialise();
	}

private:
    void getIntersection(ray myray, vector<Shape>& objects, vertexnormal& vn, int& idx) {
        vertexnormal tmp;
        float min_dis = 1e9, cur_dis;
        for (int i = 0; i < objects.size(); i++) {
            tmp = objects[i].findIntersection(myray.transf(glm::inverse(objects[i].mat4)));
            tmp = tmp.transf(objects[i].mat4);
            cur_dis = tmp.vertex.getdis(myray.source);
            if (cur_dis < min_dis) {
                min_dis = cur_dis;
                vn = tmp;
                idx = i;
            }
        }
    }
};