#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"

struct hit_record
{
	float t; // 撞击时的取值
	vec3 p; // 撞击时的点
	vec3 normal; // 单位化撞击时的法线
};

class hitable {
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif HITABLE_H