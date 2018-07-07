#include<iostream>
#include<fstream>
#include "vec3.h"
using namespace std;

void rayTracingVer2(){
	ofstream outFile;
	outFile.open("ch2.ppm");
	int nx = 200;
	int ny = 100;
	//cout << "P3\n" << nx << " " << ny << "\n255\n";
	outFile << "P3\n" << nx << " " << ny << "\n255\n";
	for(int j = 0; j < ny; ++j){
		for(int i = 0; i < nx; ++i){
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

void rayTracingVer1(){
	ofstream outFile;
	outFile.open("example.ppm");
	int nx = 200;
	int ny = 100;
	//cout << "P3\n" << nx << " " << ny << "\n255\n";
	outFile << "P3\n" << nx << " " << ny << "\n255\n";
	for(int j = 0; j < ny; ++j){
		for(int i = 0; i < nx; ++i){
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

int main(){
	//rayTracingVer1();
	rayTracingVer2();
	return 0;
}