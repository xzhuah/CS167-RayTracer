#pragma once
#include "point.h"
#include "matrix44.h"

class ray
{
public:
	point source;
	Vec3 dir;
	ray() {}
	ray(point source, Vec3 direction) {
		this->source = source;
		this->dir = Vec3::normalize(direction);
	}

	point calcPosi(float t) const {
		point result(this->source + dir*t);
		return result;
	}

    ray transf(const matrix44& mat) {
        ray newray;
        float tmp1[4] = { source.x, source.y, source.z, 1 };
        float tmp2[4] = { dir.x, dir.y, dir.z, 0 };
        float res[4];
        for (int i = 0; i < 4; i++) {
            res[i] = 0;
            for (int j = 0; j < 4; j++) {
                res[i] += mat.matrix[i][j] * tmp1[j];
            }
        }
        newray.source = point(res[0], res[1], res[2]);

        for (int i = 0; i < 4; i++) {
            res[i] = 0;
            for (int j = 0; j < 4; j++) {
				//ignore the translate component
				res[i] += mat.matrix[i][j] * tmp2[j];
            }
        }
        newray.dir = Vec3::normalize(Vec3(res[0], res[1], res[2]));
        return newray;
    }
};