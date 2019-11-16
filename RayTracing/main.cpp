#include<iostream>
#include<fstream>
#include "vec3.h"
#include "ray.h"

#include "sphere.h"
#include "hitable_list.h"
//#include "cfloat"

using namespace std;

static string prefixPath = "../Image/";

void rayTracingVer1() {
    ofstream outFile;
    outFile.open(prefixPath + "example.ppm");
    int nx = 200;
    int ny = 100;
    //cout << "P3\n" << nx << " " << ny << "\n255\n";
    outFile << "P3\n" << nx << " " << ny << "\n255\n";
    for(int j = 0; j < ny; ++j) {
        for(int i = 0; i < nx; ++i) {
            float r = float(i) / float(nx);
            float g = float(ny - j) / float(ny);
            float b = 0.2;
            int ir = int(255 * r);
            int ig = int(255 * g);
            int ib = int(255 * b);
            //cout << ir << " " << ig << " " << ib << "\n";
            outFile << ir << " " << ig << " " << ib << "\n";
        }
    }
    outFile.close();
}

void rayTracingVer2() {
	ofstream outFile;
	outFile.open(prefixPath + "ch2.ppm");
	int nx = 200;
	int ny = 100;
	//cout << "P3\n" << nx << " " << ny << "\n255\n";
	outFile << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = 0; j < ny; ++j) {
		for (int i = 0; i < nx; ++i) {
			vec3 col(float(i) / float(nx), float(ny - j) / float(ny), 0.2);
			int ir = int(255 * col[0]);
			int ig = int(255 * col[1]);
			int ib = int(255 * col[2]);
			//cout << ir << " " << ig << " " << ib << "\n";
			outFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outFile.close();
}

////////////////////////////////////////////////////////////////////

vec3 color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

void rayTracingVer3() {
    int nx = 200;
    int ny = 100;
    ofstream outFile;
    outFile.open(prefixPath + "rt3.ppm");
    //std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    outFile << "P3\n" << nx << " " << ny << "\n255\n";
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vetrical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    for(int j = ny - 1; j >= 0; j--) {
        for(int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u * horizontal + v * vetrical);
            vec3 col = color(r);
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);
            //std::cout << ir << " " << ig << " " << ib << "\n";
            outFile << ir << " " << ig << " " << ib << "\n";
        }
    }
    outFile.close();
}

////////////////////////////////////////////////////////////////////


bool hit_sphere(const vec3& center, float radius, const ray& r) {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;
	return discriminant > 0;
}

vec3 color2(const ray& r) {
	if (hit_sphere(vec3(0, 0, -1), 0.5, r)) {
		return vec3(1, 0, 0);
	}
	vec3 unit_direction = unit_vector(r.direction());
	float t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

void rayTracingVer4() {
	int nx = 200;
	int ny = 100;
	ofstream outFile;
	outFile.open(prefixPath + "hitSphere.ppm");
	//std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	outFile << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vetrical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vetrical);
			vec3 col = color2(r);
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			//std::cout << ir << " " << ig << " " << ib << "\n";
			outFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outFile.close();
}

////////////////////////////////////////////////////////////////////


float hit_sphere2(const vec3& center, float radius, const ray& r) {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
}

vec3 color3(const ray& r) {
	float t = hit_sphere2(vec3(0, 0, -1), 0.5, r);
	
	if (t > 0.0) {
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
		return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	
	vec3 unit_direction = unit_vector(r.direction());
	t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

void rayTracingVer5() {
	int nx = 200;
	int ny = 100;
	ofstream outFile;
	outFile.open(prefixPath + "hitSphere2.ppm");
	//std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	outFile << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vetrical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vetrical);
			vec3 col = color3(r);
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			//std::cout << ir << " " << ig << " " << ib << "\n";
			outFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outFile.close();
}

////////////////////////////////////////////////////////////////////

vec3 color4(const ray& r, hitable *world) {
	hit_record rec;
	if(world->hit(r, 0.0, FLT_MAX, rec)){
		return 0.5 * vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
	}
	else {
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

void rayTracingVer6() {
	int nx = 200;
	int ny = 100;
	ofstream outFile;
	outFile.open(prefixPath + "hitSphere3.ppm");
	//std::cout << "P3\n" << nx << " " << ny << "\n255\n";
	outFile << "P3\n" << nx << " " << ny << "\n255\n";
	vec3 lower_left_corner(-2.0, -1.0, -1.0);
	vec3 horizontal(4.0, 0.0, 0.0);
	vec3 vetrical(0.0, 2.0, 0.0);
	vec3 origin(0.0, 0.0, 0.0);

	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);

	hitable *world = new hitable_list(list, 2);
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r(origin, lower_left_corner + u * horizontal + v * vetrical);

			//vec3 p = r.point_at_parameter(2.0);
			vec3 col = color4(r, world);

			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);
			//std::cout << ir << " " << ig << " " << ib << "\n";
			outFile << ir << " " << ig << " " << ib << "\n";
		}
	}
	outFile.close();
}

////////////////////////////////////////////////////////////////////


int main() {
    //rayTracingVer1();
    //rayTracingVer2();
    //rayTracingVer3();
	//rayTracingVer4();
	//rayTracingVer5();
	rayTracingVer6();
    return 0;
}