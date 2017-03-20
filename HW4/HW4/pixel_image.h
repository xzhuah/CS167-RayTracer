#pragma once
#include <vector>
#include "pixel.h"
#include "FreeImage.h"
#include "color.h"
#include "ray.h"
#include "vertexnormal.h"
#include "variables.h"

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

	void calcPixel(int x, int y, ray myray, int max_depth) {
		color c = myCalcPixel(myray, max_depth);
		image[x*width + y] = pixel(c.r * 255 + 0.5, c.g * 255 + 0.5, c.b * 255 + 0.5);
        //printf("%f %f %f\n", c.r, c.g, c.b);
	}

	color myCalcPixel(ray myray, int max_depth) {
		if (max_depth <= 0) return color();

		color res(0, 0, 0);
		vertexnormal vn;
		int idx = -1;
		getIntersection(myray, vn, idx);
		if (idx == -1) return res;
		ray newray(vn.vertex, Vec3::normalize(myray.dir - vn.mynormal * 2 * (vn.mynormal.dot(myray.dir))));
		newray.source = newray.source + newray.dir*eps;
		res = objects[idx]->ambient + objects[idx]->emission;
		float decay, dis;
        //printf("%d\n", lights.size());
		for (int i = 0; i < lights.size(); i++) {
            //printf("calc lights\n");
			if (visible(vn.vertex, lights[i])) {
                //printf("here!!!!!!!!!!!!!!!!!!!!!!\n");
				if (lights[i].type == 1) {
					dis = vn.vertex.getdis(point(lights[i].dir.x, lights[i].dir.y, lights[i].dir.z));
					decay = 1 / (attenuation_const + attenuation_linear*dis + attenuation_quadratic*dis*dis);
                    //printf("%f %f %f %f\n", attenuation_const, attenuation_linear, attenuation_quadratic, decay);
				}
                else decay = 1.0f;
				Vec3 light_dir = lights[i].type == 0 ? lights[i].dir :  lights[i].dir - Vec3(vn.vertex.x, vn.vertex.y, vn.vertex.z) ;
                light_dir = Vec3::normalize(light_dir);
				Vec3 half_angle = Vec3::normalize( myray.dir.negative() + light_dir );

                color lambert = objects[idx]->diffuse  * max(vn.mynormal.dot(light_dir), 0);
                color phong = objects[idx]->specular * pow(max(vn.mynormal.dot(half_angle), 0), objects[idx]->shininess);
                res = res + lights[i].c * decay * ( lambert + phong );
			}
		}
		color post = myCalcPixel(newray, max_depth - 1); 
        res = res + post * objects[idx]->specular;
		return res;
	}

	void outputImage(const char* filename) {
		FreeImage_Initialise();

		int pix = width * height;
		BYTE *pixels = new BYTE[3 * pix];
		for (int i = 0, j = 0; i < pix, j<pix * 3; i++, j += 3) {
			pixels[j] = image[i].b;
			pixels[j + 1] = image[i].g;
			pixels[j + 2] = image[i].r;
		}
		FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, width, height, width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);
		FreeImage_Save(FIF_PNG, img, filename, 0);
		FreeImage_DeInitialise();
	}

private:
	void getIntersection(ray myray, vertexnormal& vn, int& idx) {
		vertexnormal tmp;
		float min_dis = 1e9, cur_dis;
		for (int i = 0; i < objects.size(); i++) {
			tmp = objects[i]->findIntersection(myray.transf(matrix44::inverse(objects[i]->transform)));
			tmp = tmp.transf(objects[i]->transform);
			if (tmp.mynormal.x == 0 && tmp.mynormal.y == 0 && tmp.mynormal.z == 0) continue;
			cur_dis = tmp.vertex.getdis(myray.source);
			if (cur_dis < min_dis) {
				min_dis = cur_dis;
				vn = tmp;
				idx = i;
			}
		}
	}
	bool visible(point pos, Light light) {
		Vec3 light_dir = light.type == 0 ? light.dir : light.dir - Vec3(pos.x, pos.y, pos.z);
        light_dir = Vec3::normalize(light_dir);
		ray myray(pos + light_dir*0.001, light_dir);
		vertexnormal vn;
		int idx = -1;
		getIntersection(myray, vn, idx);
		if (idx == -1) return true;
		if (light.type == 0) return false;
		float dis1 = vn.vertex.getdis(pos);
		float dis2 = point(light.dir.x, light.dir.y, light.dir.z).getdis(pos);
		return dis1 > dis2;
	}
	float max(float a, float b) {
		if (a > b) return a;
		else return b;
	}
};