#pragma once
#include "ray.h"
#include "intersection.h"
#include "color.h"
class Primitive {
public:
	color mycolor;
	Primitive() {

	}
	Primitive(color mcolor) {
		this->mycolor = mcolor;
	}
	const color& getColor() const{
		return this->mycolor;
	}
	virtual intersection findIntersection(ray& theray) {
		return intersection();
	}
	virtual ~Primitive() {

	}

private:
};

class sphere : public Primitive {
public:
	point center;
	float radius;
	sphere() {

	}
	sphere(point& center, float radius, color& mcolor) {
		this->center = center;
		this->radius = radius;
		this->mycolor = mcolor;
	}
	intersection findIntersection(ray& theray) {
		Vec3 Poc = theray.source.minus(this->center);
		float a = theray.dir.dot(theray.dir);
		float b = 2 * theray.dir.dot(Poc);
		float c = Poc.dot(Poc) - this->radius*this->radius;

		float delta = b*b - 4 * a*c;

		if (delta < 0) {
			//Didn't intersection
			return intersection();
		}
		else {
			float r1 = (-b + pow(delta, 0.5)) / 2 / a;
			float r2 = (-b - pow(delta, 0.5)) / 2 / a;
			if (r2 > 0) {
				//pick the smaller
				if (r1 != r2) {
					//not tangent

					point inter_point = theray.calcPosi(r1);
					Vec3 normal = inter_point.minus(this->center);
				}
				else {
					//tangent
					point inter_point = theray.calcPosi(r1);
					Vec3 normal = inter_point.minus(this->center);

				}
			}
			else if (r1 > 0) {
				//ray source inside the sphere
				point inter_point = theray.calcPosi(r1);
				Vec3 normal = this->center.minus(inter_point);
			}
			else {
				//no intersect
			}
		}
	}
};

class triangle :public Primitive {
public:
	point a, b, c;
	color mcolor;
	normal mnormal;
	triangle(const point& a, const point& b, const point& c, const color& mcolor) {
		this->a = a;
		this->b = b;
		this->c = c;
		this->mcolor = mcolor;

		Vec3 ab(b.x - a.x, b.y - a.y, b.z - a.z);
		Vec3 ac(c.x - a.x, c.y - a.y, c.z - a.z);
		mnormal = ab.cross(ac);
		mnormal.normalize();
	}
	virtual intersection findIntersection(ray& theray) {
		//return the 
		Vec3 A(this->a.x, this->a.y, this->a.z);
		Vec3 P0(theray.source.x, theray.source.y, theray.source.z);
		float up = A.dot(this->mnormal) - P0.dot(this->mnormal);
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