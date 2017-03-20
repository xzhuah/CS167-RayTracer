#pragma once
#include "point.h"
#include "color.h"
#include "ray.h"
#include "Vec3.h"
#include "intersection.h"
#include "primitive.h"
class triangle:public primitive {
public:
	point a, b, c;
	normal mnormal;
	triangle(const point& a, const point& b, const point& c) {
		this->a = a;
		this->b = b;
		this->c = c;

		Vec3 ab(b.x - a.x, b.y - a.y, b.z - a.z);
		Vec3 ac(c.x - a.x, c.y - a.y, c.z - a.z);
		mnormal = ab.cross(ac);
		mnormal.normalize();
	}
	virtual intersection findIntersection(ray& theray) {
		//return the 
		Vec3 A(this->a.x, this->a.y, this->a.z);
		Vec3 P0(theray.source.x, theray.source.y, theray.source.z);
		float up = A.dot(this->mnormal)-P0.dot(this->mnormal);
		float down = theray.dir.dot(this->mnormal);
		if (down == 0) {
			//parallel
		}
		else {
			float t = up / down;
			point inter = theray.calcPosi(t);
			//is inter inside the triangle?
		}
	}
};