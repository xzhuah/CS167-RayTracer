#pragma once
#include "point.h"
#include "color.h"
#include "ray.h"
#include "Vec3.h"
#include "shape.h"
#include <iostream>
using namespace std;
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
        //printf("%f %f %f\n", theray.dir.x, theray.dir.y, theray.dir.z);
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
			if (t < eps) {
				return res;
			}
			point p = theray.calcPosi(t);
            //printf("%f %f %f\n", p.x, p.y, p.z);
            Vec3 ab(b.x - a.x, b.y - a.y, b.z - a.z);
            Vec3 ac(c.x - a.x, c.y - a.y, c.z - a.z);
            Vec3 ap(p.x - a.x, p.y - a.y, p.z - a.z);
            float alpha = ( ac.dot(ac)*ap.dot(ab) - ac.dot(ab)*ap.dot(ac) ) / ( ac.dot(ac)*ab.dot(ab)-ac.dot(ab)*ab.dot(ac) );
            float beta = ( ab.dot(ab)*ap.dot(ac) - ac.dot(ab)*ap.dot(ab) ) / ( ac.dot(ac)*ab.dot(ab) - ac.dot(ab)*ab.dot(ac) );
            //float test_val = alpha * ab.z + beta * ab.z - ap.z;
            //if (test_val > eps || test_val < -eps) printf("wrong calc\n");
            if (alpha < 0 || alpha > 1 || beta < 0 || beta > 1 || alpha + beta > 1) {
                return res;
            }
            else {
                //printf("%f %f\n", alpha, beta);
                return vertexnormal(p, this->mnormal*(-this->mnormal.dot(theray.dir)));
            }
		}
	}
};