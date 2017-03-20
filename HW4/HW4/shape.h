#pragma once
#include "ray.h"
#include "vertexnormal.h"
#include "matrix44.h"
class Shape {
public:
    color ambient;
    color diffuse;
    color specular;
    color emission;
    float shininess;
    matrix44 transform;
	Shape() {

	}
	virtual vertexnormal findIntersection(ray& theray) {

	}
	~Shape() {

	}
};