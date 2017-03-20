#pragma once
#include "point.h"
#include "color.h"
#include "ray.h"
#include "Vec3.h"
#include "shape.h"
class triangle:public Shape {
public:
	point a, b, c;
	Vec3 mnormal;
	triangle(const point& a, const point& b, const point& c) {
		this->a = a;
		this->b = b;
		this->c = c;

		Vec3 ab(b.x - a.x, b.y - a.y, b.z - a.z);
		Vec3 ac(c.x - a.x, c.y - a.y, c.z - a.z);
		mnormal = ab.cross(ac);
		mnormal.normalize();
	}
	virtual vertexnormal findIntersection(ray& theray) {
        vertexnormal res = vertexnormal();
		Vec3 A(this->a.x, this->a.y, this->a.z);
		Vec3 P0(theray.source.x, theray.source.y, theray.source.z);
		float up = A.dot(this->mnormal)-P0.dot(this->mnormal);
		float down = theray.dir.dot(this->mnormal);
		if (down == 0) {
			//parallel
            return res;
		}
		else {
			float t = up / down;
			point p = theray.calcPosi(t);
			//is inter inside the triangle?
            Vec3 ab(b.x - a.x, b.y - a.y, b.z - a.z);
            Vec3 ac(c.x - a.x, c.y - a.y, c.z - a.z);
            Vec3 ap(p.x - a.x, p.y - a.y, p.z - a.z);
            float alpha = (ap.x * ac.y - ap.y * ac.x) / (ab.x * ac.y - ab.y * ac.x);
            float beta = (ap.x - ab.x * alpha) / ac.x;
            if (alpha < 0 || alpha > 1 || beta < 0 || beta > 1 || alpha + beta > 1 ) return res;
            else return vertexnormal(p, this->mnormal);
		}
	}
};