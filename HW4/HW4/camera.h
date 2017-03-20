#pragma once
#include "point.h"
#include "Vec3.h"
#include "ray.h"
#include <cmath>
class camera
{
public:
	point posi;
	Vec3 camera_front;//-W
	Vec3 camera_right;//U
	Vec3 camera_up;//V
	float fovy;

    camera() {}
	camera(const point & posi, const point& lookat, const Vec3& up, float fovy) {
		this->posi = posi;

		Vec3 w(posi.minus(lookat));
		w.normalize();
		camera_front = w.negative();
        Vec3 u = up;
		Vec3 u = u.cross(w);
		u.normalize();
		camera_right = u;
		camera_up = w.cross(u);
		
		this->fovy = fovy;
	}
	ray genRay(int i, int j, int height,int width) {
		point source(this->posi);
		float alpha = tan(fovy / 2)*(j - width / 2) / (width / 2);
		float blta= tan(fovy / 2)*(height/2 -i) / (height / 2);
		Vec3 direction_ray = this->camera_front + this->camera_right*alpha + this->camera_up*blta;
		direction_ray.normalize();
		return ray(source,direction_ray);
	}
    ~camera() {}

private:

};
