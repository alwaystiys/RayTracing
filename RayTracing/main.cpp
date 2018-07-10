#include<iostream>
#include<fstream>
#include "vec3.h"
#include "ray.h"
using namespace std;

void rayTracingVer2() {
    ofstream outFile;
    outFile.open("ch2.ppm");
    int nx = 200;
    int ny = 100;
    //cout << "P3\n" << nx << " " << ny << "\n255\n";
    outFile << "P3\n" << nx << " " << ny << "\n255\n";
    for(int j = 0; j < ny; ++j) {
        for(int i = 0; i < nx; ++i) {
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

void rayTracingVer1() {
    ofstream outFile;
    outFile.open("example.ppm");
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
    outFile.open("rt3.ppm");
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

int main() {
    //rayTracingVer1();
    //rayTracingVer2();
    rayTracingVer3();
    return 0;
}