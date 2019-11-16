#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"

struct hit_record
{
	float t; // ײ��ʱ��ȡֵ
	vec3 p; // ײ��ʱ�ĵ�
	vec3 normal; // ��λ��ײ��ʱ�ķ���
};

class hitable {
public:
	virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const = 0;
};

#endif HITABLE_H